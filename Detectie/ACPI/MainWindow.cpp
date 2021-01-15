#include "MainWindow.h"
#include "qfiledialog.h"
void thresh_callback(int, void*);
using namespace cv;
using namespace std;
Mat src, src_gray;
int thresh_int = 100;
Mat img, eqh, sobel, sobeleqh, gaussian, morph;
QString fileName;

MainWindow::MainWindow() : QMainWindow(), ui(new Ui::MainWindow) {
        ui->setupUi(this);

        connect(ui->LoadImage, SIGNAL(released()), this, SLOT(addImage()));
        connect(ui->ApplyFilter, SIGNAL(released()), this, SLOT(filter()));
        connect(ui->SaveImage, SIGNAL(released()), this, SLOT(saveImage()));
    }

void thresh_callback(int, void*)
{
    Mat canny_output, canny_input;
    Scalar color = Scalar(0, 0, 0);
    GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 1);
    Canny(src_gray, canny_output, 0, 255, 3, true);
    vector<vector<Point> > contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f>centers(contours.size());
    vector<float>radius(contours.size());


    for (size_t i = 0; i < contours.size(); i++)
    {
        double p;
        p = arcLength(contours[i], true);
        vector<Point> aprox;
        approxPolyDP(contours[i], aprox, 0.018 * p, true);

        //if (aprox.size() == 4)
        {
            boundRect[i] = boundingRect(aprox);
        }
    }
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        if (boundRect[i].area() > 1500 && boundRect[i].area() < 3000)
            if ((float)boundRect[i].width / boundRect[i].height >= 2.6 && (float)boundRect[i].width / boundRect[i].height <= 5)
            {
                rectangle(src, boundRect[i].tl(), boundRect[i].br(), color, FILLED);
            }
    }
}

void MainWindow::addImage() {
   
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));

    src = imread(samples::findFile(fileName.toStdString()));
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;       
    }
    cv::resize(src, src, Size(480, 320));
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    const int max_thresh = 255;
    QImage img;
    img.load(fileName);
    ui->Poza_OG->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::filter() {
    thresh_callback(0, 0);
    QImage img(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
    img = img.rgbSwapped();
    ui->Poza_FILT->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::saveImage() {
    fileName = fileName.split(".", QString::SkipEmptyParts).at(0);
    imwrite(fileName.toStdString()+"_filtrat.jpg", src);
}

