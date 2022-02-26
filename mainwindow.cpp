#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonDisplayImage_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::cvtColor(original , original , cv::COLOR_BGR2RGB);
    ui->displayOriginalImage->setPixmap(QPixmap::fromImage(QImage(original.data, original.cols, original.rows, original.step, QImage::Format_RGB888)));
}

void MainWindow::on_pushButtonCopyImage_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat copied = cv::imread(extension.toStdString());
    if (copied.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::cvtColor(copied, copied, cv::COLOR_BGR2RGB);
    ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(copied.data, copied.cols, copied.rows, copied.step, QImage::Format_RGB888)));
}

void MainWindow::on_pushButtonInvertVertical_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    for(int row = 0; row < modified.size().height / 2; row++)
    {
        for(int col = 0; col < modified.size().width; col++)
        {
            modified.at<cv::Vec3b>(row, col) = original.at<cv::Vec3b>(modified.size().height - 1 - row, col);
            modified.at<cv::Vec3b>(modified.size().height - 1 - row, col) = original.at<cv::Vec3b>(row, col);
        }
    }

    cv::cvtColor(modified , modified , cv::COLOR_BGR2RGB);
    ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
}

void MainWindow::on_pushButtonInvertHorizontal_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    for(int row = 0; row < modified.size().height; row++)
    {
        for(int col = 0; col < modified.size().width / 2; col++)
        {
            modified.at<cv::Vec3b>(row, col) = original.at<cv::Vec3b>(row, modified.size().width - 1 - col);
            modified.at<cv::Vec3b>(row, modified.size().width - 1 - col) = original.at<cv::Vec3b>(row, col);
        }
    }

    cv::cvtColor(modified , modified , cv::COLOR_BGR2RGB);
    ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
}

void MainWindow::on_pushButtonConvertGrayscale_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    for(int r = 0; r < original.rows; r++)
    {
        for(int c = 0; c < original.cols; c++)
        {
            float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
            modified.at<cv::Vec3b>(r, c)[0] = gray;
            modified.at<cv::Vec3b>(r, c)[1] = gray;
            modified.at<cv::Vec3b>(r, c)[2] = gray;
        }
    }

    cv::cvtColor(modified , modified , cv::COLOR_BGR2RGB);
    ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
}

void MainWindow::on_pushButtonSaveNewImage_clicked()
{
    QString filepath;
    filepath = ui->lineEditSave->text();

    QImage newImage;
    const QPixmap *pixMap = ui->displayNewImage->pixmap();

    if (pixMap)
    {
        newImage = pixMap->toImage();
    }

    newImage.save(filepath);
}

void MainWindow::on_pushButtonQuantizeImage_clicked()
{
    QString number;
    number = ui->lineEditQuantize->text();
    int n = number.toInt();

    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    for(int r = 0; r < original.rows; r++)
    {
        for(int c = 0; c < original.cols; c++)
        {
            float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
            modified.at<cv::Vec3b>(r, c)[0] = gray;
            modified.at<cv::Vec3b>(r, c)[1] = gray;
            modified.at<cv::Vec3b>(r, c)[2] = gray;
        }
    }
    cv::cvtColor(modified, modified, cv::COLOR_BGR2GRAY);

    double t1, t2;
    cv::minMaxLoc(modified, &t1, &t2);

    int tam_int = t2 - t1 + 1;

    if (n >= tam_int)
    {
        cout << "Quntization is not necessary." << endl;
        cout << "Displaying grayscale image." << endl;
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_Grayscale8)));
    }

    if (n < tam_int)
    {
        float tb = tam_int / n;

        for(int i = 0; i < n; i++)
        {
            float min_tb = (t1 - 0.5) + tb * i;
            float max_tb = (t1 - 0.5) + tb * (i+1);

            for(int r = 0; r < modified.rows; r++)
            {
                for(int c = 0; c < modified.cols; c++)
                {
                    float pixelVal = modified.at<uint8_t>(r, c) * 1;

                    if((pixelVal >= min_tb) && (pixelVal <= max_tb))
                    {
                        float pixelNew = min_tb + (max_tb - min_tb) / 2;
                        modified.at<uint8_t>(r, c) = (int)pixelNew;
                    }
                }
            }
        }
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_Grayscale8)));
    }
}

