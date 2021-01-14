/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *LoadImage;
    QFrame *line;
    QFrame *line_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *ApplyFilter;
    QPushButton *SaveImage;
    QLabel *Poza_OG;
    QLabel *Poza_FILT;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1020, 440);
        MainWindow->setMinimumSize(QSize(1020, 440));
        MainWindow->setMaximumSize(QSize(1020, 440));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LoadImage = new QPushButton(centralwidget);
        LoadImage->setObjectName(QString::fromUtf8("LoadImage"));
        LoadImage->setGeometry(QRect(20, 390, 101, 31));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 370, 1021, 4));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(490, -90, 41, 461));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(3);
        line_2->setFrameShape(QFrame::VLine);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 13, 91, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(720, 10, 71, 20));
        ApplyFilter = new QPushButton(centralwidget);
        ApplyFilter->setObjectName(QString::fromUtf8("ApplyFilter"));
        ApplyFilter->setGeometry(QRect(460, 390, 101, 31));
        SaveImage = new QPushButton(centralwidget);
        SaveImage->setObjectName(QString::fromUtf8("SaveImage"));
        SaveImage->setGeometry(QRect(890, 390, 101, 31));
        Poza_OG = new QLabel(centralwidget);
        Poza_OG->setObjectName(QString::fromUtf8("Poza_OG"));
        Poza_OG->setGeometry(QRect(10, 40, 480, 320));
        Poza_OG->setMinimumSize(QSize(480, 320));
        Poza_OG->setMaximumSize(QSize(480, 320));
        Poza_OG->setScaledContents(true);
        Poza_FILT = new QLabel(centralwidget);
        Poza_FILT->setObjectName(QString::fromUtf8("Poza_FILT"));
        Poza_FILT->setGeometry(QRect(530, 40, 480, 320));
        Poza_FILT->setMinimumSize(QSize(480, 320));
        Poza_FILT->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        LoadImage->setText(QCoreApplication::translate("MainWindow", "Incarca Imagine", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Imaginea initiala", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Imaginea filtrata", nullptr));
        ApplyFilter->setText(QCoreApplication::translate("MainWindow", "Aplica filtru", nullptr));
        SaveImage->setText(QCoreApplication::translate("MainWindow", "Salvare Imagine", nullptr));
        Poza_OG->setText(QString());
        Poza_FILT->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
