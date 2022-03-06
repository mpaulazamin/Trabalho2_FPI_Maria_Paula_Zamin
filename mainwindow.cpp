#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

int getClosest(int val1, int val2, int target)
{
    if (target - val1 >= val2 - target)
    {
        return val2;
    }
    else
    {
        return val1;
    }
}

int findClosest(int arr[], int n, int target)
{
    // Corner cases
    if (target <= arr[0])
    {
        return arr[0];
    }
    if (target >= arr[n - 1])
    {
        return arr[n - 1];
    }

    // Doing binary search
    int i = 0, j = n, mid = 0;

    while (i < j)
    {
        mid = (i + j) / 2;

        if (arr[mid] == target)
        {
            return arr[mid];
        }

        // If target is less than array element, then search in left
        if (target < arr[mid])
        {
            // If target is greater than previous
            // to mid, return closest of two
            if (mid > 0 && target > arr[mid - 1])
            {
                return getClosest(arr[mid - 1], arr[mid], target);
            }

            // Repeat for left half
            j = mid;
        }

        // If target is greater than mid
        else
        {
            if (mid < n - 1 && target < arr[mid + 1])
            {
                return getClosest(arr[mid], arr[mid + 1], target);
            }
            // update i
            i = mid + 1;
        }
    }
    // Only single element left after search
    return arr[mid];
}

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
        cv::Mat modified = original.clone();

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

        int histogram[256];

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
        }

        for(int r = 0; r < modified.rows; r++)
        {
            for(int c = 0; c < modified.cols; c++)
            {
                histogram[(int)modified.at<uchar>(r, c)]++;
            }
        }

        int hist_width = 512;
        int hist_height = 400;
        int bin_w = cvRound((double) hist_width / 256);

        QImage image = QImage(hist_width, hist_height, QImage::Format_Grayscale8);
        image.fill(255);
        image.save("/home/ubuntu/histimage.jpg");

        cv::Mat histImage = cv::imread("/home/ubuntu/histimage.jpg");
        if (histImage .empty())
        {
            cout << "Image could not be found." << endl;
        }

        int max = histogram[0];
        for(int i = 1; i < 256; i++)
        {
            if(max < histogram[i])
            {
                max = histogram[i];
            }
        }

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = ((double)histogram[i]/max) * histImage.rows;
            cout << histogram[i] << endl;
        }

        cout << "done" << endl;

        for(int i = 0; i < 255; i++)
        {
             cv::line(histImage, cv::Point(bin_w*(i), hist_height), cv::Point(bin_w*(i), hist_height - histogram[i]), cv::Scalar(0,0,0), 1, 8, 0);
        }

        cout << "done" << endl;

        cv::imshow("Intensity Histogram", histImage);
        cv::waitKey();
    }

    if(original.channels() == 1)
    {
        cv::Mat modified = original.clone();

        int histogram[256];

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
        }

        for(int r = 0; r < modified.rows; r++)
        {
            for(int c = 0; c < modified.cols; c++)
            {
                histogram[(int)modified.at<uchar>(r, c)]++;
            }
        }

        int hist_width = 512;
        int hist_height = 400;
        int bin_w = cvRound((double) hist_width / 256);

        QImage image = QImage(hist_width, hist_height, QImage::Format_Grayscale8);
        image.fill(255);
        image.save("/home/ubuntu/histimage.jpg");

        cv::Mat histImage = cv::imread("/home/ubuntu/histimage.jpg");
        if (histImage .empty())
        {
            cout << "Image could not be found." << endl;
        }

        int max = histogram[0];
        for(int i = 1; i < 256; i++)
        {
            if(max < histogram[i])
            {
                max = histogram[i];
            }
        }

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = ((double)histogram[i]/max) * histImage.rows;
            cout << histogram[i] << endl;
        }

        for(int i = 0; i < 255; i++)
        {
              cv::line(histImage, cv::Point(bin_w*(i), hist_height), cv::Point(bin_w*(i), hist_height - histogram[i]), cv::Scalar(0,0,0), 1, 8, 0);
        }

        cv::imshow("Intensity Histogram", histImage);
        cv::waitKey();
    }
}

