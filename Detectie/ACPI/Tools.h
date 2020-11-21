#pragma once
#include <QString>
#include <QImage>
#include "PITimer.h"
#include <QDebug>

class Tools
{
	static PITimer t;
	static QVector<QRgb> grayLUT;

public:
	static unsigned char* readImageGray8(const QString &fileName, int &w, int &h)
	{
		QImage* img = new QImage(fileName);
		w = img->width();
		h = img->height();
		unsigned char *pixelValues = new unsigned char[w*h];
		for (int i = 0; i < h; i++)
			memcpy(pixelValues + i*w, img->scanLine(i), w);
		delete img;
		return pixelValues;
	}

	static QImage* imageGray8FromArray(unsigned char* bytes, int w, int h)
	{
		QImage *img = new QImage(bytes, w, h, w, QImage::Format_Indexed8);
		img->setColorTable(grayLUT);
		return img;
	}

	static unsigned char* imDiff(unsigned char* im1, unsigned char* im2, int w, int h)
	{
		int size = w*h;
		unsigned char* diff = new unsigned char[size];
		for (int i = 0; i < size; i++)
			diff[i] = abs(im1[i] - im2[i]);
		return diff;
	}

	static void timerStart()
	{
		t.start();
	}

	static void timerStop()
	{
		t.stop();
	}

	static double timerElapsed()
	{
		return t.elapsed();
	}
};



