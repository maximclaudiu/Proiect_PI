#include <QApplication>
#include "ImageGrid.h"
#include "PlateDetection.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
	Mat img = imread("Images/test.jpg", IMREAD_GRAYSCALE);
	Mat eqh, sobel, sobeleqh, gaussian, morph;
	equalizeHist(img, eqh);

	Sobel(img, sobel, img.depth(), 1, 0, 3);
	Sobel(eqh, sobeleqh, eqh.depth(), 1, 0, 3);

	GaussianBlur(sobeleqh, gaussian, Size(11, 11), 10, 3);
	imshow("GaussianBlur", gaussian);

	threshold(gaussian, gaussian, 30, 255, THRESH_BINARY);

	auto kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(gaussian, morph, MORPH_OPEN, kernel, Point(-1, -1), 1);
	morphologyEx(morph, morph, MORPH_CLOSE, kernel, Point(-1, -1), 1);


	//imshow("Asa de test", img);
	//imshow("Histograma", eqh);
	//imshow("Sobel", sobel);
	//imshow("SobelEqh", sobeleqh);
	imshow("Binarization", gaussian);
	imshow("Morphology", morph);
	waitKey();
	return 0;
}