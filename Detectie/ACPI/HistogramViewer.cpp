#include "HistogramViewer.h"
#include "ImageGridCell.h"
#include <QPainter>

HistogramViewer::HistogramViewer(QWidget *parent)
	: AbstractViewer(parent), vals(nullptr),
	minVal(0), maxVal(1), vScale(1),
	cursorPos(-1)
{
	QVBoxLayout* lay = new QVBoxLayout;
	setLayout(lay);
}

void HistogramViewer::setValues(int* _vals, int _nrVals)
{
	if (_vals)
	{
		vals = _vals;
		nrVals = _nrVals;

		maxVal = vals[0];
		for (int i = 1; i<nrVals; i++)
			if (vals[i] > maxVal) maxVal = vals[i];
		minVal = vals[0];
		for (int i = 1; i < nrVals; i++)
			if (vals[i] < minVal) minVal = vals[i];

		update();
	}
}

void HistogramViewer::setCursor(float val)
{
	cursorPos = val;
	update();
}

void HistogramViewer::paintEvent(QPaintEvent *e)
{
	QRect viewPort = rect();
	int xLeft = viewPort.left();
	int xRight = viewPort.right();
	int yTop = viewPort.top();
	int yBottom = viewPort.bottom();
	int width = viewPort.width();
	int height = viewPort.height();

	QPainter painter(this);

	QPen pen;
	pen.setColor("#0000AA");
	pen.setWidth(1);
	painter.setPen(pen);

	QBrush brush(Qt::SolidPattern);
	brush.setColor("#7777FF");
	painter.setBrush(brush);

	int newMaxVal = vals[0];
	for (int i = 1; i<nrVals; i++)
		if (vals[i] > newMaxVal) newMaxVal = vals[i];
	if (abs(newMaxVal - maxVal) / (float)maxVal > 0.05f)
		maxVal = newMaxVal;

	QPolygon poly;

	if (nrVals < width)
	{
		vScale = 1.0;
		float ws = (float)width / nrVals;
		float hs = (float)height / maxVal;

		poly.clear();
		poly << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
		for (int i = 0; i < nrVals; ++i)
			poly << QPoint(xLeft + ws*i, yTop + hs*(maxVal - vals[i]));
		painter.drawPolygon(poly);
	}
	else
	{
		float ws = (float)(nrVals - 1) / (width - 1);
		float hs = (float)height / maxVal;

		poly.clear();
		poly << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
		for (int i = 0; i < width; ++i)
			poly << QPoint(xLeft + i, yTop + hs*(maxVal - vals[(int)(ws*i)]));
		painter.drawPolygon(poly);
	}

	//draw cursor
	if (cursorPos >= 0 && cursorPos <= 1.0)
	{
		pen.setColor(Qt::red);
		pen.setWidth(2.0);
		painter.setPen(pen);
		int cx = cursorPos * width;
		painter.drawLine(cx, 0, cx, height);
	}

	//draw border
	pen.setColor(Qt::black);
	pen.setWidth(1.0);
	painter.setPen(pen);

	painter.drawLine(xLeft, yTop, xRight, yTop);
	painter.drawLine(xRight, yTop, xRight, yBottom);
	painter.drawLine(xRight, yBottom, xLeft, yBottom);
	painter.drawLine(xLeft, yBottom, xLeft, yTop);
}

QPoint HistogramViewer::getCursorValues()
{
	if (cursorPos < 0 || cursorPos > 1 || !vals)
		return QPoint(0, 0);
	int domainValue = round(cursorPos * 255);
	return QPoint(domainValue, vals[domainValue]);
}

QString HistogramViewer::getInfo()
{
	std::string info;
	QPoint cursorVals = getCursorValues();
	info += "Domain: 0 - " + std::to_string(nrVals - 1) + "\n"
		"Range: " + std::to_string(minVal) + " - " + std::to_string(maxVal) +
		"\nCursor: intensity: " + std::to_string(cursorVals.x()) + 
		", nr. pixels: " + std::to_string(cursorVals.y());

	return QString::fromStdString(info);
}

void HistogramViewer::restoreOriginalSize()
{
	// ???
}

void HistogramViewer::setAutoResize(bool enable)
{
	// ???
}

void HistogramViewer::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		setCursor((float)e->x() / width());
		((ImageGridCell*)parentWidget())->updateInfo();
	} 
	else if (e->button() == Qt::RightButton)
	{
		setCursor(-1);
		((ImageGridCell*)parentWidget())->updateInfo();
	}
}

void HistogramViewer::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		setCursor((float)e->x() / width());
		((ImageGridCell*)parentWidget())->updateInfo();
	}
}
