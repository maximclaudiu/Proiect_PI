#include "ImageGrid.h"
#include <QApplication>
#include <QWidgetItem>
#include <QDebug>

ImageGrid::ImageGrid(QString title, QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout(this);
	setLayout(layout);
	setWindowTitle(title);
	autoResizeCells = false;
	//setStyleSheet("border: 1px solid red;");
}

void ImageGrid::addImage(QImage* image, int posX, int posY, QString title, double timerVal)
{
	ImageGridCell *cell = new ImageGridCell(this);
	cell->setImage(image, title);
	layout->addWidget(cell, posX, posY);
}

void ImageGrid::addImage(unsigned char* pixelData, int width, int height,
	int posX, int posY, QString title)
{
	addImage(Tools::imageGray8FromArray(pixelData, width, height), posX, posY, title);
}

void ImageGrid::addImage(QString fileName, int posX, int posY, QString title)
{
	if (title == "") title = fileName;
	addImage(new QImage(fileName), posX, posY, title);
}

void ImageGrid::addHistogram(int *values, int nrValues, int posX, int posY, QString title)
{
	ImageGridCell *cell = new ImageGridCell(this);
	cell->setHistogram(values, nrValues, title);
	layout->addWidget(cell, posX, posY);
	setLayout(layout);
}

QSize ImageGrid::getCellSize()
{
	int w = this->width();
	int h = this->height();
	int m = layout->margin();
	int s = layout->spacing();
	int nRows = layout->rowCount();
	int nCols = layout->columnCount();
	return QSize((w - m * 2 - s*(nCols - 1)) / nCols, (h - m * 2 - s*(nRows - 1)) / nRows);
}

void ImageGrid::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
	{
		QCoreApplication::exit();
	}
	else if (e->key() == Qt::Key_A &&
		(QApplication::keyboardModifiers()& Qt::ShiftModifier))
	{
		autoResizeCells = autoResizeCells ? false : true;
		for (int i = 0; i < layout->count(); i++)
		{
			((ImageGridCell*)(QWidgetItem*)layout->itemAt(i)->widget())->setAutoResize(autoResizeCells);
		}
	}
	else if (e->key() == Qt::Key_R &&
		(QApplication::keyboardModifiers()& Qt::ShiftModifier))
	{
		for (int i = 0; i < layout->count(); i++)
		{
			((ImageGridCell*)(QWidgetItem*)layout->itemAt(i)->widget())->restoreOriginalSize();
		}
	}
}