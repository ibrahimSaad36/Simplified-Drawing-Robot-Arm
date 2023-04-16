#include "imageprocessing.h"

using namespace std;
using namespace cv;

ImageProcessing::ImageProcessing(string path)
{
    sourceImage = imread(path);
    faceDetection = false;
    cannyEdgeContour = false;
    imageResized = false;
    minThreshold = 50;
    maxThreshold = 100;
}
bool ImageProcessing::imageValid()
{
    if(sourceImage.empty())
        return false;
    else
        return true;
}
void ImageProcessing::imageResize(float factor)
{
    resize(sourceImage, resizedImage, Size(), factor, factor);
    imageResized = true;
}
void ImageProcessing::faceDetected()
{
    if (!face.load("D:/harscades/harscades/haarcascade_frontalface_default.xml"))
    {
        QMessageBox msg;
        msg.setText(" The XML File \"haarcascade_frontalface_default.xml\" isn't loaded successfuly");
        msg.show();
        msg.exec();
        return;
    }
    if (imageResized)
        face.detectMultiScale(resizedImage, recognizedFace);
    else
        face.detectMultiScale(sourceImage, recognizedFace);
    faceDetection = true;
}
void ImageProcessing::crobToFace()
{
    Rect cropedArea;
    for (int i = 0; i < recognizedFace.size(); i++)
    {
        Point p1(recognizedFace[i].x, recognizedFace[i].y);
        Point p2((recognizedFace[i].x + recognizedFace[i].height), (recognizedFace[i].y + recognizedFace[i].width));
        cropedArea = Rect(p1, p2);
        if (imageResized)
            faceCropedImage = resizedImage(cropedArea);
        else
            faceCropedImage = sourceImage(cropedArea);
    }
}
Mat ImageProcessing::imageGray()
{
    if (faceDetection)
        cvtColor(faceCropedImage, grayImage, COLOR_BGR2GRAY);
    else
    {
        if (imageResized)
            cvtColor(resizedImage, grayImage, COLOR_BGR2GRAY);
        else
            cvtColor(sourceImage, grayImage, COLOR_BGR2GRAY);
    }
    return grayImage;
}
Mat ImageProcessing::imageCannyContours()
{
    Mat drawing;
    Canny(grayImage, imageAfterCanny, minThreshold, maxThreshold, 3, true);
    findContours(imageAfterCanny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    bitwise_not(imageAfterCanny, drawing);
    cannyEdgeContour = true;
    return drawing;
}
void ImageProcessing::imageContoursOnly()
{
    GaussianBlur(grayImage, bluredImage, Size(5, 5), 0);
    threshold(bluredImage, thresholdImage, minThreshold, maxThreshold, THRESH_BINARY | THRESH_OTSU);
    findContours(thresholdImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    cannyEdgeContour = false;
}
Mat ImageProcessing::drawingContours()
{
    RNG rng(12345);
    Mat drawing;
    if (cannyEdgeContour)
        drawing = Mat::zeros(imageAfterCanny.size(), CV_8UC3);
    else
        drawing = Mat::zeros(thresholdImage.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }
    return drawing;
}
Mat ImageProcessing::getCannyImage()
{
    return imageAfterCanny;
}
int ImageProcessing::getContoursSize()
{
    return contours.size();
}
