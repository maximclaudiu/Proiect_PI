#include "PlateDetection.h"

unsigned char* negateImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	cv::Mat inMat(h, w, CV_8UC1, img);
	cv::Mat negateMat(h, w, CV_8UC1, result);
	cv::bitwise_not(inMat, negateMat);
	return result;
}
unsigned char* binarizareImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	cv::Mat inMat(h, w, CV_8UC1, img);
	cv::Mat outMat(h, w, CV_8UC1, result);
	cv::threshold(inMat, outMat, 70, 255, 0);
	return result;
}
int* histogram(unsigned char* img, int w, int h)
{
	int* pixeli = new int[256];
	for (int i = 0; i < 256; i++)
		pixeli[i] = 0;
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			pixeli[img[w*x+y]]++;
	return pixeli;
}
unsigned char* sobelImage(unsigned char* img, int w, int h)
{
	using namespace cv;
	unsigned char* result = new unsigned char[w * h];
	Mat inMat(h, w, CV_8UC1, img);
	Mat outMat(h, w, CV_8UC1, result);
	Mat Sobelx;
	Mat Sobely;
	Sobel(inMat, Sobelx, CV_8U, 0, 1);
	Sobel(inMat, Sobely, CV_8U, 1, 0);
	convertScaleAbs(Sobelx, Sobelx);
	convertScaleAbs(Sobely, Sobely);
	addWeighted(Sobelx, 0.5, Sobely, 0.5, 0, outMat);
	return result;
}