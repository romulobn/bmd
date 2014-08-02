#include "imageevaluator.h"

#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QDebug>

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
            if( srcFileName.split("." + srcfilter).first().compare( binFileName.split("." + binfilter).first() ) == 0 ){
                evaluateImage(srcDirPath + "/" + srcFileName, binDirPath + "/" + binFileName, resultFilePath);
            }
        }
    }
}

void ImageEvaluator::evaluateImage(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath)
{
    cv::Mat srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_GRAYSCALE);
    cv::Mat binImg = cv::imread(binImgPath.toStdString(), cv::IMREAD_GRAYSCALE);

    Q_ASSERT(srcImg.data && binImg.data);

    srcImg = caib::morphNeg(caib::morphBinary(srcImg, 100));
    binImg = caib::morphNeg(caib::morphBinary(binImg, 100));

    bool exist;
    if ((exist = QFileInfo(resultFilePath).exists())) {
        Q_ASSERT(!QFileInfo(resultFilePath).isDir());
    } else {

    }
    QFile savingFile(resultFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    QTextStream outStream(&savingFile);

    if (!exist) {
    outStream << "Image" << "\t" <<"Area Overlap" << "\t" << "Area Similarity" << "\t" << "Overlap Error"
              << "\t" << "Sensivity" << "\t" << "FP" << "\t" << "TP" << "\t" << "FN" << "\n";
    }

    cv::Mat TP_only_img = caib::morphInfrec(caib::morphIntersec(binImg, srcImg), srcImg);
    cv::Mat TP_only_bin = caib::morphInfrec(caib::morphIntersec(binImg, srcImg), binImg);

    outStream <<  srcImgPath.split("/").last() << "\t";
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
