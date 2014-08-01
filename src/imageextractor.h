#ifndef IMAGEEXTRACTOR_H
#define IMAGEEXTRACTOR_H

#include <QString>
#include <QStringList>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <caib/imgproc.h>

class ImageExtractor
{
public:
    ImageExtractor();

    void measureImages(const QString &srcDirPath, const QString &destFilePath, const QString &filter, float scale);
    void measureImage(const QString &srcImgPath, const QString &destFilePath, float scale);

private:
    QStringList getFileList(const QString &srcDir, const QString &filter);
};

#endif // IMAGEEXTRACTOR_H
