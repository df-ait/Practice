#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "无法打开摄像头" << endl;
        return -1;
    }
    
    cout << "摄像头测试 - 按ESC退出" << endl;
    
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        
        // 显示帧信息
        string info = "Frame: " + to_string(frame.cols) + "x" + to_string(frame.rows);
        putText(frame, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        putText(frame, "Press ESC to exit", Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        
        imshow("Camera Test", frame);
        
        if (waitKey(1) == 27) break;
        cout << "摄像头帧率: " << cap.get(CAP_PROP_FPS) << endl;
    }
    cout << "OpenCV版本: " << CV_VERSION << endl;
    cout << "测试完成" << endl;
    return 0;
}