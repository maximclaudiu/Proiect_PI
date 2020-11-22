#pragma once
#include <cmath>
#include "opencv2/opencv.hpp"

//================================================================
//Functii Globale Qt
//================================================================

unsigned char* negateImage(unsigned char* img, int w, int h);
unsigned char* binarizareImage(unsigned char* img, int w, int h);
unsigned char* sobelImage(unsigned char* img, int w, int h);
int* histogram(unsigned char* img, int w, int h);

//================================================================
//Functii Locale
//================================================================