void MainWindow::on_pushButtonHistogram_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (original.channels() == 3)
    {
        cv::Mat modified = cv::imread(extension.toStdString());
        if (modified.empty())
        {
            cout << "Image could not be found." << endl;
        }

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
                modified.at<cv::Vec3b>(r, c)[0] = gray;
                modified.at<cv::Vec3b>(r, c)[1] = gray;
                modified.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2GRAY);

        // Creates array to store histogram values
        int histogram[256];

        // Initializes all intensities values to zero
        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
        }

        // Calculates the number of pixels for each intensity value
        for(int r = 0; r < modified.rows; r++)
        {
            for(int c = 0; c < modified.cols; c++)
            {
                histogram[(int)modified.at<uchar>(r, c)]++;
            }
        }

        // Draws the histogram
        int hist_w = 512;
        int hist_h = 400;
        int bin_w = cvRound((double)hist_w/256);

        cv::Mat histImage = cv::imread("/home/ubuntu/x.jpg");
        //cout << histImage.size().width << " " << histImage.size().height << endl;
        cv::cvtColor(histImage, histImage, cv::COLOR_BGR2GRAY);

        // Finds the maximum intensity element from histogram
        int max = histogram[0];
        for(int i = 1; i < 256; i++)
        {
            if(max < histogram[i])
            {
                max = histogram[i];
            }
        }

        // Normalizes the histogram between 0 and histImage.rows
        for(int i = 0; i < 255; i++)
        {
            histogram[i] = ((double)histogram[i]/max) * histImage.rows;
            //cout << histogram[i] << endl;
        }

        // draw the intensity line for histogram
        for(int i = 0; i < 255; i++)
        {
            cv::line(histImage, cv::Point(bin_w*(i), hist_h - histogram[i]), cv::Point(bin_w*(i), hist_h), cv::Scalar(0, 0, 0), 1, 8, 0);
        }

        cout << "done" << endl;

        // display histogram
        cv::imshow("Intensity Histogram", histImage);
        cv::waitKey();
    }
}

