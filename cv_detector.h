#ifndef CV_DETECTOR_H
#define CV_DETECTOR_H
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

using namespace std;

class CvDetector
{
public:
    CvDetector(string , string, int model_inputSize = 416);

    cv::dnn::Net net;
    void load_model(string, string);
    //define the inference function
    void predict(cv::Mat src, vector<int>& classIds, vector<float>& confidences, vector<cv::Rect>& boxes,
                 float confThreshold = 0.25, float nmsThreshold= 0.4);
    int input_size;

    std::vector<cv::Mat> detectionMat;
    vector<int> indices;
//    vector<int> classIds;
//    vector<float> confidences;
//    vector<cv::Rect> boxes;
    vector<string> getOutputsNames(const cv::dnn::Net& net);

    vector<vector<int>> results;


private:










};


#endif // CV_DETECTOR_H
