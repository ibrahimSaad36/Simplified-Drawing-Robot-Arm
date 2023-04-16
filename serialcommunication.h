#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <QProgressBar>

class SerialCommunication
{
private:
    HANDLE myCom;
    DCB dcb;
    bool state;
    std::string portName;
    int portSpeed;
public:
    int contoursSendingCounter = 0;
    QProgressBar* sendProgress;
    SerialCommunication(std::string port, int speed);
    void connect();
    bool status();
    void sendData(std::vector<std::vector<cv::Point>> contourCoordinates);
    void closePort();
    void setSendProgressBar(QProgressBar* progress);
    void setPortName(std::string newName);
};

#endif // SERIALCOMMUNICATION_H
