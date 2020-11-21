#pragma once
#include <QGridLayout>
#include <QKeyEvent>
#include "ImageGridCell.h"
#include "Tools.h"
#include <iostream>
#include <map>

class ImageGrid : public QWidget
{
	QGridLayout *layout;
	bool autoResizeCells;

public:
	ImageGrid(QString title = "ACPI", QWidget *parent = nullptr);
	void addImage(QImage* image, int posX, int posY, QString title, double timerVal = 0);
	void addImage(unsigned char* pixelData, int width, int height, int posX, int posY, QString title = "");
	void addImage(QString fileName, int posX, int posY, QString title = "");
	void addHistogram(int *values, int nrValues, int posX, int posY, QString title = "histogram");
	QSize getCellSize();
	void keyPressEvent(QKeyEvent *e);
};