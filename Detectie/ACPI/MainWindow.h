#pragma once
#include "GeneratedFiles\ui_MainWindow.h"
#include <QApplication>
#include "ImageGrid.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>

class MainWindow : public QMainWindow, private Ui_MainWindow
{
	Q_OBJECT
public: 
	MainWindow();
private:
	Ui::MainWindow* ui;
private slots:
	void addImage();
	void filter();
	void saveImage();
};