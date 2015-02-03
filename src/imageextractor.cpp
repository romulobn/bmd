#include "imageextractor.h"

#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

ImageExtractor::ImageExtractor()
{

}

void ImageExtractor::measureImages(const QString &srcDirPath, const QString &destFilePath, const QStringList &filters, float scale)
{
    Q_ASSERT(QDir(srcDirPath).exists() && (QFileInfo(destFilePath).isFile() || !QFileInfo(destFilePath).exists()));
    QStringList fileList = getFileList(srcDirPath, filters);
    QString fileName;

    foreach (fileName, fileList) {
        measureImage(srcDirPath + "/"+ fileName, destFilePath, scale);
    }
}

void ImageExtractor::measureImage(const QString &srcImgPath, const QString &destFilePath, float scale)
{
    cv::Mat input = cv::imread(srcImgPath.toStdString(), cv::IMREAD_GRAYSCALE);
    Q_ASSERT(input.data);

    input = caib::morphNeg(caib::morphBinary(input,100));

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(input.clone(), contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);

    QList<double> axon_area, axon_diam, fiber_area, fiber_diam, ratio_g;

    for (int i=0; !(i<0) && (i < hierarchy.size()); i = hierarchy[i][0]) {
        if (hierarchy[i][2] > -1) {
            int childIdx = hierarchy[i][2], maxChildIdx = 0;
            double maxArea = 0;


            while( childIdx != -1 ) {
                if(hierarchy[childIdx][3] != i)
                    break;
                if(cv::contourArea(contours[childIdx]) > maxArea) {
                    maxChildIdx = childIdx;
                    maxArea = cv::contourArea(contours[childIdx]);
                }

                childIdx = hierarchy[childIdx][0];
            }

            if ( caib::getMinCalliper(contours[maxChildIdx]) / caib::getMinCalliper(contours[i]) <= 1.0) {

               axon_area.append(cv::contourArea(contours[maxChildIdx]) * scale * scale);
               axon_diam.append(caib::getMinCalliper(contours[maxChildIdx]) * scale);
               fiber_area.append(cv::contourArea(contours[i]) * scale * scale);
               fiber_diam.append(caib::getMinCalliper(contours[i]) * scale);

               ratio_g.append(caib::getMinCalliper(contours[maxChildIdx]) / caib::getMinCalliper(contours[i]));

            }
        }
    }

    bool writeHeader = true;

    if(QFileInfo(destFilePath).exists()) {
        writeHeader = false;
    }

    QFile savingFile(destFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    QTextStream outStream(&savingFile);


    if( writeHeader )
        outStream << "Axon Area" << "," << "Axon Diameter" << "," << "Fiber Area" << "," << "Fiber Diameter" << "," << "Ratio G" << "\n";

    while( !axon_area.empty() && !axon_diam.empty() && !fiber_area.empty() && !fiber_diam.empty() && !ratio_g.empty()) {

        outStream << axon_area.first() << "," << axon_diam.first() << ","  << fiber_area.first() << "," << fiber_diam.first() << "," << ratio_g.first() << "\n";

        axon_area.pop_front();
        axon_diam.pop_front();
        fiber_area.pop_front();
        fiber_diam.pop_front();
        ratio_g.pop_front();

    }

    savingFile.close();

}

QStringList ImageExtractor::getFileList(const QString &srcDir, const QStringList &filters)
{
    QDir dir(srcDir);

    QStringList fileList = dir.entryList(), outputList;
    QString fileName;
    foreach(fileName, fileList)
    {
        foreach(QString filter, filters) {
            if(fileName.endsWith( "." + filter, Qt::CaseInsensitive))
            {
               outputList.append(fileName);
            }
        }
    }

    return outputList;
}
