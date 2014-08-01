#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "../src/imageextractor.h"

int main(int argc, char *argv[])
{
    ImageExtractor ime;
    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 5)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    ime.measureImages(args[1], args[2], args[3], args[4].toFloat());
}
