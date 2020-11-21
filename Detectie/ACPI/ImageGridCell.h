#pragma once
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QLabel>
#include "AbstractViewer.h"

class ImageGridCell : public QWidget
{
	QLabel *titleLabel;
	AbstractViewer *viewer;
	QLabel *bottomLabel;
	QVBoxLayout *layout;
	bool showInfo;

public:
	ImageGridCell(QWidget *parent = nullptr);
	void setImage(QImage* image, QString title);
	void setHistogram(int *values, int size, QString title = "");
	void updateInfo();
	void setImage(QString fileName, QString title = "");
	void setBottomText(QString text = "");
	void setAutoResize(bool enable);
	void restoreOriginalSize();
	QSize sizeHint() const;
}; 