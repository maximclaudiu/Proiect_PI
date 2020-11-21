#pragma once
#include <cmath>
#include "opencv2/opencv.hpp"
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
	cv::Mat outMat(h,w, CV_8UC1,result);
	cv::threshold(inMat, outMat, 70, 255, 0);
	return result;
}
unsigned char* sobelImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	cv::Mat inMat(h, w, CV_8UC1, img);
	cv::Mat outMat(h, w, CV_8UC1, result);
	cv::Mat Sobelx;
	cv::Mat Sobely;
	cv::Sobel(inMat, Sobelx, CV_8U, 0, 1);
	cv::Sobel(inMat, Sobely, CV_8U, 1, 0);
	cv::convertScaleAbs(Sobelx, Sobelx);
	cv::convertScaleAbs(Sobely, Sobely);
	cv::addWeighted(Sobelx, 0.5, Sobely, 0.5, 0, outMat);
	return result;
}