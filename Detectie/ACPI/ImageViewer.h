#pragma once
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include "AbstractViewer.h"

class ImageWidget;

class ImageViewer : public AbstractViewer
{
	QImage *image;
	int tx, ty, imx, imy, imW, imH;
	int scrollBarThickness;
	int enableScrollBars;

public:
	ImageViewer(QWidget *parent);
	void setImage(QImage* image);
	void restoreOriginalSize();
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void resizeEvent(QResizeEvent* e);
	void wheelEvent(QWheelEvent *e);
	void keyPressEvent(QKeyEvent *e);
	QString getInfo();
	void paintEvent(QPaintEvent *e);
	QSize sizeHint() const;
	void setAutoResize(bool enabled);
};