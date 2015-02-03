#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "../src/imageextractor.h"

const float scale = 0.123636;

int main(int argc, char *argv[])
{
    ImageExtractor ime;
    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 3)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    QStringList filters;
    filters << "jpg" << "jpeg" << "tif" << "tiff" << "bmp";

    ime.measureImages(args[1], args[2], filters, scale);
}
