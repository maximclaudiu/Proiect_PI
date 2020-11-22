#include <QApplication>
#include "ImageGrid.h"
#include "PlateDetection.h"

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);

	ImageGrid* grid = new ImageGrid("Prelucrarea imaginilor");

	QString imageDir = "Images/";
	QString imageFile(imageDir + "lena512.bmp");

	grid->addImage(imageFile, 0, 0);

	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);

	grid->show();
	return a.exec();
}

