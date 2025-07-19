@startuml

class SerialCommunication
{
    + contoursSendingCounter : int
    + sendProgress : QProgressBar*
    + SerialCommunication(port : std::string, speed : int)
    + connect() : void
    + status() : bool
    + sendData(contourCoordinates : std::vector<std::vector<cv::Point>>) : void
    + closePort() : void
    + setSendProgressBar(progress : QProgressBar*) : void
    + setPortName(newName : std::string) : void
    - myCom : HANDLE
    - dcb : DCB
    - state : bool
    - portName : std::string
    - portSpeed : int
}

class ImageProcessing
{
    + sourceImage : cv::Mat
    + resizedImage : cv::Mat
    + imageAfterCanny : cv::Mat
    + grayImage : cv::Mat
    + blurredImage : cv::Mat
    + thresholdedImage : cv::Mat
    + faceCropedImage : cv::Mat
    + face : cv::CascadeClassifier
    + recognizedFace : std::vector <cv::Rect>
    + contours : std::vector<std::vector<cv::Point>>
    + hierarchy : std::vector<cv::Vec4i>
    + minThreshold : int
    + maxThreshold : int
    + minThresholdLoc : int*
    + maxThresholdLoc : int*
    + faceDetection : bool
    + cannyEdgeDetection : bool
    + imageResized : bool
    + ImageProcessing(path : std::string)
    + imageValid() : bool
    + imageResize() : void
    + faceDetected() : void
    + crobToFace() : void
    + imageGray() : cv::Mat
    + getCannyImage() : cv::Mat
    + imageContoursOnly() : void
    + drawingContours() : cv::Mat
    + imageCannyContours() : cv::Mat
    + getContoursSize() : int
}

class QMainWindow <<external>>

class MainWindow <<boundary>> 
{
    + MainWindow(parent: QWidget* = nullptr)
    + ~MainWindow()
    --
    - ui: Ui::MainWindow*
}

class CustomizeCannyDetection <<boundary>> 
{
    + CustomizeCannyDetection(parent: QWidget* = nullptr)
    + ~CustomizeCannyDetection()
    + setImageObject(img: ImageProcessing*)
    --
    - ui: Ui::CustomizeCannyDetection*
}

class SendingData <<boundary>>
{
    + SendingData(parent: QWidget* = nullptr)
    + ~SendingData()
    + setSerialObject(serial: SerialCommunication*, img: ImageProcessing*)
    + sendCords() : void
}

CustomizeCannyDetection -up-|> QMainWindow
MainWindow -up-|> QMainWindow
SendingData -up-|> QMainWindow

SendingData .. SerialCommunication
SendingData .. ImageProcessing
CustomizeCannyDetection .. ImageProcessing

SerialCommunication --* HANDLE
note "Handle to an open file object. Windows.h" as N1
HANDLE .. N1

SerialCommunication --* DCB
note "Device Control Block, a structure that contains information about the serial port. (Windows.h)" as N2
DCB .. N2

SerialCommunication --o QProgressBar
note "Qt widget for displaying progress." as N3
QProgressBar .. N3

SerialCommunication --o Point
note "Vector of vectors to hold contour coordinates." as N4
Point .. N4

ImageProcessing --* Mat
note "OpenCV Matrix" as N5
Mat .. N5

ImageProcessing --* CascadeClassifier
note "OpenCV class for object detection using Haar cascades." as N6
CascadeClassifier .. N6

ImageProcessing --* Rect
note "OpenCV class for representing rectangles." as N7
Rect .. N7

ImageProcessing --* Point
note "OpenCV class for representing points." as N8
Point .. N8

ImageProcessing --* Vec4i
note "OpenCV class for representing 4-element vectors." as N9
Vec4i .. N9

@enduml