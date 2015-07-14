#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDir>

#include "../src/imageprocessor.h"

int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("fiber-image-processor");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Myelinated fiber image processor");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption targetDirectoryOption(QStringList() << "t" << "target-directory", QCoreApplication::translate("main", "Save all processed files into <target-directory>."), QCoreApplication::translate("main", "target-directory"));
    parser.addOption(targetDirectoryOption);
    
    QCommandLineOption sourceDirectoryOption(QStringList() << "s" << "source-directory", QCoreApplication::translate("main", "Process all images from the <source-directory>."), QCoreApplication::translate("main", "source-directory"));
    parser.addOption(sourceDirectoryOption);
    
    QCommandLineOption nerveTypeOption(QStringList() << "n" << "nerve-type", QCoreApplication::translate("main", "Process as the <nerve-type>."), QCoreApplication::translate("main", "nerve-type"));
    parser.addOption(nerveTypeOption);
    
    QCommandLineOption pipelineTypeOption(QStringList() << "p" << "pipeline-type", QCoreApplication::translate("main", "Process using the <pipeline-type> pipeline."), QCoreApplication::translate("main", "pipeline-type"));
    parser.addOption(pipelineTypeOption);
    
    parser.process(app);
    
    if(!parser.isSet(targetDirectoryOption) || !parser.isSet(sourceDirectoryOption) || !parser.isSet(nerveTypeOption) || !parser.isSet(pipelineTypeOption)) {
        parser.showHelp();
        return -1;
    }
    
    QString targetDirectory = parser.value(targetDirectoryOption);
    QString sourceDirectory = parser.value(sourceDirectoryOption);
    QString nerveType = parser.value(nerveTypeOption);
    QString pipelineType = parser.value(pipelineTypeOption);
    
    int nerveEnum, pipelineEnum;
    
    if(nerveType == "lar")
        nerveEnum = ImageProcessor::Laryngeal;
    if(nerveType == "ves")
        nerveEnum = ImageProcessor::Vestibulochoclear;
    if(nerveType == "sur")
        nerveEnum = ImageProcessor::Sural;
    if(nerveType == "vag")
        nerveEnum = ImageProcessor::Vagus;
    if(nerveType == "fre")
        nerveEnum = ImageProcessor::Frenic;
    
    if(pipelineType == "color")
        pipelineEnum = ImageProcessor::Color;
    if(pipelineType == "morph")
        pipelineEnum = ImageProcessor::Morph;

    ImageProcessor().processImages(sourceDirectory, targetDirectory, QStringList() << "jpg" << "jpeg" << "tif" << "tiff" << "bmp", nerveEnum, pipelineEnum);
    
    return 0;
}
