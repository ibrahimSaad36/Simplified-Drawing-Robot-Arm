#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageprocessing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_butChooseImage_clicked();

    void on_butGrayImage_clicked();

    void on_checkBoxResizeImage_stateChanged(int arg1);

    void on_butViewContours_clicked();

    void on_checkBoxFaceDetection_stateChanged(int arg1);

    void on_butCustomizeCanny_clicked();

    void on_butViewContours_2_clicked();

    void on_butPortConnect_clicked();

    void on_butSendData_clicked();

    void on_butCheckIfAllInside_clicked();

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