void MainWindow::on_pushButtonHistogramEqualization_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = original.clone();

    if (original.channels() == 1)
    {
        int histogram[256];
        int hist_cum[256];

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
            hist_cum[i] = 0;
        }

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                histogram[(int)original.at<uchar>(r, c)]++;
            }
        }

        float alpha = 255 / (original.rows * original.cols);
        cout << alpha << endl;
        hist_cum[0] = (int)(alpha * histogram[0]);
        cout << hist_cum[0] << endl;

        for(int i = 1; i < 255; i++)
        {
            hist_cum[i] = (int)hist_cum[i-1] + (int)(alpha * histogram[i]);
        }

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                modified.at<uint8_t>(r, c) = hist_cum[original.at<uint8_t>(r, c)];
            }
        }
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_Grayscale8)));
    }

    if (original.channels() == 3)
    {
        cv::Mat grayimg = original.clone();

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
                grayimg.at<cv::Vec3b>(r, c)[0] = gray;
                grayimg.at<cv::Vec3b>(r, c)[1] = gray;
                grayimg.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(grayimg, grayimg, cv::COLOR_BGR2GRAY);

        int histogram[256];
        double hist_cum[256];

        for(int i = 0; i < 255; i++)
        {
            histogram[i] = 0;
            hist_cum[i] = 0;
        }

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                histogram[(int)grayimg.at<uchar>(r, c)]++;
            }
        }

        int size = original.rows * original.cols;
        double alpha = 255.0 / size;
        hist_cum[0] = alpha * histogram[0];

        for(int i = 1; i < 255; i++)
        {
            hist_cum[i] = round(hist_cum[i-1]) + round(alpha * histogram[i]);
        }

        for(int r = 0; r < original.rows; r++)
        {
            for(int c = 0; c < original.cols; c++)
            {
                modified.at<cv::Vec3b>(r, c)[0] = hist_cum[original.at<cv::Vec3b>(r, c)[0]];
                modified.at<cv::Vec3b>(r, c)[1] = hist_cum[original.at<cv::Vec3b>(r, c)[1]];
                modified.at<cv::Vec3b>(r, c)[2] = hist_cum[original.at<cv::Vec3b>(r, c)[2]];
            }
        }
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
    }
}

void MainWindow::on_pushButtonHistogramMatching_clicked()
{
    QString extension_source;
    extension_source = ui->lineEditReadImage->text();

    cv::Mat source = cv::imread(extension_source.toStdString());
    if (source.empty())
    {
        cout << "Image could not be found." << endl;
    }
    cv::Mat source_gray = source.clone();

    QString extension_target;
    extension_target = ui->lineEditHistMatch->text();

    cv::Mat target = cv::imread(extension_target.toStdString());
    if (target.empty())
    {
        cout << "Image could not be found." << endl;
    }
    cv::Mat target_gray = target.clone();

    if(source.channels() == 3)
    {
        for(int r = 0; r < source.rows; r++)
        {
            for(int c = 0; c < source.cols; c++)
            {
                float gray = source.at<cv::Vec3b>(r, c)[0] * 0.114  + source.at<cv::Vec3b>(r, c)[1] * 0.587 + source.at<cv::Vec3b>(r, c)[2] * 0.299;
                source_gray.at<cv::Vec3b>(r, c)[0] = gray;
                source_gray.at<cv::Vec3b>(r, c)[1] = gray;
                source_gray.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(source_gray, source_gray, cv::COLOR_BGR2GRAY);
    }

    if(target.channels() == 3)
    {
        for(int r = 0; r < target.rows; r++)
        {
            for(int c = 0; c < target.cols; c++)
            {
                float gray = target.at<cv::Vec3b>(r, c)[0] * 0.114  + target.at<cv::Vec3b>(r, c)[1] * 0.587 + target.at<cv::Vec3b>(r, c)[2] * 0.299;
                target_gray.at<cv::Vec3b>(r, c)[0] = gray;
                target_gray.at<cv::Vec3b>(r, c)[1] = gray;
                target_gray.at<cv::Vec3b>(r, c)[2] = gray;
            }
        }
        cv::cvtColor(target_gray, target_gray, cv::COLOR_BGR2GRAY);
    }

    int histogram_source[256];
    int histogram_target[256];
    int HM[256];

    double hist_cum_source[256];
    double hist_cum_target[256];

    for(int i = 0; i < 255; i++)
    {
        histogram_source[i] = 0;
        histogram_target[i] = 0;
        hist_cum_source[i] = 0;
        hist_cum_target[i] = 0;
    }

    for(int r = 0; r < source.rows; r++)
    {
        for(int c = 0; c < source.cols; c++)
        {
            histogram_source[(int)source_gray.at<uchar>(r, c)]++;
        }
    }

    for(int r = 0; r < target.rows; r++)
    {
        for(int c = 0; c < target.cols; c++)
        {
            histogram_target[(int)target_gray.at<uchar>(r, c)]++;
        }
    }

    int size_source = source.rows * source.cols;
    double alpha_source = 255.0 / size_source;
    hist_cum_source[0] = alpha_source * histogram_source[0];

    for(int i = 1; i < 255; i++)
    {
        hist_cum_source[i] = round(hist_cum_source[i-1]) + round(alpha_source * histogram_source[i]);
    }

    int size_target = target.rows * target.cols;
    double alpha_target = 255.0 / size_target;
    hist_cum_target[0] = alpha_target * histogram_target[0];

    for(int i = 1; i < 255; i++)
    {
        hist_cum_target[i] = round(hist_cum_target[i-1]) + round(alpha_target * histogram_target[i]);
    }

    int hist_cum_target_int[256];
    int hist_cum_source_int[256];

    for(int i = 1; i < 255; i++)
    {
        hist_cum_target_int[i] = round(hist_cum_target[i]);
        hist_cum_source_int[i] = round(hist_cum_source[i]);
    }

    for (int i = 0; i < 255; i++)
    {
        int n = 255;
        int source_shade = hist_cum_source_int[i];
        HM[i] = findClosest(hist_cum_target_int, n, source_shade);
    }

    cv::Mat source_matched = source_gray.clone();

    for(int r = 0; r < source_matched.rows; r++)
    {
        for(int c = 0; c < source_matched.cols; c++)
        {
            source_matched.at<uint8_t>(r, c) = HM[source_gray.at<uint8_t>(r, c)];
        }
    }
    ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(source_matched.data, source_matched.cols, source_matched.rows, source_matched.step, QImage::Format_Grayscale8)));

    cv::imshow("Target grayscale image", target_gray);
    cv::imshow("Source grayscale image", source_gray);
    cv::waitKey(0);
}

