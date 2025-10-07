#include "data_manager/base.h"
#include "data_manager/param.h"
#include "threads/pipeline.h"
#include "threads/control.h"
#include "garage/garage.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <unistd.h>

//海康相机驱动
#include "HIKdriver.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

//前端参数loader
#include "parameter_loader.hpp"

//cam calib
#include "cam_calibration.hpp"

//全局定义的互斥锁和条件变量
std::mutex hang_up_mutex;
std::condition_variable hang_up_cv;

int main(int argc, char** argv) {
    //获取各个核心模块的单例实例，确保全局唯一性
    auto param = Param::get_instance();
    auto pipeline = Pipeline::get_instance();
    auto garage = Garage::get_instance();
    auto control = Control::get_instance();

    int option;

    para_load("/etc/openrm/forward_config/config.yaml");

    // if(argc > 1) std::cout << "!!!!!!!!!!" << argv[1] << std::endl;
    while ((option = getopt(argc, argv, "hsv")) != -1) {
        switch (option) {
            case 's':
                Data::imshow_flag = true;//启用图像显示标志
                break;
            case 'h':
                std::cout << "Usage: " << argv[0] << " [-h] [-s] " << std::endl;
                break;//显示帮助信息
            case 'v':
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!imshow enable" << std::endl;
                params.is_imshow = 1;//启用图像显示功能
        }
    }
    

    /*相机读取线程*/
    std::thread cameraThread(HIKcamtask);
    cv::Mat inputImage;

    // calibration_main();


    //debug
    // while(1)
    // {
    //     //读取视频帧
    //     HIKframemtx.lock();
    //     HIKimage.copyTo(inputImage);
    //     HIKframemtx.unlock();
    //     if(inputImage.empty()) continue;

    //     cv::imshow("cam", inputImage);
    //     if(cv::waitKey(1)=='q') break;
    // }

    // while(true) if(init_camera()) break;

    rm::message_init("autoaim");//初始化消息系统，标识为"autoaim"
    init_debug();//初始化调试系统
    init_attack();//初始化攻击识别系统
    //DEBUG 暂时关闭serial
    // if (Data::serial_flag) init_serial();
    //DEBUG 暂时关闭control
    control->autoaim();

    //3v3没能量机关，直接baseline
    pipeline->autoaim_baseline();

    // #if defined(TJURM_INFANTRY) || defined(TJURM_BALANCE)
    // pipeline->autoaim_combine();
    // std::cout << "set INFANTRY" << std::endl;  
    // #endif

    // #if defined(TJURM_SENTRY) || defined(TJURM_DRONSE) || defined(TJURM_HERO)
    // pipeline->autoaim_baseline();
    // std::cout << "set SENTRY" << std::endl;  
    // #endif

    //手动模式下的射击控制 按回车键出发一次自动射击
    while(Data::manu_fire) {
        std::cin.get();
        Data::auto_fire = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Data::auto_fire = false;
    }

    //程序挂起等待，直到收到退出信号
    rm::message("Main thread hang up!", rm::MSG_OK);
    std::unique_lock<std::mutex> lock(hang_up_mutex);
    hang_up_cv.wait(lock);
    std::cout << "end" << std::endl;
    return 0;
}