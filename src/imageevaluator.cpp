#include "imageevaluator.h"

#include <QDir>
#include <QDate>
#include <QTextStream>
#include <opencv/cv.h>
#include <caib/imgproc.h>

ImageEvaluator::ImageEvaluator()
{

}

void ImageEvaluator::evaluateImages(const QString &srcDirPath, const QString &binDirPath, const QString &srcfilter, const QString &binfilter, const QString &resultFilePath)
{
    Q_ASSERT(QDir(srcDirPath).exists() && QDir(binDirPath).exists());
    QStringList srcFileList = getFileList(srcDirPath, srcfilter);
    QStringList binFileList = getFileList(binDirPath, binfilter);
    QString srcFileName, binFileName;

    foreach(srcFileName, srcFileList) {
        foreach(binFileName, binFileList) {
            if(binFileName.contains(srcFileName.split("." + srcfilter).first()))
                evaluateImage(srcDirPath + "/" + srcFileName, binDirPath + "/" + binFileName, resultFilePath);
        }
    }
}

void ImageEvaluator::evaluateImage(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath)
{
    cv::Mat srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_COLOR);
    cv::Mat binImg = cv::imread(binImgPath.toStdString(), cv::IMREAD_COLOR);

    Q_ASSERT(srcImg.data && binImg.data);

    srcImg = caib::morphBinary(srcImg, 100);
    binImg = caib::morphBinary(binImg, 100);

    QFile savingFile(resultFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    QTextStream outStream(&savingFile);

    outStream << "Image" << "\t" << srcImgPath.split("/").last();
    outStream << "Evaluation Date" << "\t" << QDate::currentDate().toString() << "\n";
    outStream << "Area Overlap" << "\t" << "Area Similarity" << "\t" << "Overlap Error"
              << "\t" << "Sensivity" << "\t" << "FP" << "\t" << "TP" << "\t" << "FN" << "\n";


    cv::Mat TP_only_img = caib::morphInfrec(caib::morphIntersec(caib::morphNeg(binImg), srcImg), srcImg);
    cv::Mat TP_only_bin = caib::morphInfrec(caib::morphIntersec(caib::morphNeg(binImg), srcImg), caib::morphNeg(binImg));

    outStream << caib::areaOverlap(TP_only_bin, TP_only_img) << "\t";
    outStream << caib::areaSimilarity(TP_only_bin, TP_only_img) << "\t";
    outStream << caib::overlapError(TP_only_bin, TP_only_img) << "\t";
    outStream << caib::sensivity(caib::morphNeg(binImg), srcImg) << "\t";
    outStream << caib::getFP(caib::morphNeg(binImg), srcImg) << "\t";
    outStream << caib::getTP(caib::morphNeg(binImg), srcImg) << "\t";
    outStream << caib::getFN(caib::morphNeg(binImg), srcImg) << "\n";
}

QStringList ImageEvaluator::getFileList(const QString &srcDir, const QString &filter)
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
