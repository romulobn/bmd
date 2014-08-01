#include "imageprocessor.h"

#include <QDir>
#include <QDebug>

ImageProcessor::ImageProcessor(unsigned char options)
{
    optionsFlag = options;
}

void ImageProcessor::processImages(const QString &srcDir, const QString &destDir, const QString &filter, const int nerve, const int pipeline)
{
    Q_ASSERT(QDir(srcDir).exists() && QDir(destDir).exists());
    QStringList fileList = getFileList(srcDir, filter);
    QString fileName;
    foreach(fileName, fileList)
    {
        QStringList tempString = fileName.split("/");
        QString outputFileName = tempString.last();

        processImage(srcDir + "/" + fileName, destDir + outputFileName, nerve, pipeline);

    }
}

void ImageProcessor::processImage(const QString &srcImgPath, const QString &destImgPath, const int nerve, const int pipeline)
{
    cv::Mat srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_COLOR);
    Q_ASSERT(srcImg.data);

    pipelineChosen = pipeline;

    switch (nerve) {
    case Laryngeal:
        clusterNumber = 4;
        areaToClose = 20;
        areaToOpen = 20;
        eleSize = 10;
        threshSize = 19;
        learningRate = 0.005;
        break;
    case Vestibulochoclear:
        clusterNumber = 4;
        areaToClose = 10;
        areaToOpen = 10;
        eleSize = 10;
        threshSize = 19;
        learningRate = 0.005;
        break;
    case Sural:
        clusterNumber = 4;
        areaToClose = 10;
        areaToOpen = 10;
        eleSize = 10;
        threshSize = 19;
        learningRate = 0.005;
        break;
    default:
        clusterNumber = 4;
        areaToClose = 10;
        areaToOpen = 10;
        eleSize = 10;
        threshSize = 19;
        learningRate = 0.005;
        break;
    }

    cv::Mat myelinImg = segmentMyelinSheaths(srcImg);
    cv::Mat filteredMyelinImg = removeMinorNoise(myelinImg);
    cv::Mat kumarImg = applyKumar(filteredMyelinImg);
    cv::Mat filteredKumarImg = removeMajorNoise(kumarImg);


    if ( (optionsFlag & SaveSteps) == SaveSteps )
    {
        QString path = destImgPath;

        path.insert(destImgPath.indexOf("."), "_myelin");
        cv::imwrite(path.toStdString(), myelinImg);

        path.replace("_myelin", "_filteredMyelin");
        cv::imwrite(path.toStdString(), filteredMyelinImg);

        path.replace("_filteredMyelin", "_kumar");
        cv::imwrite(path.toStdString(), kumarImg);

        path.replace("_kumar", "_filteredKumar");
        cv::imwrite(path.toStdString(), filteredKumarImg);
    }

    if ( (optionsFlag & SaveFinalImage) == SaveFinalImage)
        cv::imwrite(destImgPath.toStdString(), caib::morphNeg(filteredKumarImg));
}

QStringList ImageProcessor::getFileList(const QString &srcDir, const QString &filter)
{
    QDir dir(srcDir);

    QStringList fileList = dir.entryList(), outputList;
    QString fileName;
    foreach(fileName, fileList)
    {
        if(fileName.endsWith( "." + filter))
        {
           outputList.append(fileName);
        }
    }

    return outputList;
}

cv::Mat ImageProcessor::segmentMyelinSheaths(const cv::Mat &input)
{
    cv::Mat output = cv::Mat::zeros(input.size(), input.type());

    if (pipelineChosen == Color)
    {
        cv::Mat labels = caib::clis(input, learningRate, clusterNumber), temp = caib::paintLabels(labels);
        int cluster = -1, n = clusterNumber;

        while (true)
        {
            cv::namedWindow("Clusters", cv::WINDOW_AUTOSIZE);
            cv::imshow("Clusters", temp);
            cv::namedWindow("Bin", cv::WINDOW_AUTOSIZE);
            cv::imshow("Bin", output);
            char key = (char) cv::waitKey();

            if ( key == 'r' )
            {
                qDebug() << "Enter number of clusters: ";
                char c = (char) cv::waitKey();
                n = atoi(&c);

                qDebug() << n;

                labels = caib::clis(input, learningRate, n);
                temp = caib::paintLabels(labels);
            }
            else if ( key == 'c' )
            {
                qDebug() << "Enter cluster: ";
                char c = (char) cv::waitKey();
                cluster = atoi(&c);

                qDebug() << cluster;

                if ( cluster <= clusterNumber && cluster > 0)
                {
                    output = caib::paintLabel(labels, cluster-1, cv::Scalar(255,255,255));
                }
                else
                {
                    qDebug() << "Invalid cluster!";
                }
            }
            else if ( ( key == ' ' || key == 'w' ) && cluster != -1 )
            {
                break;
            }
        }
    } else if (pipelineChosen == Morph)
    {
        cv::Mat temp;
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::Mat closerecth = caib::morphNeg(caib::morphCloserecth(temp, caib::morphSebox(eleSize)));
        cv::adaptiveThreshold(closerecth, output, 255, CV_ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, threshSize, 5);
    }

    return output;
}

cv::Mat ImageProcessor::removeMinorNoise(const cv::Mat &input)
{
    cv::Mat temp;
    if(pipelineChosen == Morph)
        temp = input.clone();
    else if(pipelineChosen == Color)
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
    cv::Mat binary = caib::morphBinary(temp, 100);
    cv::Mat areaOpen = caib::morphAreaopen(binary, areaToOpen);
    cv::Mat output = caib::morphAreaclose(areaOpen, areaToClose);

    return output;
}

cv::Mat ImageProcessor::applyKumar(const cv::Mat &input)
{
    return caib::kumar(input);
}

cv::Mat ImageProcessor::removeMajorNoise(const cv::Mat &input)
{
    cv::Mat edgeoff= caib::morphEdgeoff(input);
    cv::Mat onlyHoles = caib::morphInfrec(caib::morphGradm(caib::morphClohole(caib::morphClohole(edgeoff) - edgeoff)), edgeoff);

    return onlyHoles;
}
