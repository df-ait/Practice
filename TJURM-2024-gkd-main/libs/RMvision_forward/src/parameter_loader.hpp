#ifndef LOADER_CPP
#define LOADER_CPP

#ifdef Status
#undef Status
#endif
#include <iostream>
// opencv
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>

#ifdef Success
#undef Success
#endif

#include <Eigen/Dense>  


typedef struct
{
    /*推理参数*/
    std::string model_path_xml; //ok
    std::string model_path_bin; //ok
    float conf_threshold;   //ok
    int rect_cut = 1;       //ok
    /*标定参数*/
    int boardSize_h;        //ok
    int boardSize_w;        //ok
    float squareSize;       //ok
    int img_count;          //ok
    int sample_period;      //ok
    std::string calib_yaml_path;    //ok
    std::string camera_extrinsics_path;
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
    /*相机参数*/
    cv::Mat intrinsic_matrix;
    cv::Mat distortion_coeffs;
    Eigen::Matrix3d rotate_pnp2hea;
    Eigen::Matrix4d trans_pnp2head;
    /*赛前新增*/
    int shoot_speed = 0;
    int is_camreverse = 0;
    int is_filted = 1;
    int is_imshow = 0;
    int is_pose_out = 0;
    int is_target_out = 0;
    int sentry_head_type = 0;


} parameter_loader_t;


extern int para_load(std::string filepath);

extern parameter_loader_t params;

#endif
