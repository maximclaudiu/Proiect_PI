#include "ImageGridCell.h"
#include "ImageGrid.h"
#include "ImageViewer.h"
#include "HistogramViewer.h"
#include <QApplication>

ImageGridCell::ImageGridCell(QWidget *parent)
	: QWidget(parent)
{
	titleLabel = new QLabel(this);
	titleLabel->setStyleSheet("font-weight: bold;");
	viewer = nullptr;
	bottomLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	setLayout(layout);
	layout->addWidget(titleLabel, 0, Qt::AlignHCenter);
	showInfo = true;
}

void ImageGridCell::setImage(QImage* image, QString title)
{
	titleLabel->setText(title);
	viewer = new ImageViewer(this);
	((ImageViewer*)viewer)->setImage(image);
	layout->addWidget(viewer, 1);
	layout->addWidget(bottomLabel, 0, Qt::AlignHCenter);
	if (showInfo) updateInfo();
}

void ImageGridCell::updateInfo()
{
	bottomLabel->setText(viewer->getInfo());
}

void ImageGridCell::setImage(QString fileName, QString title)
{
	setImage(new QImage(fileName), title == "" ? fileName : title);
}

void ImageGridCell::setHistogram(int *values, int size, QString title)
{
	titleLabel->setText(title);
	viewer = new HistogramViewer(this);
	((HistogramViewer*)viewer)->setValues(values, size);
	layout->addWidget(viewer, 1);
	layout->addWidget(bottomLabel, 0, Qt::AlignHCenter);
	if (showInfo) updateInfo();
}

void ImageGridCell::setAutoResize(bool enable)
{
	viewer->setAutoResize(enable);
}

void ImageGridCell::restoreOriginalSize()
{
	viewer->restoreOriginalSize();
}

QSize ImageGridCell::sizeHint() const
{
	return ((ImageGrid*)parentWidget())->getCellSize();
}