void MainWindow::on_spinBoxBrightness_valueChanged(int arg1)
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    int brigthness = (int)arg1;
    // cout << brigthness << endl;

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (original.channels() == 3)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float pixelB = modified.at<cv::Vec3b>(r, c)[0] * 1;
                float pixelG = modified.at<cv::Vec3b>(r, c)[1] * 1;
                float pixelR = modified.at<cv::Vec3b>(r, c)[2] * 1;

                pixelB = pixelB + brigthness;
                pixelG = pixelG + brigthness;
                pixelR = pixelR + brigthness;

                if (pixelB < 0)
                {
                    pixelB = 0;
                }

                if (pixelB > 255)
                {
                    pixelB = 255;
                }

                if (pixelG < 0)
                {
                    pixelG = 0;
                }

                if (pixelG > 255)
                {
                    pixelG = 255;
                }

                if (pixelR < 0)
                {
                    pixelR = 0;
                }

                if (pixelR > 255)
                {
                    pixelR = 255;
                }

                modified.at<cv::Vec3b>(r, c)[0] = pixelB;
                modified.at<cv::Vec3b>(r, c)[1] = pixelG;
                modified.at<cv::Vec3b>(r, c)[2] = pixelR;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }

    else if (original.channels() == 1)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float pixel = original.at<uint8_t>(r, c) * 1;
                pixel = pixel + brigthness;

                if (pixel < 0)
                {
                    pixel = 0;
                }

                if (pixel > 255)
                {
                    pixel = 255;
                }

                original.at<uint8_t>(r, c) = pixel;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_spinBoxContrast_valueChanged(int arg1)
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    int contrast = (int)arg1;
    // cout << contrast << endl;

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (original.channels() == 3)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float pixelB = modified.at<cv::Vec3b>(r, c)[0] * 1;
                float pixelG = modified.at<cv::Vec3b>(r, c)[1] * 1;
                float pixelR = modified.at<cv::Vec3b>(r, c)[2] * 1;

                pixelB = pixelB * contrast;
                pixelG = pixelG * contrast;
                pixelR = pixelR * contrast;

                if (pixelB > 255)
                {
                    pixelB = 255;
                }

                if (pixelG > 255)
                {
                    pixelG = 255;
                }

                if (pixelR > 255)
                {
                    pixelR = 255;
                }

                modified.at<cv::Vec3b>(r, c)[0] = pixelB;
                modified.at<cv::Vec3b>(r, c)[1] = pixelG;
                modified.at<cv::Vec3b>(r, c)[2] = pixelR;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }

    else if (original.channels() == 1)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float pixel = original.at<uint8_t>(r, c) * 1;
                pixel = pixel * contrast;

                if (pixel < 0)
                {
                    pixel = 0;
                }

                if (pixel > 255)
                {
                    pixel = 255;
                }

                original.at<uint8_t>(r, c) = pixel;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_pushButtonNegative_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (original.channels() == 3)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                modified.at<cv::Vec3b>(r, c)[0] = 255 - modified.at<cv::Vec3b>(r, c)[0];
                modified.at<cv::Vec3b>(r, c)[1] = 255 - modified.at<cv::Vec3b>(r, c)[1];
                modified.at<cv::Vec3b>(r, c)[2] = 255 - modified.at<cv::Vec3b>(r, c)[2];
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }

    else if (original.channels() == 1)
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                original.at<uint8_t>(r, c) = 255 - original.at<uint8_t>(r, c);
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_pushButtonConvolution_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = cv::imread(extension.toStdString());
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat filtered = cv::imread(extension.toStdString());
    if (filtered.empty())
    {
        cout << "Image could not be found." << endl;
    }

    QString kernelName;
    kernelName = ui->lineEditGetKernelName->text();

    QString vec00;
    QString vec01;
    QString vec02;
    QString vec10;
    QString vec11;
    QString vec12;
    QString vec20;
    QString vec21;
    QString vec22;

    vec00 = ui->lineEdit_filter00->text();
    vec01 = ui->lineEdit_filter01->text();
    vec02 = ui->lineEdit_filter02->text();
    vec10 = ui->lineEdit_filter10->text();
    vec11 = ui->lineEdit_filter11->text();
    vec12 = ui->lineEdit_filter12->text();
    vec20 = ui->lineEdit_filter20->text();
    vec21 = ui->lineEdit_filter21->text();
    vec22 = ui->lineEdit_filter22->text();

    float n00 = vec00.toFloat();
    float n01 = vec01.toFloat();
    float n02 = vec02.toFloat();
    float n10 = vec10.toFloat();
    float n11 = vec11.toFloat();
    float n12 = vec12.toFloat();
    float n20 = vec20.toFloat();
    float n21 = vec21.toFloat();
    float n22 = vec22.toFloat();

    float kernel[3][3] = {{n00, n01, n02}, {n10, n11, n12}, {n20, n21, n22}};

    if(kernelName == "Gaussian")
    {
        if(original.channels() == 3)
        {
            for(int y = 1; y < original.rows - 1; y++)
            {
                for(int x = 1; x < original.cols - 1; x++)
                {
                    float sumB = 0;
                    float sumG = 0;
                    float sumR = 0;

                    for(int k = -1; k <= 1; k++)
                    {
                        for(int j = -1; j <= 1; j++)
                        {
                            sumB = sumB + kernel[j+1][k+1] * modified.at<cv::Vec3b>(y - j, x - k)[0];
                            sumG = sumG + kernel[j+1][k+1] * modified.at<cv::Vec3b>(y - j, x - k)[1];
                            sumR = sumR + kernel[j+1][k+1] * modified.at<cv::Vec3b>(y - j, x - k)[2];
                        }
                    }

                    if (sumB < 0)
                    {
                        sumB = 0;
                    }

                    if (sumB > 255)
                    {
                        sumB = 255;
                    }

                    if (sumG < 0)
                    {
                        sumG = 0;
                    }

                    if (sumG > 255)
                    {
                        sumG = 255;
                    }

                    if (sumR < 0)
                    {
                        sumR = 0;
                    }

                    if (sumR > 255)
                    {
                        sumR = 255;
                    }

                    filtered.at<cv::Vec3b>(y, x)[0] = sumB;
                    filtered.at<cv::Vec3b>(y, x)[1] = sumG;
                    filtered.at<cv::Vec3b>(y, x)[2] = sumR;
                }
            }
            cv::cvtColor(filtered, filtered, cv::COLOR_BGR2RGB);
            ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(filtered.data, filtered.cols, filtered.rows, filtered.step, QImage::Format_RGB888)));
        }

        if(original.channels() == 1)
        {
            for(int y = 1; y < original.rows - 1; y++)
            {
                for(int x = 1; x < original.cols - 1; x++)
                {
                    float sum = 0;
                    for(int k = -1; k <= 1; k++)
                    {
                        for(int j = -1; j <= 1; j++)
                        {
                            sum = sum + kernel[j+1][k+1] * modified.at<uint8_t>(y - j, x - k);
                        }
                    }

                    if (sum < 0)
                    {
                        sum = 0;
                    }

                    if (sum > 255)
                    {
                        sum = 255;
                    }

                    filtered.at<uint8_t>(y, x) = sum;
                }
            }
            cv::cvtColor(filtered, filtered, cv::COLOR_BGR2RGB);
            ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(filtered.data, filtered.cols, filtered.rows, filtered.step, QImage::Format_RGB888)));
        }
    }

    else
    {
        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
                modified.at<cv::Vec3b>(r, c)[0] = gray;
                modified.at<cv::Vec3b>(r, c)[1] = gray;
                modified.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2GRAY);

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
                filtered.at<cv::Vec3b>(r, c)[0] = gray;
                filtered.at<cv::Vec3b>(r, c)[1] = gray;
                filtered.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(filtered, filtered, cv::COLOR_BGR2GRAY);

        //cout << modified.channels() << endl;
        //cout << original.channels() << endl;

        for(int y = 1; y < original.rows - 1; y++)
        {
            for(int x = 1; x < original.cols - 1; x++)
            {
                float sum = 0;
                for(int k = -1; k <= 1; k++)
                {
                    for(int j = -1; j <= 1; j++)
                    {
                        sum = sum + kernel[j+1][k+1] * modified.at<uint8_t>(y - j, x - k);
                    }
                }

                if(kernelName == "HighPass" || kernelName == "Laplacian")
                {
                    if (sum < 0)
                    {
                        sum = 0;
                    }

                    if (sum > 255)
                    {
                        sum = 255;
                    }
                }

                if(kernelName == "PrewittHy" || kernelName == "PrewittHx" || kernelName == "SobelHx" || kernelName == "SobelHy")
                {
                    sum = sum + 127;

                    if (sum < 0)
                    {
                        sum = 0;
                    }

                    if (sum > 255)
                    {
                        sum = 255;
                    }
                }

                filtered.at<uint8_t>(y, x) = sum;
            }
        }
        // cv::cvtColor(filtered, filtered, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(filtered.data, filtered.cols, filtered.rows, filtered.step, QImage::Format_Grayscale8)));
    }

    //cv::Mat test = filtered.clone();
    //cv::imshow("test", test);
    //cv::waitKey(0);

    //float laplacian[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}

