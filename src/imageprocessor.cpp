#include "imageprocessor.h"

#include <QDir>
#include <QDebug>
#include <QList>

ImageProcessor::ImageProcessor(unsigned char options)
{
    optionsFlag = options;
}

void ImageProcessor::processImages(const QString &srcDir, const QString &destDir, const QStringList &filters, const int nerve, const int pipeline)
{
    Q_ASSERT(QDir(srcDir).exists() && QDir(destDir).exists());
    QStringList fileList = getFileList(srcDir, filters);
    QString fileName;
    foreach(fileName, fileList)
    {
        QStringList tempString = fileName.split("/");
        QString outputFileName = tempString.last();

        qDebug() << fileName;
        processImage(srcDir + "/" + fileName, destDir + "/" + outputFileName, nerve, pipeline);
    }
}

void ImageProcessor::processImage(const QString &srcImgPath, const QString &destImgPath, const int nerve, const int pipeline)
{
    cv::Mat srcImg;
    try {
        srcImg = cv::imread(srcImgPath.toStdString(), cv::IMREAD_COLOR);
    } catch ( cv::Exception &e) {
        qDebug() << e.what();
        exit(1);
    }
    
    Q_ASSERT(srcImg.data);

    pipelineChosen = pipeline;

    switch (nerve) {
    case Laryngeal:
        clusterNumber = 4;
        eleToClose = 2;
        eleToOpen = 2;
        eleSize = 18;
        threshSize = 19;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(0, 0, 0, 0, 0, 0);
        break;
    case Vestibulochoclear:
        clusterNumber = 5;
        eleToClose = 1;
        eleToOpen = 1;
        eleSize = 10;
        threshSize = 25;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(0, 0, 0, 0, 0, 0);
        break;
    case Sural:
        clusterNumber = 4;
        eleToClose = 1;
        eleToOpen = 1;
        eleSize = 10;
        threshSize = 25;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(0, 0, 0, 0, 0, 0);
        break;
    case Frenic:
        clusterNumber = 3;
        eleToClose = 1;
        eleToOpen = 1;
        eleSize = 10;
        threshSize = 25;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(4.27530502/100, 0.036062041, 0.030824848, 0.0414256, 0.080060492, 0.038893232);
        break;
    case Vagus:
        clusterNumber = 3;
        eleToClose = 1;
        eleToOpen = 1;
        eleSize = 12;
        threshSize = 19;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(0, 0, 0, 0, 0, 0);
        break;
    default:
        clusterNumber = 4;
        eleToClose = 1;
        eleToOpen = 1;
        eleSize = 10;
        threshSize = 19;
        learningRate = 0.005;
        closestCenter = cv::Vec6f(0, 0, 0, 0, 0, 0);
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
        cv::imwrite(destImgPath.split(".").first().append(".bmp").toStdString(), caib::morphNeg(filteredKumarImg));
}

QStringList ImageProcessor::getFileList(const QString &srcDir, const QStringList &filters)
{
    QDir dir(srcDir);

    QStringList fileList = dir.entryList(), outputList;
    QString fileName;
    foreach(fileName, fileList)
    {
        foreach(QString filter, filters) {
            if(fileName.endsWith( "." + filter, Qt::CaseInsensitive))
            {
               outputList.append(fileName);
            }
        }
    }

    return outputList;
}

cv::Mat ImageProcessor::segmentMyelinSheaths(const cv::Mat &input)
{
    cv::Mat output = cv::Mat::zeros(input.size(), input.type());

    if (pipelineChosen == Color)
    {
        cv::Mat bgr_img = input.clone();
        bgr_img.convertTo(bgr_img, cv::DataType<cv::Vec3f>::type, 1./255);
        cv::Mat luv_img, xyz_img;
        cv::cvtColor(bgr_img, luv_img, cv::COLOR_BGR2Luv);
        cv::cvtColor(bgr_img, xyz_img, cv::COLOR_BGR2XYZ);
        cv::Mat final_img = cv::Mat(input.size(), cv::DataType<cv::Vec6f>::type);
        for (int x=0; x<input.cols; x++) {
            for (int y=0; y<input.rows; y++) {
                final_img.at<cv::Vec6f>(cv::Point(x,y)) = cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0]/100, xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
                //final_img.at<cv::Vec6f>(cv::Point(x,y)) = cv::Vec6f(bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);

            }
        }

        cv::Mat labels = caib::clis(final_img, learningRate, clusterNumber), temp = caib::paintLabels(labels);
        std::vector<cv::Vec6f> centroids = std::vector<cv::Vec6f>(clusterNumber);
        std::vector<cv::Vec6f> var = std::vector<cv::Vec6f>(clusterNumber);
        std::vector<float> counts = std::vector<float>(clusterNumber);
        
        for (int i = 0; i < clusterNumber; i++) {
            centroids[i] = cv::Vec6f(0,0,0,0,0,0);
            var[i] = cv::Vec6f(0,0,0,0,0,0);
            counts[i] = 0;
        }
        
        for (int x = 0; x < final_img.cols; x++) {
            for(int y = 0; y < final_img.rows; y++) {
                centroids[labels.at<int>( cv::Point(x,y) )] += cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0]/100, xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
                //centroids[labels.at<int>( cv::Point(x,y) )] += cv::Vec6f(bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]);
                counts[labels.at<int>( cv::Point(x,y) )]++;
            }
        }
        
        for (int i = 0; i < clusterNumber; i++) {
            centroids[i] /= final_img.rows * final_img.cols;
        }
        
        for (int x = 0; x < final_img.cols; x++) {
            for(int y = 0; y < final_img.rows; y++) {
                cv::Vec6f temp;
                cv::pow(cv::Vec6f(luv_img.at<cv::Vec3f>(cv::Point(x,y))[0]/100, xyz_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[0], xyz_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]) - centroids[labels.at<int>( cv::Point(x,y) )], 2, temp);
                //cv::pow(cv::Vec6f(bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[1], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[0], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2], bgr_img.at<cv::Vec3f>(cv::Point(x,y))[2]) - centroids[labels.at<int>( cv::Point(x,y) )], 2, temp);
                var[labels.at<int>( cv::Point(x,y) )] += temp;
            }
        }
        
        for (int i = 0; i < clusterNumber; i++) {
            var[i] /= (final_img.rows * final_img.cols) - 1;
        }
        
        int min_idx = -1;
        float min_dist = MAXFLOAT;
        
        for (int i = 0; i < clusterNumber; i++) {
            float dist = 0;
            for (int j = 0; j < 6; j++) {
                dist += powf(centroids[i][j] - closestCenter[j], 2)*var[i][j];
            }
            
            dist = (sqrtf(dist)/ (counts[i]/(final_img.cols*final_img.rows)) );
            if (min_dist > dist) {
                min_idx = i;
                min_dist = dist;
            }
        }
        
        output = caib::paintLabel(labels, min_idx, cv::Scalar(255,255,255));
        
        /*
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

                labels = caib::clis(final_img, learningRate, n);
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
        }*/
    } else if (pipelineChosen == Morph)
    {
        cv::Mat temp;
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::Mat closerecth = caib::morphNeg(caib::morphCloserecth(temp, caib::morphSebox(eleSize), caib::morphSebox(eleSize)));
        cv::adaptiveThreshold(closerecth, output, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, threshSize, 5);
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
    cv::Mat output = caib::morphCloserec(caib::morphOpenrec(binary, caib::morphSebox(eleToOpen)), caib::morphSebox(eleToClose));
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
