#include "cv_detector.h"

CvDetector::CvDetector(string cfg_path, string weights_path, int model_inputSize)
{

    load_model(cfg_path,weights_path);
    input_size = model_inputSize;

}

void CvDetector::load_model( string darknet_cfg, string darknet_weights){

    net = cv::dnn::readNetFromDarknet(darknet_cfg, darknet_weights);

//    net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
//    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    cout << "LODING MODEL!"<< endl;
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

}

void CvDetector::predict(cv::Mat frame, vector<int>& classId, vector<float>& confidence, vector<cv::Rect>& box, float confThreshold, float nmsThreshold){

    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0 / 255.0, { input_size, input_size }, 0.00392, true);
    net.setInput(blob);
    // 检测
    net.forward(detectionMat, getOutputsNames(net));// 6 845 1 W x H x C

    vector<int> pre_classIds;
    vector<float> pre_confidences;
    vector<cv::Rect> pre_boxes;

    for (size_t i = 0; i < detectionMat.size(); ++i)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float* data = (float*)detectionMat[i].data;
        for (int j = 0; j < detectionMat[i].rows; ++j, data += detectionMat[i].cols)
        {
            cv::Mat scores = detectionMat[i].row(j).colRange(5, detectionMat[i].cols);
            cv::Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                pre_classIds.push_back(classIdPoint.x);
                pre_confidences.push_back((float)confidence);
                pre_boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

        // Perform non maximum suppression to eliminate redundant overlapping boxes with
            // lower confidences

            cv::dnn::NMSBoxes(pre_boxes, pre_confidences, confThreshold, nmsThreshold, indices);

            for (size_t i = 0; i < indices.size(); ++i)
            {
                int idx = indices[i];
                box.push_back(pre_boxes[idx]);
                classId.push_back(pre_classIds[idx]);
                confidence.push_back(pre_confidences[idx]);
            }
}

// Get the names of the output layers
vector<string> CvDetector::getOutputsNames(const cv::dnn::Net& net)
{
        static vector<string> names;
        if (names.empty())
        {
                //Get the indices of the output layers, i.e. the layers with unconnected outputs
                vector<int> outLayers = net.getUnconnectedOutLayers();

                //get the names of all the layers in the network
                vector<string> layersNames = net.getLayerNames();

                // Get the names of the output layers in names
                names.resize(outLayers.size());
                for (size_t i = 0; i < outLayers.size(); ++i)
                        names[i] = layersNames[outLayers[i] - 1];
        }
        return names;
}
