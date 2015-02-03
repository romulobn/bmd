#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "../src/imageevaluator.h"

int main(int argc, char *argv[])
{
    ImageEvaluator ime;

    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 5)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    QStringList filters;
    filters << "jpg" << "jpeg" << "tif" << "tiff" << "bmp";

    if (args[4] == "seg") {
        ime.evaluateImages(args[1], args[2], filters, args[3]);
    } else if (args[4] == "img") {
        ime.measureImagesIntesityValues(args[1], args[2], filters, args[3]);
    } else if(args[4] == "pxl") {
        ime.measureImagesPixelIntesityValues(args[1], args[2], filters, args[3]);
    }
}
