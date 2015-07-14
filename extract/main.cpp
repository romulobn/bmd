#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDir>

#include "../src/imageextractor.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("morphometric-feature-extractor");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Morphometric feature extractor");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption outputFileOption(QStringList() << "o" << "output-file", QCoreApplication::translate("main", "Save all extracted morphometric measures into <output-file>."), QCoreApplication::translate("main", "output-file"));
    parser.addOption(outputFileOption);
    
    QCommandLineOption sourceDirectoryOption(QStringList() << "s" << "source-directory", QCoreApplication::translate("main", "Extract the morphometric measure of all images from the <source-directory>."), QCoreApplication::translate("main", "source-directory"));
    parser.addOption(sourceDirectoryOption);
    
    QCommandLineOption scaleValueOption(QStringList() << "c" << "scale", QCoreApplication::translate("main", "Extract the morphometric measures using the the <scale>. The default value is assumed to be 0.123636 nm/px."), QCoreApplication::translate("main", "scale"));
    parser.addOption(scaleValueOption);
    
    parser.process(app);
    
    if( !parser.isSet(outputFileOption) || !parser.isSet(sourceDirectoryOption) )
    {
        parser.showHelp();
        return 1;
    }
    
    float scale = 0.123636;
    if( parser.isSet(scaleValueOption) )
    {
        QString scaleString = parser.value(scaleValueOption);
        scale = scaleString.toFloat();
    }
    
    QString outputFile = parser.value(outputFileOption);
    QString sourceDirectory = parser.value(sourceDirectoryOption);

    ImageExtractor().measureImages(sourceDirectory, outputFile, QStringList() << "jpg" << "jpeg" << "tif" << "tiff" << "bmp", scale);
    
    return 0;
}
