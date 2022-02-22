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

        // allcoate memory for no of pixels for each intensity value
        int histogram[256];

        // initialize all intensity values to 0
        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
        }

        // calculate the no of pixels for each intensity values
        for(int r = 0; r < modified.rows; r++)
        {
            for(int c = 0; c < modified.cols; c++)
            {
                histogram[(int)modified.at<uchar>(r, c)]++;
            }
        }

        //histogram values
        //for(int i = 0; i < 256; i++)
        //{
        //    cout << histogram[i] << endl;
        //}

        // draw the histograms
        int hist_w = 512;
        int hist_h = 400;
        int bin_w = cvRound((double)hist_w/256);

        cv::Mat histImage = cv::imread("/home/ubuntu/x.jpg");
        //cout << histImage.size().width << " " << histImage.size().height << endl;
        cv::cvtColor(histImage, histImage, cv::COLOR_BGR2GRAY);

        // find the maximum intensity element from histogram
        int max = histogram[0];
        for(int i = 1; i < 256; i++)
        {
            if(max < histogram[i])
            {
                max = histogram[i];
            }
        }

        // normalize the histogram between 0 and histImage.rows
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
