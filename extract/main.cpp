#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDir>

#include "../src/imageextractor.h"


int main(int argc, char *argv[])
{
    
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("fiber-image-processor");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Myelinated fiber image processor");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption targetDirectoryOption(QStringList() << "t" << "target-file", QCoreApplication::translate("main", "Save all extracted morphometric measures into <target-file>."), QCoreApplication::translate("main", "target-directory"));
    parser.addOption(targetDirectoryOption);
    
    QCommandLineOption sourceDirectoryOption(QStringList() << "s" << "source-directory", QCoreApplication::translate("main", "Extract the morphometric measure of all images from the <source-directory>."), QCoreApplication::translate("main", "source-directory"));
    parser.addOption(sourceDirectoryOption);
    
    QCommandLineOption scaleValueOption(QStringList() << "c" << "scale", QCoreApplication::translate("main", "Extract the morphometric measures using the the <scale>. The default value is assumed to be 0.123636 nm/px."), QCoreApplication::translate("main", "scale"));
    parser.addOption(sourceDirectoryOption);
    
    parser.process(app);
    
    if( !parser.isSet(targetDirectoryOption) || !parser.isSet(sourceDirectoryOption) )
    {
        parser.showHelp();
        return -1;
    }
    
    float scale = 0.123636;
    if( parser.isSet(scaleValueOption) )
    {
        QString scaleString = parser.value(scaleValueOption);
        scale = scaleString.toFloat();
    }
    
    QString targetDirectory = parser.value(targetDirectoryOption);
    QString sourceDirectory = parser.value(sourceDirectoryOption);

    ImageExtractor().measureImages(sourceDirectory, targetDirectory, QStringList() << "jpg" << "jpeg" << "tif" << "tiff" << "bmp", scale);
}
