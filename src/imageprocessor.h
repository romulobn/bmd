#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QStringList>
#include <QString>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <caib/imgproc.h>

class ImageProcessor
{
public:
    ImageProcessor(unsigned char options = 1);
    void processImages(const QString &srcDir, const QString &destDir, const QString &filter, const int nerve, const int pipeline);
    void processImage(const QString &srcImgPath, const QString &destImgPath, const int nerve, const int pipeline);

    enum NerveType {Laryngeal, Vestibulochoclear, Sural};
    enum Pipeline {Morph, Color};
    enum Options {SaveFinalImage = 1, SaveSteps = 3};

private:
    unsigned char optionsFlag;

    QStringList getFileList(const QString &srcDir, const QString &filter);
    cv::Mat segmentMyelinSheaths(const cv::Mat &input);
    cv::Mat removeMinorNoise(const cv::Mat &input);
    cv::Mat applyKumar(const cv::Mat &input);
    cv::Mat removeMajorNoise(const cv::Mat &input);

    double areaToClose, areaToOpen, learningRate;
    int clusterNumber, pipelineChosen, eleSize, threshSize;
};

#endif // IMAGEPROCESSOR_H
