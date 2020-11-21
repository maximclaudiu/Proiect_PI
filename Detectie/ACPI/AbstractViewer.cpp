#include "AbstractViewer.h"
#include <QApplication>
#include "ImageGridCell.h"

AbstractViewer::AbstractViewer(QWidget* parent)
	: QWidget(parent), autoResize(false), 
	scaleFactor(1.0f)
{
	setMinimumSize(100, 100);
}

void AbstractViewer::enterEvent(QEvent *e)
{
	setFocus(Qt::ShortcutFocusReason);
}

void AbstractViewer::leaveEvent(QEvent *e)
{
	clearFocus();
}

void AbstractViewer::updateInfo()
{
	((ImageGridCell*)parentWidget())->updateInfo();
}