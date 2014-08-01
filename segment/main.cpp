#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "../src/imageprocessor.h"

int main(int argc, char *argv[])
{
    ImageProcessor imp (ImageProcessor::SaveSteps || ImageProcessor::SaveFinalImage);

    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 5)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    if ( args[4] == "lar")
       imp.processImages(args[1], args[2], args[3], ImageProcessor::Laryngeal, ImageProcessor::Morph);

    if ( args[4] == "ves")
        imp.processImages(args[1], args[2], args[3], ImageProcessor::Vestibulochoclear, ImageProcessor::Morph);

    if ( args[4] == "sur")
        imp.processImages(args[1], args[2], args[3], ImageProcessor::Sural, ImageProcessor::Morph);
}
