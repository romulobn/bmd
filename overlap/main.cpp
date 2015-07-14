#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <caib/imgproc.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("image-overlaper");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Overlap two images");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption outputFileOption(QStringList() << "o" << "output-file", QCoreApplication::translate("main", "Save the overlaped image to the <output-file>."), QCoreApplication::translate("main", "output-file"));
    parser.addOption(outputFileOption);
    
    QCommandLineOption sourceFile1Option(QStringList() << "s1" << "source-file-1", QCoreApplication::translate("main", "Overlap image from the <source-file-1>."), QCoreApplication::translate("main", "source-file-1"));
    parser.addOption(sourceFile1Option);
    
    QCommandLineOption sourceFile2Option(QStringList() << "n" << "source-file-2", QCoreApplication::translate("main", "Overlap image from the <source-file-2>."), QCoreApplication::translate("main", "source-file-2"));
    parser.addOption(sourceFile2Option);
    
    parser.process(app);
    
    if(!parser.isSet(outputFileOption) || !parser.isSet(sourceFile1Option) || !parser.isSet(sourceFile2Option))
    {
        parser.showHelp();
        return 1;
    }
    
    QString outputFile = parser.value(outputFileOption);
    QString sourceFile1 = parser.value(sourceFile1Option);
    QString sourceFile2 = parser.value(sourceFile2Option);

    cv::Mat img1 = cv::imread(sourceFile1.toStdString(), cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread(sourceFile2.toStdString(), cv::IMREAD_COLOR);

    img1 = caib::morphBinary(img1,100);
    cv::Mat labels = cv::Mat(img1.size(), cv::DataType<int>::type);
    img1.convertTo(labels, labels.type());

    cv::Mat overlap = caib::drawLabelsContours(img2, labels, cv::Scalar(0,0,255));
    cv::imshow("overlap", overlap);
    cv::imwrite(outputFile.toStdString(), overlap);
    
    return 0;
}
