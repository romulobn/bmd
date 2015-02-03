#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QDebug>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <caib/imgproc.h>

int main(int argc, char *argv[])
{
    QStringList args;

    for(int i = 0; i < argc; i++)
        args.append(argv[i]);

    if (args.size() < 4)
    {
        qDebug() << "Error not enough arguments!";
        exit(1);
    }

    cv::Mat img1 = cv::imread(args[1].toStdString(), cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread(args[2].toStdString(), cv::IMREAD_COLOR);

    img1 = caib::morphBinary(img1,100);
    cv::Mat labels = cv::Mat(img1.size(), cv::DataType<int>::type);
    img1.convertTo(labels, labels.type());

    cv::Mat overlap = caib::drawLabelsContours(img2, labels, cv::Scalar(0,0,255));
    cv::imshow("overlap", overlap);
    cv::imwrite(args[3].toStdString(), overlap);
    cv::waitKey();


}
