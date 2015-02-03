#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "../src/imageprocessor.h"

int main(int argc, char *argv[])
{
    ImageProcessor imp;

    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 5)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    QStringList filters;
    int nerve, pipeline;
    filters << "jpg" << "jpeg" << "tif" << "tiff" << "bmp";


    if(args[3] == "lar")
        nerve = ImageProcessor::Laryngeal;
    if(args[3] == "ves")
        nerve = ImageProcessor::Vestibulochoclear;
    if(args[3] == "sur")
        nerve = ImageProcessor::Sural;
    if(args[3] == "vag")
        nerve = ImageProcessor::Vagus;
    if(args[3] == "fre")
        nerve = ImageProcessor::Frenic;

    if(args[4] == "color")
        pipeline = ImageProcessor::Color;
    if(args[4] == "morph")
        pipeline = ImageProcessor::Morph;

    imp.processImages(args[1], args[2], filters, nerve, pipeline);
}
