#include <QApplication>
#include "ImageGrid.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "MainWindow.h"
#include <iostream>

using namespace cv;
using namespace std;
Mat src, src_gray;
int thresh_int = 100;
RNG rng(12345);
void thresh_callback(int, void*);

#ifndef NDEBUG
int GaussianSize = 5, SigmaXSize = 1, SigmaYSize = 1, threshholdValue = 18, morphOpen = 1, morphClose = 1, morphDilate = 1, morphErode = 1;
#else
int GaussianSize = 3, SigmaXSize = 6, SigmaYSize = 6, threshholdValue = 30, morphOpen = 3, morphClose = 3;
#endif
Mat img, eqh, sobel, sobeleqh, gaussian, morph;

int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{@input | Images/bmw.jpg | input image}");
    src = imread(samples::findFile(parser.get<String>("@input")));
    if (src.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    const int max_thresh = 255;
    thresh_callback(0, 0);
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
void thresh_callback(int, void*)
{
    Mat canny_output;
    Canny(src_gray, canny_output, 30, 200);
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

        if (aprox.size() == 4)
        {
            boundRect[i] = boundingRect(aprox);
            minEnclosingCircle(aprox, centers[i], radius[i]);
        }
    }
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        if (boundRect[i].area() > 4000 && boundRect[i].area() < 10000)
            if ((boundRect[i].width * 1.0) / (boundRect[i].height * 1.0) >= 3.0 && (boundRect[i].width * 1.0) /( boundRect[i].height*1.0) <= 4.9)
                if (boundRect[i].height>30 && boundRect[i].height<100)
                {
                    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
                    rectangle(src, boundRect[i].tl(), boundRect[i].br(), color, FILLED);
                }
    }
    imshow ("", src);
}