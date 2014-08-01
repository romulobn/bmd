#ifndef IMAGEEVALUATOR_H
#define IMAGEEVALUATOR_H

#include <QString>

class ImageEvaluator
{
public:
    ImageEvaluator();

    void evaluateImages(const QString &srcDirPath, const QString &binDirPath, const QString &srcfilter, const QString &binfilter, const QString &resultFilePath);
    void evaluateImage(const QString &srcImgPath, const QString &bibImgPath, const QString &resultFilePath);

private:
    QStringList getFileList(const QString &srcDir, const QString &filter);
};

#endif // IMAGEEVALUATOR_H
