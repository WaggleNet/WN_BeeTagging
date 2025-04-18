#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>

const cv::Scalar BOX_BGR(255, 0, 0);
// PROTOTYPE & CONCEPT
// returns (x, y)
std::pair<double,double> findBoxOffsetInches(const cv::Mat& img, double inchesPerPixel) // THIS IS ONLY FOR FINDING THE BEE FROM ORIGIN
{
    cv::Mat mask;
    cv::inRange(img, BOX_BGR, BOX_BGR, mask);

    cv::morphologyEx(mask, mask, cv::MORPH_OPEN,  cv::Mat(), cv::Point(-1,-1), 1);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), 1);


    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if (contours.empty()) 
    {
        throw std::runtime_error("Drawn box not detected in image."); // Testing purposes only -> potentially have it return & use while loop to rerun in main...?
    }

    size_t best = 0;
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            best = i;
        }
    }

    cv::Rect bb = cv::boundingRect(contours[best]);
    double cx = bb.x + bb.width  * 0.5;
    double cy = bb.y + bb.height * 0.5;

    double dx = cx;
    double dy = img.rows - cy;

    return { dx * inchesPerPixel, dy * inchesPerPixel };
}