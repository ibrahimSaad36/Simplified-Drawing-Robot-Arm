#include "customizecannydetection.h"
#include "ui_customizecannydetection.h"


using namespace cv;
using namespace std;


QString minThres, maxThres;
bool showCannyClicked = false;
Mat resizedCannyImg;
ImageProcessing* imageProcess;

CustomizeCannyDetection::CustomizeCannyDetection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomizeCannyDetection)
{
    ui->setupUi(this);
    this->setFixedSize(547, 317);
}

CustomizeCannyDetection::~CustomizeCannyDetection()
{
    delete ui;
}

void CustomizeCannyDetection::setImageObject(ImageProcessing* img)
{
    imageProcess = img;
    minThres = QString::fromStdString(to_string(imageProcess->minThreshold));
    maxThres = QString::fromStdString(to_string(imageProcess->maxThreshold));
    ui->sliderMinThreshold->setValue(imageProcess->minThreshold);
    ui->sliderMaxThreshold->setValue(imageProcess->maxThreshold);
    ui->labelMinThreshold->setText(minThres);
    ui->labelMaxThreshold->setText(maxThres);
}

void CustomizeCannyDetection::on_sliderMinThreshold_valueChanged(int value)
{
    imageProcess->minThreshold = value;
    minThres = QString::fromStdString(to_string(imageProcess->minThreshold));
    ui->labelMinThreshold->setText(minThres);
    if (value != 50)
    {
        if (imageProcess->imageAfterCanny.empty())
        imageProcess->imageGray();
        imshow("Customize Canny Image", imageProcess->imageCannyContours());
        waitKey(1);
    }
}

void CustomizeCannyDetection::on_sliderMaxThreshold_valueChanged(int value)
{
    imageProcess->maxThreshold = value;
    maxThres = QString::fromStdString(to_string(imageProcess->maxThreshold));
    ui->labelMaxThreshold->setText(maxThres);
    if (value != 100)
    {
        if (imageProcess->imageAfterCanny.empty())
            imageProcess->imageGray();
        imshow("Customize Canny Image", imageProcess->imageCannyContours());
        waitKey(1);
    }
}

void CustomizeCannyDetection::on_butViewCannyImage_clicked()
{
    if (imageProcess->imageAfterCanny.empty())
    {
        imageProcess->imageGray();
        imshow("Customize Canny Image", imageProcess->imageCannyContours());
        waitKey(0);
    }
    else
    {
        imshow("Customize Canny Image", imageProcess->imageCannyContours());
        waitKey(0);
    }
}
