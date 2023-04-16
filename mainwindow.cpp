#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "customizecannydetection.h"
#include "serialcommunication.h"
#include "sendingdata.h"
#include <QDir>

using namespace std;
using namespace cv;

ImageProcessing* imageProcessing;
SerialCommunication* serialPort;
bool imageLoaded = false, isResizeSelected, isConnectPressed = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditResizeFactor->setVisible(false);
    this->setFixedSize(612, 479);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_butChooseImage_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open an image");
    ui->labelImagePath->setText(path);
    string imagePath = path.toStdString();
    imageProcessing = new ImageProcessing(imagePath);
    if (!imageProcessing->imageValid())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The Choosed Image Isn't Valid, make sure you choosed an image and check if it's available");
        msgBox.exec();
        imageLoaded = false;
    }
    else
        imageLoaded = true;
}

void MainWindow::on_butGrayImage_clicked()
{
    if (imageLoaded)
    {
        Mat gray;
        float factor;
        if (isResizeSelected)
        {
            if (ui->lineEditResizeFactor->text()=="")
            {
                QMessageBox::warning(this, "Choose Resize Factor", " Write the factor to which you want the image to be resized!");
                return;
            }
            else
            {
                factor = ui->lineEditResizeFactor->text().toFloat();
                imageProcessing->imageResize(factor);
            }
        }
        else
            imageProcessing->imageResized = false;
        if (ui->checkBoxFaceDetection->isChecked())
        {
            imageProcessing->faceDetected();
            imageProcessing->crobToFace();
            gray = imageProcessing->imageGray();
            imshow("Gray Image", gray);
            waitKey(0);
        }
        else
        {
            gray = imageProcessing->imageGray();
            imshow("Gray Image", gray);
            waitKey(0);
        }
    }
    else
        QMessageBox::warning(this, "Image isn't available", "Make sure that you choosed available image");
}

void MainWindow::on_checkBoxResizeImage_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        ui->lineEditResizeFactor->setVisible(false);
        isResizeSelected = false;
    }
    else
    {
        ui->lineEditResizeFactor->setVisible(true);
        isResizeSelected = true;
    }
}

