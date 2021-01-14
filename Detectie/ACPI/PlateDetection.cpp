#include "MainWindow.h"

using namespace cv;
using namespace std;

#ifndef NDEBUG
int GaussianSize = 5, SigmaXSize = 1, SigmaYSize = 1, threshholdValue = 18, morphOpen = 1, morphClose = 1, morphDilate = 1, morphErode = 1;
#else
int GaussianSize = 5, SigmaXSize = 1, SigmaYSize = 1, threshholdValue = 18, morphOpen = 1, morphClose = 1;
#endif

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}