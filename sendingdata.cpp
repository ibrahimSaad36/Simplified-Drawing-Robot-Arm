#include "sendingdata.h"
#include "ui_sendingdata.h"

using namespace std;
using namespace cv;

float progressValue = 0;

SerialCommunication* serialPortSend;
ImageProcessing* imageProcessingSend;

SendingData::SendingData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendingData)
{
    ui->setupUi(this);
    this->setFixedSize(483, 139);
}

SendingData::~SendingData()
{
    delete ui;
}

void SendingData::setSerialObject(SerialCommunication* serial, ImageProcessing* img)
{
    serialPortSend = serial;
    imageProcessingSend = img;
}

void SendingData::on_butCancelDataSending_clicked()
{
    this->hide();
}

void SendingData::sendCords()
{
    serialPortSend->setSendProgressBar(ui->progressBarSendData);
    if (imageProcessingSend->imageAfterCanny.empty())
    {
        imageProcessingSend->imageGray();
        imageProcessingSend->imageCannyContours();
        if (serialPortSend->status())
            serialPortSend->sendData(imageProcessingSend->contours);
    }
    else
    {
        if (serialPortSend->status())
            serialPortSend->sendData(imageProcessingSend->contours);
    }
}
void SendingData::on_butStartDataSending_clicked()
{

}
