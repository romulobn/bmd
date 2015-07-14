#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDir>

#include "../src/imageevaluator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("image-segmentation-evaluator");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Image segmentation evaluator");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption binaryDirectoryOption(QStringList() << "b" << "binary-directory", QCoreApplication::translate("main", "Segmentation binary images of the <binary-directory>."), QCoreApplication::translate("main", "target-directory"));
    parser.addOption(binaryDirectoryOption);
    
    QCommandLineOption outputFileOption(QStringList() << "o" << "output-file", QCoreApplication::translate("main", "Save all extracted morphometric measures into <output-file>."), QCoreApplication::translate("main", "output-file"));
    parser.addOption(outputFileOption);
    
    QCommandLineOption sourceDirectoryOption(QStringList() << "s" << "source-directory", QCoreApplication::translate("main", "Source binary images of the <source-directory>."), QCoreApplication::translate("main", "source-directory"));
    parser.addOption(sourceDirectoryOption);
    
    QCommandLineOption evaluationTypeOption(QStringList() << "e" << "evaluation-type", QCoreApplication::translate("main", "Evaluate binary images and source images using the algorithm for the <evaluation-type>."), QCoreApplication::translate("main", "evaluation-type"));
    parser.addOption(evaluationTypeOption);
    
    parser.process(app);
    
    if (!parser.isSet(binaryDirectoryOption) || !parser.isSet(outputFileOption) || !parser.isSet(sourceDirectoryOption) || !parser.isSet(evaluationTypeOption)) {
        parser.showHelp();
        return -1;
    }
    
    QString binaryDirectory = parser.value(binaryDirectoryOption);
    QString sourceDirectory = parser.value(sourceDirectoryOption);
    QString outputFile = parser.value(outputFileOption);
    QString evaluationType = parser.value(evaluationTypeOption);
    QStringList filters = QStringList() << QStringList() << "jpg" << "jpeg" << "tif" << "tiff" << "bmp";
    if (evaluationType == "seg") {
        ImageEvaluator().evaluateImages(sourceDirectory, binaryDirectory, filters, outputFile);
    } else if (evaluationType == "img") {
        ImageEvaluator().measureImagesIntesityValues(sourceDirectory, binaryDirectory, filters, outputFile);
    } else if(evaluationType == "pxl") {
        ImageEvaluator().measureImagesPixelIntesityValues(sourceDirectory, binaryDirectory, filters, outputFile);
    }
    
    return 0;
}
