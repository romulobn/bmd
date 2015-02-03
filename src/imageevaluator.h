#ifndef IMAGEEVALUATOR_H
#define IMAGEEVALUATOR_H

#include <QString>

class ImageEvaluator
{
public:
    ImageEvaluator();

    void evaluateImages(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath);
    void evaluateImage(const QString &srcImgPath, const QString &bibImgPath, const QString &resultFilePath);
    void measureImagesIntesityValues(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath);
    void measureImageIntesityValues(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath);
    void measureImagesPixelIntesityValues(const QString &srcDirPath, const QString &binDirPath, const QStringList &filters, const QString &resultFilePath);
    void measureImagePixelIntesityValues(const QString &srcImgPath, const QString &binImgPath, const QString &resultFilePath);
    
private:
    QStringList getFileList(const QString &srcDir, const QStringList &filters);
};

#endif // IMAGEEVALUATOR_H
