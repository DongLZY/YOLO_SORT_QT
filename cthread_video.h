#ifndef CTHREAD_VIDEO_H
#define CTHREAD_VIDEO_H

#include <QThread>
#include <QtDebug>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QTime>
#include <QElapsedTimer>
#include "cv_detector.h"
#include "tracker.h"
#include "utils.h"

using namespace cv;

class Cthread_video : public QThread
{
    Q_OBJECT

public:
    explicit Cthread_video(QThread *parent = nullptr);

    void closeCamera();     // 关闭摄像头。

private:
    void run();
    QImage fromBGR2Image(cv::Mat oriMat);
    std::string get_csi_pipeline(int capture_width, int capture_height, int display_width , int display_height, int framerate);
    std::string get_usb_pipeline(int capture_width, int capture_height);
    int capture_width=640;
    int capture_height=480;

    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);

    std::string pipeline;
    VideoCapture capture;// 视频获取结构， 用来作为视频获取函数的一个参数
    Mat frame;
    QImage oriImg;
    bool flag = 1;

    const string darknet_cfg = "./face_model/face.cfg";           //网络文件
    const string darknet_weights = "./face_model/face.weights";   //模型文件
    const string darknet_names = "./face_model/face.names";       //类别文件

    std::vector<std::string> class_labels ;//类标签


    void loadWeights();
    void getLabels();
    vector<vector<Point>> vecPoint;


signals:

    void sendOriImg(QImage oriImg);

};

#endif // CTHREAD_VIDEO_H
