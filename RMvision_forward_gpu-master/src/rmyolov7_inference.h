#ifndef GMASTER_CV_2023_ARMORNEWYOLO_H
#define GMASTER_CV_2023_ARMORNEWYOLO_H

#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <openvino/openvino.hpp>
// #include <inference_engine.hpp>
// using namespace InferenceEngine;

#define NMS_THRESHOLD 0.10f //NMS参数
#define CONF_THRESHOLD_D 0.35f //置信度参数
#define CONF_REMAIN 0.0 //保留一帧保留的权重比例，如果不保留填写为0
#define IMG_SIZE  640  //推理图像大小，如果不是640 和 416 需要自己在下面添加anchor
#define ANCHOR 3 //anchor 数量
#define DETECT_MODE 0 //ARMOR 0 WIN 1 BOARD 2
#define DEVICE "GPU" // 设备选择
// #define VIDEO //是否展示推理视频

#if DETECT_MODE == 0 // 装甲板四点模型
#define KPT_NUM 4   //装甲板角点
#define CLS_NUM 14  //14个类别的装甲板
/*TODO*/
// #define MODEL_PATH_D "../models/rmyolo-v7-best/distilbert.xml","../models/rmyolo-v7-best/distilbert.bin"
// #define MODEL_PATH_D "../models/RMyolo-v7-new/RMyolov7-new.xml","../models/RMyolo-v7-new/RMyolov7-new.bin"
// #define MODEL_PATH_D "../models/RMyolov7-best-fp32/rmyolo-v7-best.xml","../models/RMyolov7-best-fp32/rmyolo-v7-best.bin"
// #define MODEL_PATH_D "../models/RMyolo-v7-new-fp32/RMyolov7-new.xml","../models/RMyolo-v7-new-fp32/RMyolov7-new.bin"

#elif DETECT_MODE == 1 // 能量机关五点模型
#define KPT_NUM 5
#define CLS_NUM 4
#define MODEL_PATH  ""
#elif DETECT_MODE == 2 // 视觉识别版检测模型
#define KPT_NUM 0
#define CLS_NUM 4
#define MODEL_PATH ""
#endif//结束条件编译
class yolo_kpt {
public:
    yolo_kpt();

    struct Object {
        /*图像识别数据*/
        cv::Rect_<float> rect; 
        int label;
        float prob;//置信度
        std::vector<cv::Point2f>kpt;
        /*pnp数据*/
        int pnp_is_calculated = 0;  //-1无解，0未计算，1计算完成
        int kpt_lost_index = -1;    //角点缺失索引，0-左上，1-左下，2-右下，3-右上
        cv::Mat pnp_tvec;
        cv::Mat pnp_rvec;
    };
    //图像缩放+填充，保持长宽比
    cv::Mat letter_box(cv::Mat &src, int h, int w, std::vector<float> &padd);
    //将关键点坐标还原到原图尺寸
    std::vector<cv::Point2f>
    scale_box_kpt(std::vector<cv::Point2f> points, std::vector<float> &padd, float raw_w, float raw_h, int idx);
    //将检测框坐标还原到原图尺寸
    cv::Rect scale_box(cv::Rect box, std::vector<float> &padd, float raw_w, float raw_h);
    //在图像上绘制检测结果
    void drawPred(int classId, float conf, cv::Rect box, std::vector<cv::Point2f> point, cv::Mat &frame,
                  const std::vector<std::string> &classes);
    //解析模型输出，生成检测提案    
    static void generate_proposals(int stride, const float *feat, std::vector<Object> &objects);
    //主函数，处理输入图像，执行推理并返回检测结果
    std::vector<Object> work(cv::Mat src_img);

    /*----新增函数----*/
    std::string label2string(int num);// 标签ID转字符串（如0→"B1"）
    cv::Mat visual_label(cv::Mat inputImage, std::vector<yolo_kpt::Object> result);// 可视化结果
    void removePointsOutOfRect(std::vector<cv::Point2f>& kpt, const cv::Rect2f& rect);// 移除矩形外的点
    int findMissingCorner(const std::vector<cv::Point2f>& pts);// 查找缺失的角点
    int pnp_kpt_preprocess(std::vector<yolo_kpt::Object>& result);// PNP解算预处理

private:
    ov::Core core;// OpenVINO核心对象
    std::shared_ptr<ov::Model> model;// 模型指针
    ov::CompiledModel compiled_model;// 编译后的模型
    ov::InferRequest infer_request;// 推理请求
    ov::Tensor input_tensor1;// 输入张量
#if DETECT_MODE == 0
    const std::vector<std::string> class_names = {
            "B1", "B2", "B3", "B4", "B5", "BO", "BS", "R1", "R2", "R3", "R4", "R5", "RO", "RS"
    };
#elif DETECT_MODE == 1
    const std::vector<std::string> class_names = {
             "RR", "RW", "BR", "BW"
    };
#elif DETECT_MODE == 2
     const std::vector<std::string> class_names = {
            "RA", "RD", "BA", "BD"
    };
#endif

    static float sigmoid(float x) {
        return static_cast<float>(1.f / (1.f + exp(-x)));
    }

};

#endif //GMASTER_CV_2023_ARMORNEWYOLO_H