void MainWindow::on_spinBoxBrightness_valueChanged(int arg1)
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    int brigthness = (int)arg1;

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = original.clone();

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

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    cv::Mat modified = original.clone();

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

    cv::Mat modified = original.clone();

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

    cv::Mat modified = original.clone();
    cv::Mat filtered = original.clone();

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

    float kernel[3][3] = {{n22, n21, n20}, {n12, n11, n10}, {n02, n01, n00}};

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
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(filtered.data, filtered.cols, filtered.rows, filtered.step, QImage::Format_Grayscale8)));
    }
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

    if (original.channels() == 3)
    {
        QImage image = QImage(new_width, new_height, QImage::Format_RGB888);
        image.fill(0);
        image.save("/home/ubuntu/clockwise.jpg");

        cv::Mat modified = cv::imread("/home/ubuntu/clockwise.jpg");
        if (modified.empty())
        {
            cout << "Image could not be found." << endl;
        }

        for(int c = 0; c < original.cols; c++)
        {
            for(int r = 0; r < original.rows; r++)
            {
                modified.at<cv::Vec3b>(c, r)[0] = original.at<cv::Vec3b>(original.rows - 1 - r, c)[0];
                modified.at<cv::Vec3b>(c, r)[1] = original.at<cv::Vec3b>(original.rows - 1 - r, c)[1];
                modified.at<cv::Vec3b>(c, r)[2] = original.at<cv::Vec3b>(original.rows - 1 - r, c)[2];
            }
        }
        cv::imshow("Rotated image", modified);
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
        cv::waitKey(0);
    }

    if (original.channels() == 1)
    {
        QImage image = QImage(new_width, new_height, QImage::Format_Grayscale8);
        image.fill(0);
        image.save("/home/ubuntu/clockwise.jpg");

        cv::Mat modified = cv::imread("/home/ubuntu/clockwise.jpg");
        if (modified.empty())
        {
            cout << "Image could not be found." << endl;
        }

        for(int c = 0; c < original.cols; c++)
        {
            for(int r = 0; r < original.rows; r++)
            {
                modified.at<uint8_t>(c, r) = original.at<uint8_t>(original.rows - 1 - r, c);
            }
        }
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_Grayscale8)));
        cv::imshow("Rotated image", modified);
        cv::waitKey(0);
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

    if (original.channels() == 3)
    {
        QImage image = QImage(new_width, new_height, QImage::Format_RGB888);
        image.fill(0);
        image.save("/home/ubuntu/anticlockwise.jpg");

        cv::Mat modified = cv::imread("/home/ubuntu/anticlockwise.jpg");
        if (modified.empty())
        {
            cout << "Image could not be found." << endl;
        }

        for(int c = 0; c < original.cols; c++)
        {
            for(int r = 0; r < original.rows; r++)
            {
                modified.at<cv::Vec3b>(c, r)[0] = original.at<cv::Vec3b>(r, original.cols - 1 - c)[0];
                modified.at<cv::Vec3b>(c, r)[1] = original.at<cv::Vec3b>(r, original.cols - 1 - c)[1];
                modified.at<cv::Vec3b>(c, r)[2] = original.at<cv::Vec3b>(r, original.cols - 1 - c)[2];
            }
        }
        cv::imshow("Rotated image", modified);
        cv::cvtColor(modified, modified, cv::COLOR_BGR2RGB);
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_RGB888)));
        cv::waitKey(0);
    }

    if (original.channels() == 1)
    {
        QImage image = QImage(new_width, new_height, QImage::Format_Grayscale8);
        image.fill(0);
        image.save("/home/ubuntu/anticlockwise.jpg");

        cv::Mat modified = cv::imread("/home/ubuntu/anticlockwise.jpg");
        if (modified.empty())
        {
            cout << "Image could not be found." << endl;
        }

        for(int c = 0; c < original.cols; c++)
        {
            for(int r = 0; r < original.rows; r++)
            {
                modified.at<uint8_t>(c, r) = original.at<uint8_t>(r, original.cols - 1 - c);
            }
        }
        ui->displayNewImage->setPixmap(QPixmap::fromImage(QImage(modified.data, modified.cols, modified.rows, modified.step, QImage::Format_Grayscale8)));
        cv::imshow("Rotated image", modified);
        cv::waitKey(0);
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

        for(int r = 0; r < modified.rows; r = r + 2)
        {
            for(int c = 1; c <= modified.cols; c = c + 2)
            {
                modified1.at<cv::Vec3b>(r, c)[0] = modified.at<cv::Vec3b>(r, c - 1)[0] + (modified.at<cv::Vec3b>(r, c + 1)[0] - modified.at<cv::Vec3b>(r, c - 1)[0]) / 2;
                modified1.at<cv::Vec3b>(r, c)[1] = modified.at<cv::Vec3b>(r, c - 1)[1] + (modified.at<cv::Vec3b>(r, c + 1)[1] - modified.at<cv::Vec3b>(r, c - 1)[1]) / 2;
                modified1.at<cv::Vec3b>(r, c)[2] = modified.at<cv::Vec3b>(r, c - 1)[2] + (modified.at<cv::Vec3b>(r, c + 1)[2] - modified.at<cv::Vec3b>(r, c - 1)[2]) / 2;
            }
        }

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

    if(modified.channels() == 1)
    {
        int i = 0;

        for(int r = 0; r < modified.rows; r = r + 2)
        {
            int j = 0;
            for(int c = 0; c < modified.cols; c = c + 2)
            {
                modified.at<uint8_t>(r, c) = original.at<uint8_t>(i, j);
                j = j + 1;
            }
            i = i + 1;
        }

        cv::Mat modified1 = modified.clone();

        for(int r = 0; r < modified.rows; r = r + 2)
        {
            for(int c = 1; c <= modified.cols; c = c + 2)
            {
                modified1.at<uint8_t>(r, c) = modified.at<uint8_t>(r, c - 1) + (modified.at<uint8_t>(r, c + 1) - modified.at<uint8_t>(r, c - 1)) / 2;
            }
        }

        cv::Mat modified2 = modified1.clone();

        for(int r = 1; r <= modified1.rows; r = r + 2)
        {
            for(int c = 0; c < modified1.cols; c = c + 1)
            {
                modified2.at<uint8_t>(r, c) = modified1.at<uint8_t>(r - 1, c) + (modified1.at<uint8_t>(r + 1, c) - modified1.at<uint8_t>(r - 1, c)) / 2;
            }
        }
        cv::imshow("Zoom In", modified2);
        cv::waitKey(0);
    }
}

