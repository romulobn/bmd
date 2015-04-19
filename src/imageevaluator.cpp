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

void ImageEvaluator::evaluateImages(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath)
{
    Q_ASSERT(QDir(srcDirPath).exists() && QDir(binDirPath).exists());
    QStringList srcFileList = getFileList(srcDirPath, filters);
    QStringList binFileList = getFileList(binDirPath, filters);
    QString srcFileName, binFileName;

    foreach(srcFileName, srcFileList) {
        foreach(binFileName, binFileList) {
            if( srcFileName.split(".").first().compare( binFileName.split(".").first().replace("B", ""), Qt::CaseInsensitive) == 0 ){
                qDebug() << srcFileName << " " << binFileName << " " ;
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
        outStream << "Image" << "," <<"Area Overlap" << "," << "Area Similarity" << "," << "Overlap Error"
        << "," << "Sensivity" << "," << "FP" << "," << "TP" << "," << "FN" << "\n";
    }
    
    cv::Mat TP_only_img = caib::morphInfrec(caib::morphIntersec(binImg, srcImg), srcImg);
    cv::Mat TP_only_bin = caib::morphInfrec(caib::morphIntersec(binImg, srcImg), binImg);
    
    outStream <<  srcImgPath.split("/").last() << ",";
    outStream << caib::areaOverlap(TP_only_bin, TP_only_img) << ",";
    outStream << caib::areaSimilarity(TP_only_bin, TP_only_img) << ",";
    outStream << caib::overlapError(TP_only_bin, TP_only_img) << ",";
    outStream << caib::sensivity(binImg, srcImg) << ",";
    outStream << caib::getFP(binImg, srcImg) << ",";
    outStream << caib::getTP(binImg, srcImg) << ",";
    outStream << caib::getFN(binImg, srcImg) << "\n";
}

void ImageEvaluator::measureImagesPixelIntesityValues(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath)
{
    Q_ASSERT(QDir(srcDirPath).exists() && QDir(binDirPath).exists());
    QStringList srcFileList = getFileList(srcDirPath, filters);
    QStringList binFileList = getFileList(binDirPath, filters);
    QString srcFileName, binFileName;
    
    foreach(srcFileName, srcFileList) {
        foreach(binFileName, binFileList) {
            if( srcFileName.split(".").first().compare( binFileName.split(".").first(), Qt::CaseInsensitive) == 0 ){
                qDebug() << srcFileName << " " << binFileName;
                measureImagePixelIntesityValues(srcDirPath + "/" + srcFileName, binDirPath + "/" + binFileName, resultFilePath);
            }
        }
    }
}

void ImageEvaluator:: measureImagePixelIntesityValues(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath)
{
    cv::Mat srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_COLOR);
    cv::Mat binImg = cv::imread(binImgPath.toStdString(), cv::IMREAD_GRAYSCALE);
    
    Q_ASSERT(srcImg.data && binImg.data);
    
    binImg = caib::morphNeg(caib::morphBinary(binImg, 100));
    
    bool exist;
    if ((exist = QFileInfo(resultFilePath).exists())) {
        Q_ASSERT(!QFileInfo(resultFilePath).isDir());
    }
    
    QFile savingFile(resultFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    
    QTextStream outStream(&savingFile);
    
    if (!exist) {
        outStream << "class" << "," <<"L" << "," << "Y" << "," << "G" << "," << "X" << "," << "Z" << "," << "R" << "\n";
    }
    
    cv::Mat bgr_img = srcImg.clone();
    bgr_img.convertTo(bgr_img, cv::DataType<cv::Vec3f>::type, 1./255);
    cv::Mat luv_img, xyz_img;
    cv::cvtColor(bgr_img, luv_img, cv::COLOR_BGR2Luv);
    cv::cvtColor(bgr_img, xyz_img, cv::COLOR_BGR2XYZ);
    cv::Mat final_img = cv::Mat(srcImg.size(), cv::DataType<cv::Vec6f>::type);
    for (int x=0; x<srcImg.cols; x++) {
        for (int y=0; y<srcImg.rows; y++) {
            cv::Vec6f vec = cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
            
            if(binImg.at<uchar>(cv::Point(x,y))) {
                outStream << "nonaxon" << ",";
            } else {
                outStream << "axon" << ",";
            }
            
            outStream << vec[0] << ",";
            outStream << vec[1] << ",";
            outStream << vec[2] << ",";
            outStream << vec[3] << ",";
            outStream << vec[4] << ",";
            outStream << vec[5] << "\n";
            
        }
    }
    
}

void ImageEvaluator::measureImagesIntesityValues(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath)
{
    Q_ASSERT(QDir(srcDirPath).exists() && QDir(binDirPath).exists());
    QStringList srcFileList = getFileList(srcDirPath, filters);
    QStringList binFileList = getFileList(binDirPath, filters);
    QString srcFileName, binFileName;
    
    foreach(srcFileName, srcFileList) {
        foreach(binFileName, binFileList) {
            if( srcFileName.split(".").first().compare( binFileName.split(".").first(), Qt::CaseInsensitive) == 0 ){
                qDebug() << srcFileName << " " << binFileName;
                measureImageIntesityValues(srcDirPath + "/" + srcFileName, binDirPath + "/" + binFileName, resultFilePath);
            }
        }
    }
}

void ImageEvaluator:: measureImageIntesityValues(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath)
{
    cv::Mat srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_COLOR);
    cv::Mat binImg = cv::imread(binImgPath.toStdString(), cv::IMREAD_GRAYSCALE);
    
    Q_ASSERT(srcImg.data && binImg.data);
    
    binImg = caib::morphBinary(binImg, 100);
    
    
    bool exist;
    if ((exist = QFileInfo(resultFilePath).exists())) {
        Q_ASSERT(!QFileInfo(resultFilePath).isDir());
    }
    
    QFile savingFile(resultFilePath);
    savingFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    
    QTextStream outStream(&savingFile);
    
    if (!exist) {
        outStream << "Image" << "," <<"axon-L" << "," << "axon-Y" << "," << "axon-G" << "," << "axon-X" << "," << "axon-Z" << "," << "axon-R" << "," << "nonaxon-L" << "," << "nonaxon-Y" << "," << "nonaxon-G" << "," << "nonaxon-X" << "," << "nonaxon-Z" << "," << "nonaxon-R" << "\n";
    }
    
    cv::Mat bgr_img = srcImg.clone();
    bgr_img.convertTo(bgr_img, cv::DataType<cv::Vec3f>::type, 1./255);
    cv::Mat luv_img, xyz_img;
    cv::cvtColor(bgr_img, luv_img, cv::COLOR_BGR2Luv);
    cv::cvtColor(bgr_img, xyz_img, cv::COLOR_BGR2XYZ);
    cv::Vec6f axon_vec = cv::Vec6f(0, 0, 0, 0, 0, 0);
    cv::Vec6f nonaxon_vec = cv::Vec6f(0, 0, 0, 0, 0, 0);
    cv::Mat final_img = cv::Mat(srcImg.size(), cv::DataType<cv::Vec6f>::type);
    for (int x=0; x<srcImg.cols; x++) {
        for (int y=0; y<srcImg.rows; y++) {
            if(binImg.at<uchar>(cv::Point(x,y))) {
                nonaxon_vec += cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
            } else {
                axon_vec += cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
            }
        }
    }
    
    axon_vec /= srcImg.cols * srcImg.rows;
    nonaxon_vec /= srcImg.cols * srcImg.rows;
    
    outStream << srcImgPath.split("/").last() << ",";
    outStream << axon_vec[0] << ",";
    outStream << axon_vec[1] << ",";
    outStream << axon_vec[2] << ",";
    outStream << axon_vec[3] << ",";
    outStream << axon_vec[4] << ",";
    outStream << axon_vec[5] << ",";
    outStream << nonaxon_vec[0] << ",";
    outStream << nonaxon_vec[1] << ",";
    outStream << nonaxon_vec[2] << ",";
    outStream << nonaxon_vec[3] << ",";
    outStream << nonaxon_vec[4] << ",";
    outStream << nonaxon_vec[5] << "\n";

}



QStringList ImageEvaluator::getFileList(const QString &srcDir, const QStringList &filters)
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
