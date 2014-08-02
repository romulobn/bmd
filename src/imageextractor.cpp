#include "imageextractor.h"

#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

ImageExtractor::ImageExtractor()
{

}

void ImageExtractor::measureImages(const QString &srcDirPath, const QString &destFilePath, const QString &filter, float scale)
{
    Q_ASSERT(QDir(srcDirPath).exists() && (QFileInfo(destFilePath).isFile() || !QFileInfo(destFilePath).exists()));
    QStringList fileList = getFileList(srcDirPath, filter);
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

    for (int i=0; !(i<0); i = hierarchy[i][0]) {
        if (hierarchy[i][2] > -1) {
            if ( caib::getMinCalliper(contours[hierarchy[i][2]]) / caib::getMinCalliper(contours[i]) <= 1.0) {

               axon_area.append(cv::contourArea(contours[hierarchy[i][2]]) * scale * scale);
               axon_diam.append(caib::getMinCalliper(contours[hierarchy[i][2]]) * scale);
               fiber_area.append(cv::contourArea(contours[i]) * scale * scale);
               fiber_diam.append(caib::getMinCalliper(contours[i]) * scale);

               ratio_g.append(caib::getMinCalliper(contours[hierarchy[i][2]]) / caib::getMinCalliper(contours[i]));

            }
        }
    }


    QFile savingFile(destFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    QTextStream outStream(&savingFile);

    outStream << "Image" << "\t" << destFilePath.split("/").last();
    outStream << "Extraction Date" << "\t" << QDate::currentDate().toString();
    outStream << "Axon Area" << "\t" << "Axon Diameter" << "\t" << "Fiber Area" << "\t" << "Fiber Diameter" << "\t" << "Ratio G" << "\n";


    while( !axon_area.empty() && !axon_diam.empty() && !fiber_area.empty() && !fiber_diam.empty() && !ratio_g.empty()) {

        outStream << axon_area.first() << "\t" << axon_diam.first() << "\t"  << "\t" << fiber_area.first() << "\t" << fiber_diam.first() << "\t" << ratio_g.first() << "\n";

        axon_area.pop_front();
        axon_diam.pop_front();
        fiber_area.pop_front();
        fiber_diam.pop_front();
        ratio_g.pop_front();

    }

    savingFile.close();

}

QStringList ImageExtractor::getFileList(const QString &srcDir, const QString &filter)
{
    QDir dir(srcDir);

    QStringList fileList = dir.entryList(), outputList;
    QString fileName;
    foreach(fileName, fileList)
    {
        if(fileName.endsWith( "." + filter))
        {
           outputList.append(fileName);
        }
    }

    return outputList;
}
