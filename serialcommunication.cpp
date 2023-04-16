#include "serialcommunication.h"
using namespace std;
using namespace cv;

SerialCommunication::SerialCommunication(string port, int speed)
{
    portName = port;
    portSpeed = speed;
    state = false;
}
void SerialCommunication::setPortName(string newName)
{
    portName = newName;
}
void SerialCommunication::connect()
{
    QMessageBox msg;
    msg.setWindowTitle("ERROR");
    msg.setIcon(QMessageBox::Warning);
    myCom = CreateFileA(static_cast <LPCSTR> (portName.c_str()), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (myCom == INVALID_HANDLE_VALUE)
    {
        msg.setText("There is an error while opening the port, check if the port isn't busy and its name is correct");
        msg.exec();
        state = false;
        return;
    }
    if (!GetCommState(myCom, &dcb))
    {
        msg.setText("There is an error while getting the port parameters");
        msg.exec();
        state = false;
        return;
    }
    dcb.DCBlength = sizeof(dcb);
    dcb.BaudRate = portSpeed;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = TWOSTOPBITS;
    if (!SetCommState(myCom, &dcb))
    {
        msg.setText("There is an error while setting the port parameters");
        msg.exec();
        state = false;
        return;
    }
    PurgeComm(myCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
    state = true;
}
bool SerialCommunication::status()
{
    return state;
}
void SerialCommunication::sendData(vector<vector<cv::Point>> contourCoordinates)
{
    string x, y, contoursSize, contourPoints;
    contoursSize = to_string(contourCoordinates.size());
    WriteFile(myCom, contoursSize.c_str(), 8, NULL, NULL);
    sendProgress->setValue(1);
    for (int i = 0; i < contourCoordinates.size(); i++)
    {
        sendProgress->setValue(3);
        if (state)
        {
            contourPoints = to_string(contourCoordinates[i].size());
            WriteFile(myCom, contourPoints.c_str(), 8, NULL, NULL);
            for (int j = 0; j < contourCoordinates[i].size(); j++)
            {
                x = to_string(contourCoordinates[i][j].x);
                y = to_string(contourCoordinates[i][j].y);
                WriteFile(myCom, x.c_str(), 8, NULL, NULL);
                WriteFile(myCom, y.c_str(), 8, NULL, NULL);
                //Sleep(500);
            }
        }
        else
        {
            QMessageBox msg;
            msg.setWindowTitle("ERROR");
            msg.setIcon(QMessageBox::Warning);
            msg.setText("Make sure that the program is still connected to the port");
            msg.exec();
            return;
        }
        contoursSendingCounter += 1;
    }
    sendProgress->setValue(50);
    Sleep(100);
    sendProgress->setValue(55);
    Sleep(100);
    sendProgress->setValue(65);
    Sleep(100);
    sendProgress->setValue(70);
    Sleep(100);
    sendProgress->setValue(80);
    Sleep(110);
    sendProgress->setValue(95);
    Sleep(150);
    sendProgress->setValue(100);
}
void SerialCommunication::closePort()
{
    CloseHandle(myCom);
    state = false;
}
void SerialCommunication::setSendProgressBar(QProgressBar *progress)
{
    sendProgress = progress;
}
