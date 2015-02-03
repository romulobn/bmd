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
    void processImages(const QString &srcDir, const QString &destDir, const QStringList &filters, const int nerve, const int pipeline);
    void processImage(const QString &srcImgPath, const QString &destImgPath, const int nerve, const int pipeline);

    enum NerveType {Laryngeal, Vestibulochoclear, Sural, Frenic, Vagus};
    enum Pipeline {Morph, Color};
    enum Options {SaveFinalImage = 1, SaveSteps = 2};

private:
    unsigned char optionsFlag;

    QStringList getFileList(const QString &srcDir, const QStringList &filters);
    cv::Mat segmentMyelinSheaths(const cv::Mat &input);
    cv::Mat removeMinorNoise(const cv::Mat &input);
    cv::Mat applyKumar(const cv::Mat &input);
    cv::Mat removeMajorNoise(const cv::Mat &input);

    double eleToClose, eleToOpen, learningRate;
    int clusterNumber, pipelineChosen, eleSize, threshSize;
    cv::Vec6f closestCenter;
};

#endif // IMAGEPROCESSOR_H
