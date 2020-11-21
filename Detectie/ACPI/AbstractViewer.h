#pragma once
#include <QWidget>
#include <QKeyEvent>

class AbstractViewer : public QWidget
{
protected:
	bool autoResize;
	float scaleFactor;
	int mousePosX, mousePosY;

public:
	AbstractViewer(QWidget* parent);
	virtual void setAutoResize(bool enabled) = 0;
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);
	virtual void updateInfo();
	virtual QString getInfo() = 0;
	virtual void restoreOriginalSize() = 0;
};
