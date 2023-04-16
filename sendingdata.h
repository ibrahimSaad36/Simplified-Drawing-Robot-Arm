#ifndef SENDINGDATA_H
#define SENDINGDATA_H

#include <QMainWindow>
#include "imageprocessing.h"
#include "serialcommunication.h"
#include <thread>

namespace Ui {
class SendingData;
}

class SendingData : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendingData(QWidget *parent = nullptr);
    ~SendingData();

    void setSerialObject (SerialCommunication* serial, ImageProcessing* img);
    void sendCords();

private slots:
    void on_butCancelDataSending_clicked();

    void on_butStartDataSending_clicked();

private:
    Ui::SendingData *ui;
};

#endif // SENDINGDATA_H
