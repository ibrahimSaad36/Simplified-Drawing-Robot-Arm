#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <QMessageBox>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <opencv2/core.hpp>
#include <vector>

class ImageProcessing
{
public:
    cv::Mat sourceImage, resizedImage;
    cv::Mat imageAfterCanny;
    cv::Mat grayImage, bluredImage, thresholdImage, faceCropedImage;
    cv::CascadeClassifier face;
    std::vector <cv::Rect> recognizedFace;
    std::vector <std::vector<cv::Point>> contours;
    std::vector <cv::Vec4i> hierarchy;
    int minThreshold;
    int maxThreshold;
    int* minThresholdLoc = &minThreshold;
    int* maxThresholdLoc = &maxThreshold;
    bool faceDetection;
    bool cannyEdgeContour;
    bool imageResized;
    ImageProcessing(std::string path);
    bool imageValid();
    void imageResize(float factor);
    void faceDetected();
    void crobToFace();
    cv::Mat imageGray();
    cv::Mat getCannyImage();
    void imageContoursOnly();
    cv::Mat drawingContours();
    cv::Mat imageCannyContours();
    int getContoursSize();
};

#endif // IMAGEPROCESSING_H
