#ifndef LOADER_CPP
#define LOADER_CPP

#ifdef Status
#undef Status
#endif

#include <iostream>
// opencv
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>


typedef struct
{
    /*推理参数*/
    std::string model_path_xml; //ok // 模型XML文件路径（如OpenVINO格式）
    std::string model_path_bin; //ok // 模型BIN文件路径
    float conf_threshold;   //ok // 目标检测的置信度阈值
    int rect_cut = 1;       //ok // 是否启用图像裁剪（1=启用）
    /*标定参数*/
    int boardSize_h;        //ok
    int boardSize_w;        //ok
    float squareSize;       //ok
    int img_count;          //ok
    int sample_period;      //ok
    std::string calib_yaml_path;    //ok
    /*相机*/
    float cam_gain;         //ok
    int cam_exptime;        //ok
    float framerate;        //ok
    /*其他*/
    int imshow_en;          //ok
    int debug_info;         //not used
    float armor_small_h;    //小装甲板高    ok
    float armor_small_w;    //小装甲板宽    ok
    float armor_large_h;    //大装甲板高    ok
    float armor_large_w;    //大装甲板宽    ok

} parameter_loader_t;


extern int para_load(std::string filepath);

extern parameter_loader_t params;

#endif