void MainWindow::on_pushButtonRotateClockWise_clicked()
{
    QImage newImage;
    const QPixmap *pixMap = ui->displayNewImage->pixmap();

    if (pixMap)
    {
        newImage = pixMap->toImage();
    }

    newImage.save("/home/ubuntu/original.jpg");

    cv::Mat original = cv::imread("/home/ubuntu/original.jpg");
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    int new_width = original.size().height;
    int new_height = original.size().width;

    QImage image = QImage(new_width, new_height, QImage::Format_RGB888);
    image.fill(0);
    image.save("/home/ubuntu/clockwise.jpg");

    cv::Mat modified = cv::imread("/home/ubuntu/clockwise.jpg");
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (modified.channels() == 3)
    {
        for(int i = 0; i < original.cols; i++)
        {
            for(int j = 0; j < original.rows; j++)
            {
                modified.at<cv::Vec3b>(i, j)[0] = original.at<cv::Vec3b>(original.rows - 1 - j, i)[0];
                modified.at<cv::Vec3b>(i, j)[1] = original.at<cv::Vec3b>(original.rows - 1 - j, i)[1];
                modified.at<cv::Vec3b>(i, j)[2] = original.at<cv::Vec3b>(original.rows - 1 - j, i)[2];
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_pushButtonRotateAntiClockWise_clicked()
{
    QImage newImage;
    const QPixmap *pixMap = ui->displayNewImage->pixmap();

    if (pixMap)
    {
        newImage = pixMap->toImage();
    }

    newImage.save("/home/ubuntu/original.jpg");

    cv::Mat original = cv::imread("/home/ubuntu/original.jpg");
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    int new_width = original.size().height;
    int new_height = original.size().width;

    QImage image = QImage(new_width, new_height, QImage::Format_RGB888);
    image.fill(0);
    image.save("/home/ubuntu/anticlockwise.jpg");

    cv::Mat modified = cv::imread("/home/ubuntu/anticlockwise.jpg");
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (modified.channels() == 3)
    {
        for(int i = 0; i < original.cols; i++)
        {
            for(int j = 0; j < original.rows; j++)
            {
                modified.at<cv::Vec3b>(i, j)[0] = original.at<cv::Vec3b>(j, original.cols - 1 - i)[0];
                modified.at<cv::Vec3b>(i, j)[1] = original.at<cv::Vec3b>(j, original.cols - 1 - i)[1];
                modified.at<cv::Vec3b>(i, j)[2] = original.at<cv::Vec3b>(j, original.cols - 1 - i)[2];
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_pushButtonZoomIn_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    int new_width = 2 * original.size().width - 1;
    int new_height = 2 * original.size().height - 1;

    QImage image = QImage(new_width, new_height, QImage::Format_RGB888);
    image.fill(0);
    image.save("/home/ubuntu/zoomin.jpg");

    cv::Mat modified = cv::imread("/home/ubuntu/zoomin.jpg");
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    if (modified.channels() == 3)
    {
        int i = 0;

        for(int r = 0; r < modified.rows; r = r + 2)
        {
            int j = 0;
            for(int c = 0; c < modified.cols; c = c + 2)
            {
                modified.at<cv::Vec3b>(r, c)[0] = original.at<cv::Vec3b>(i, j)[0];
                modified.at<cv::Vec3b>(r, c)[1] = original.at<cv::Vec3b>(i, j)[1];
                modified.at<cv::Vec3b>(r, c)[2] = original.at<cv::Vec3b>(i, j)[2];

                j = j + 1;
            }
            i = i + 1;
        }

        cv::Mat modified1 = modified.clone();
        // cv::imshow("mod", modified);

        for(int r = 0; r < modified.rows; r = r + 2)
        {
            for(int c = 1; c <= modified.cols; c = c + 2)
            {
                modified1.at<cv::Vec3b>(r, c)[0] = modified.at<cv::Vec3b>(r, c - 1)[0] + (modified.at<cv::Vec3b>(r, c + 1)[0] - modified.at<cv::Vec3b>(r, c - 1)[0]) / 2;
                modified1.at<cv::Vec3b>(r, c)[1] = modified.at<cv::Vec3b>(r, c - 1)[1] + (modified.at<cv::Vec3b>(r, c + 1)[1] - modified.at<cv::Vec3b>(r, c - 1)[1]) / 2;
                modified1.at<cv::Vec3b>(r, c)[2] = modified.at<cv::Vec3b>(r, c - 1)[2] + (modified.at<cv::Vec3b>(r, c + 1)[2] - modified.at<cv::Vec3b>(r, c - 1)[2]) / 2;
            }
        }

        // cv::imshow("mod1", modified1);

        cv::Mat modified2 = modified1.clone();

        for(int r = 1; r <= modified1.rows; r = r + 2)
        {
            for(int c = 0; c < modified1.cols; c = c + 1)
            {
                modified2.at<cv::Vec3b>(r, c)[0] = modified1.at<cv::Vec3b>(r - 1, c)[0] + (modified1.at<cv::Vec3b>(r + 1, c)[0] - modified1.at<cv::Vec3b>(r - 1, c)[0]) / 2;
                modified2.at<cv::Vec3b>(r, c)[1] = modified1.at<cv::Vec3b>(r - 1, c)[1] + (modified1.at<cv::Vec3b>(r + 1, c)[1] - modified1.at<cv::Vec3b>(r - 1, c)[1]) / 2;
                modified2.at<cv::Vec3b>(r, c)[2] = modified1.at<cv::Vec3b>(r - 1, c)[2] + (modified1.at<cv::Vec3b>(r + 1, c)[2] - modified1.at<cv::Vec3b>(r - 1, c)[2]) / 2;
            }
        }

        cv::imshow("Zoom In", modified2);
        cv::waitKey(0);
    }
}

void MainWindow::on_pushButtonZoomOut_clicked()
{

}
