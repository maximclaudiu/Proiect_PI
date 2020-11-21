#pragma once
#include "AbstractViewer.h"

class HistogramViewer : public AbstractViewer
{
	int *vals;
	int nrVals;
	int maxVal;
	int minVal;
	float vScale;
	float cursorPos;

public:
	HistogramViewer(QWidget *parent);
	void setValues(int* _vals, int _nrVals);
	void paintEvent(QPaintEvent* e);
	QString getInfo();
	void restoreOriginalSize();
	QPoint getCursorValues();
	void setCursor(float val);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void setAutoResize(bool enable);
};