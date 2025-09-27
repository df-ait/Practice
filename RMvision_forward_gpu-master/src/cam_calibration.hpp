#ifndef CALIB_H
#define CALIB_H


#include <iostream>

// opencv
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>

// cam_driver
#include "HIKdriver.hpp"

typedef struct
{
    cv::Mat frame;  //当前帧的原始图像
    cv::Mat frame_gray; //当前帧的灰度图像
    std::vector<cv::Mat> frame_calib; //合格的标定图像序列
    cv::VideoCapture cam;   //相机或者视频流的控制器，用于帧捕获
    int sample_period_count = 0;    //采样计数器，记录自上次保存标定帧后的帧数（控制采集间隔）
    int cam_id = 0;             //相机ID
    long int plate_lasttime = 0;    //上次检测到标定板的时间
    int image_sample_isok = 0;      //标定板采集是否成功
    std::string video_path;     //或，视频文件路径
    std::vector<std::vector<cv::Point3f>> objectPoints;//3D标定板角点
    std::vector<std::vector<cv::Point2f>> imagePoints;//2D图像角点
    std::vector<cv::Point2f> corners;//检测到的角点
    std::vector<cv::Point3f> objP;//棋盘格的3D坐标
}camera_cali_type;

class camrea_calibtation
{
private:
    /* data */
public:
    camera_cali_type camrea;
    cv::Mat mtx, dist;//相机内参矩阵(mtx)和畸变系数(dist)
    std::vector<cv::Mat> rvecs, tvecs;// 每张标定图的旋转/平移向量

    /*************** calibration settings ****************/
    //TODO
    cv::Size boardSize; // 棋盘格的尺寸
    float squareSize = 20.0f; // 每格的大小，单位mm
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<cv::Point2f> corners;
    // 创建棋盘格的3D点
    std::vector<cv::Point3f> objP;
    
    void init();
    int image_add(cv::Mat frame);

    camrea_calibtation(/* args */);
    ~camrea_calibtation();
};




extern int calibration_main();
extern cv::Mat rect_cut(cv::Mat image);
#endif