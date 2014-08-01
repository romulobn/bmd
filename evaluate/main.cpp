#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "../src/imageevaluator.h"

int main(int argc, char *argv[])
{
    ImageEvaluator ime;

    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 6)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    ime.evaluateImages(args[1], args[2], args[3], args[4], args[5]);
}