void MainWindow::on_pushButtonZoomOut_clicked()
{
    QString extension;
    extension = ui->lineEditReadImage->text();

    cv::Mat original = cv::imread(extension.toStdString());
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    int sx = 20;
    int sy = 20;

    int original_rows = original.rows;
    int original_cols = original.cols;

    int fit_rows = round(original_rows / sx);
    int fit_cols = round(original_cols / sy);

    int n_rows = fit_rows / sx;
    int n_cols = fit_cols / sy;

    int remain_rows  = original_rows - sx * fit_rows;
    int remain_cols = original_cols - sy * fit_cols;

    int new_rows = fit_rows + remain_rows;
    int new_cols = fit_cols + remain_cols;

    cout << fit_rows << remain_rows << new_rows << endl;
    cout << fit_cols << remain_cols << new_cols << endl;

    QImage image = QImage(new_rows, new_cols, QImage::Format_RGB888);
    image.fill(0);
    image.save("/home/ubuntu/zoomout.jpg");

    cv::Mat modified = cv::imread("/home/ubuntu/zoomout.jpg");
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    int r = 0;
    int c = 0;

    for (int i = 1; i <= new_rows; i++)
    {
        for (int j = 1; j <= new_cols; j++)
        {
            while (r < sx * i)
            {
                while (c < sy * i)
                {
                    // float meanB =
                    c = c + 1;
                }
                c = c + sy;
                r = r + 1;
            }
            r = r + sx;
            // modified.at<cv::Vec3b>(i - 1, j - 1)[0] = meanB;
        }
    }
}
