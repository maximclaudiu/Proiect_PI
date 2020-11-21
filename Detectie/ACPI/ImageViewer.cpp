#include "ImageViewer.h"
#include <QApplication>
#include <QHBoxLayout>
#include "ImageGridCell.h"
#include <QPainter>

ImageViewer::ImageViewer(QWidget *parent)
	: AbstractViewer(parent),
	tx(0), ty(0),
	imx(0), imy(0), imW(0), imH(0),
	scrollBarThickness(4),
	enableScrollBars(false)
{
}

void ImageViewer::setImage(QImage* _image)
{
	if (_image)
	{
		image = _image;
		imW = image->width();
		imH = image->height();
		update();
	}
}

void ImageViewer::restoreOriginalSize()
{
	imx = 0;
	imy = 0;
	imW = image->width();
	imH = image->height();
	scaleFactor = 1.0f;
	update();
	updateInfo();
}

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		mousePosX = e->pos().x();
		mousePosY = e->pos().y();
	}
}

void ImageViewer::mouseMoveEvent(QMouseEvent *e)
{
	if (!autoResize)
	{
		if (e->buttons() & Qt::LeftButton)
		{
			int mx = e->pos().x();
			int my = e->pos().y();
			tx = mx - mousePosX;
			ty = my - mousePosY;
			mousePosX = mx;
			mousePosY = my;
			update();
		}
	}
}

void ImageViewer::wheelEvent(QWheelEvent *e)
{
	if (!autoResize)
	{
		float oldScaleFactor = scaleFactor;
		scaleFactor *= 1 + (float)e->delta() / 1200;
		imx -= e->pos().x() * (scaleFactor - oldScaleFactor);
		imy -= e->pos().y() * (scaleFactor - oldScaleFactor);
		imW = image->width() * scaleFactor;
		imH = image->height() * scaleFactor;
		update();
		updateInfo();
	}
}

void ImageViewer::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_A &&
		(QApplication::keyboardModifiers() & Qt::ControlModifier))
	{
		autoResize ? setAutoResize(false) : setAutoResize(true);
	}
	else if (e->key() == Qt::Key_R && !autoResize &&
		(QApplication::keyboardModifiers() & Qt::ControlModifier))
	{
		restoreOriginalSize();
	}

	AbstractViewer::keyPressEvent(e);
}

void ImageViewer::resizeEvent(QResizeEvent* e)
{
	if (autoResize)
		updateInfo();
}

QString ImageViewer::getInfo()
{
	std::string info;
	info += "Size:" + std::to_string(imW) + "x" + std::to_string(imH) +
		"\nOriginal size: " + std::to_string(image->width()) + "x" +
		std::to_string(image->height()) +
		"\nAuto resize: " + (autoResize ? "on" : "off");
	return QString::fromStdString(info);
}

void ImageViewer::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	QPen pen(Qt::red);
	painter.setPen(pen);
	int viewW = width();
	int viewH = height();

	if (image)
	{
		float imAspect = (float)image->width() / image->height();
		float viewAspect = (float)viewW / viewH;
		if (autoResize)
		{
			if (imAspect >= viewAspect)
			{
				imx = 0;
				imW = viewW;
				imH = imW / imAspect;
				imy = (viewH - imH) / 2;
			}
			else
			{
				imy = 0;
				imH = viewH;
				imW = imH * imAspect;
				imx = (viewW - imW) / 2;
			}
			tx = 0;
			ty = 0;
		}
		else
		{
			if (imW <= viewW)
			{
				imx = (viewW - imW) / 2;
				tx = 0;
			}
			else
			{
				imx += tx;
				if (imx > 0) imx = 0;
				if (imx < viewW - imW) imx = viewW - imW;
			}
			if (imH <= viewH)
			{
				imy = (viewH - imH) / 2;
				ty = 0;
			}
			else
			{
				imy += ty;
				if (imy > 0) imy = 0;
				if (imy < viewH - imH) imy = viewH - imH;
			}
		}
			
		painter.drawImage(QRect(imx, imy, imW, imH), *image);

		//pseudoscrollbars
		if (enableScrollBars && !autoResize)
		{
			if (imW > viewW)
			{
				int sbarSizeX = viewW * viewW / imW;
				int sbarSizeX2 = sbarSizeX / 2;
				int sbarMinPosX = sbarSizeX2;
				int sbarMaxPosX = viewW - sbarSizeX2;
				int sbarPosX = sbarMinPosX + (float)imx / (viewW - imW) * (sbarMaxPosX - sbarMinPosX);

				pen.setColor(Qt::darkRed);
				pen.setWidth(scrollBarThickness);
				painter.setPen(pen);
				painter.drawRect(sbarPosX - sbarSizeX2, viewH - scrollBarThickness,
					sbarSizeX, scrollBarThickness);
			}
			if (imH > viewH)
			{
				int sbarSizeY = viewH * viewH / imH;
				int sbarSizeY2 = sbarSizeY / 2;
				int sbarMinPosY = sbarSizeY2;
				int sbarMaxPosY = viewH - sbarSizeY2;
				int sbarPosY = sbarMinPosY + (float)imy / (viewH - imH) * (sbarMaxPosY - sbarMinPosY);

				pen.setColor(Qt::darkRed);
				pen.setWidth(scrollBarThickness);
				painter.setPen(pen);
				painter.drawRect(viewW - scrollBarThickness, sbarPosY - sbarSizeY2,
					scrollBarThickness, sbarSizeY);
			}
		}	
	}
	else
	{
		pen.setColor(Qt::red);
		painter.setPen(pen);
		painter.drawLine(0, 0, viewW, viewH);
		painter.drawLine(viewW, 0, 0, viewH);
		painter.drawRect(QRect(0, 0, viewW, viewH));
	}
}

QSize ImageViewer::sizeHint() const
{
	if (image) return image->size();
	return QWidget::sizeHint();
}

void ImageViewer::setAutoResize(bool enabled)
{
	autoResize = enabled;
	if (!autoResize)
	{
		restoreOriginalSize();
	}
	else
	{
		repaint();
		updateInfo();
	}
}