void MainWindow::on_butViewContours_clicked()
{
    Mat drawing, gray;
    float factor;
    if (imageLoaded)
    {
         if (isResizeSelected)
         {
             if (ui->lineEditResizeFactor->text()=="")
             {
                 QMessageBox::warning(this,"Choose Resize Factor", "Write the factor to which you want the image to be resized!");
                 return;
             }
             else
             {
                 factor = ui->lineEditResizeFactor->text().toFloat();
                 imageProcessing->imageResize(factor);
             }
         }
         else
             imageProcessing->imageResized = false;
         if (ui->radioButtonCannyContours->isChecked())
         {
             if (ui->checkBoxFaceDetection->isChecked())
             {
                 imageProcessing->faceDetected();
                 imageProcessing->crobToFace();
                 imageProcessing->imageGray();
                 imageProcessing->imageCannyContours();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
             else
             {
                 imageProcessing->imageGray();
                 imageProcessing->imageCannyContours();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
         }
         else if (ui->radioButtonContoursOnly->isChecked())
         {
             if (ui->checkBoxFaceDetection->isChecked())
             {
                 imageProcessing->faceDetected();
                 imageProcessing->crobToFace();
                 imageProcessing->imageGray();
                 imageProcessing->imageContoursOnly();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
             else
             {
                 imageProcessing->imageGray();
                 imageProcessing->imageContoursOnly();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
         }
         else
         {
             if (ui->checkBoxFaceDetection->isChecked())
             {
                 imageProcessing->faceDetected();
                 imageProcessing->crobToFace();
                 imageProcessing->imageGray();
                 imageProcessing->imageContoursOnly();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
             else
             {
                 imageProcessing->imageGray();
                 imageProcessing->imageContoursOnly();
                 drawing = imageProcessing->drawingContours();
                 imshow("Contours Image", drawing);
                 waitKey(0);
             }
         }

    }
    else
        QMessageBox::warning(this, "Image isn't available", "Make sure that you choosed available image");
}

void MainWindow::on_checkBoxFaceDetection_stateChanged(int arg1)
{
    if (arg1 == 0)
        imageProcessing->faceDetection = false;
    else
        imageProcessing->faceDetection = true;
}

void MainWindow::on_butCustomizeCanny_clicked()
{
    if (!imageLoaded)
        QMessageBox::warning(this, "Image isn't available", "Make sure that you choosed available image");
    else
    {
        CustomizeCannyDetection* customizeForm = new CustomizeCannyDetection;
        customizeForm->setWindowModality(Qt::ApplicationModal);
        customizeForm->setImageObject(imageProcessing);
        customizeForm->show();
    }
}

void MainWindow::on_butViewContours_2_clicked()
{
    float factor;
    if (!imageLoaded)
        QMessageBox::warning(this,"Image isn't available", "Make sure that you choosed available image");
    else
    {
        if (isResizeSelected)
        {
            if (ui->lineEditResizeFactor->text()=="")
            {
                QMessageBox::warning(this, "Type resize factor", "Write the factor to which you want the image to be resized !");
                return;
            }
            else
            {
                factor = ui->lineEditResizeFactor->text().toFloat();
                imageProcessing->imageResize(factor);
            }
        }
        else
            imageProcessing->imageResized = false;
        if (ui->checkBoxFaceDetection->isChecked())
        {
            imageProcessing->faceDetected();
            imageProcessing->crobToFace();
            imageProcessing->imageGray();
            imshow("Canny Image", imageProcessing->imageCannyContours());
            waitKey(0);
        }
        else
        {
            imageProcessing->imageGray();
            imshow("Canny Image", imageProcessing->imageCannyContours());
            waitKey(0);
        }
    }
}


void MainWindow::on_butPortConnect_clicked()
{
    if (imageLoaded)
    {
        QString str;
        string tmp;
        string portName;
        string previousPortName;
        if (ui->lineEditPortName->text() == "")
            QMessageBox::warning(this, "ERROR", "Enter The Port Name !");
        else
        {
            if (isConnectPressed)
            {
                str = ui->lineEditPortName->text();
                tmp = str.toStdString();
                portName = tmp;
                if (previousPortName == portName)
                     QMessageBox::warning(this,"Already Connected", "The program is already connected to the typed port");
                else
                {
                    serialPort->closePort();
                    serialPort = new SerialCommunication(portName, 9600);
                    previousPortName = portName;
                    serialPort->connect();
                    if (serialPort->status())
                    {
                        QMessageBox::information(this, "Connected", "The program connected successfuly to the entered port !");
                        isConnectPressed = true;
                    }
                }
            }
            else
            {
                str = ui->lineEditPortName->text();
                tmp = str.toStdString();
                portName = tmp;
                serialPort = new SerialCommunication(portName, 9600);
                previousPortName = portName;
                serialPort->connect();
                if (serialPort->status())
                {
                    QMessageBox::information(this, "Connected", "The program connected successfuly to the entered port !");
                    isConnectPressed = true;
                }
            }
        }
    }
    else
        QMessageBox::warning(this, "ERROR", "Load image firsly and choose your options before connecting the port !");
}

void MainWindow::on_butSendData_clicked()
{
    if (!imageLoaded)
        QMessageBox::warning(this, "ERROR", "Load image firstly and connect to the port before that !");
    else if (!isConnectPressed)
        QMessageBox::warning(this, "ERROR", "Connect to the port firstly !");
    else
    {
        SendingData* send = new SendingData;
        send->setWindowModality(Qt::ApplicationModal);
        send->setSerialObject(serialPort, imageProcessing);
        send->show();
    }
}

void MainWindow::on_butCheckIfAllInside_clicked()
{
    float factor;
    int countXOutside = 0, countYOutside = 0;
    QString xOutside, yOutside;
    if (!imageLoaded)
        QMessageBox::warning(this, "ERROR", "Load the image firstly and choose your options !");
    else
    {
        countXOutside = 0;
        countYOutside = 0;
        if (isResizeSelected)
        {
            if (ui->lineEditResizeFactor->text()=="")
            {
                QMessageBox::warning(this, "Type resize factor", "Write the factor to which you want the image to be resized !");
                return;
            }
            else
            {
                factor = ui->lineEditResizeFactor->text().toFloat();
                imageProcessing->imageResize(factor);
            }
        }
        else
            imageProcessing->imageResized = false;
        if (ui->checkBoxFaceDetection->isChecked())
        {
            imageProcessing->faceDetected();
            imageProcessing->crobToFace();
            imageProcessing->imageGray();
            imageProcessing->imageCannyContours();
            for (int i = 0; i < imageProcessing->contours.size(); i++)
            {
                for (int j = 0; j < imageProcessing->contours[i].size(); j++)
                {
                    if (imageProcessing->contours[i][j].x > 300)
                    countXOutside += 1;
                    if (imageProcessing->contours[i][j].y > 480)
                    countYOutside += 1;
                }
            }
            xOutside = QString::number(countXOutside);
            yOutside = QString::number(countYOutside);
            QMessageBox::information(this, "Check Points", "There are "+ xOutside + " points as they are larger than area width and "+ yOutside + " points as they are larger than area height");
         }
        else
        {
            imageProcessing->imageGray();
            imageProcessing->imageCannyContours();
            for (int i = 0; i < imageProcessing->contours.size(); i++)
            {
                for (int j = 0; j < imageProcessing->contours[i].size(); j++)
                {
                    if (imageProcessing->contours[i][j].x > 300)
                    countXOutside += 1;
                    if (imageProcessing->contours[i][j].y > 480)
                    countYOutside += 1;
                }
            }
            xOutside = QString::number(countXOutside);
            yOutside = QString::number(countYOutside);
            QMessageBox::information(this, "Check Points", "There are "+ xOutside + " points are larger than area width and "+ yOutside + " points are larger than area height");
        }
    }
}
