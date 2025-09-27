#ifndef HIK_CPP
#define HIK_CPP

#include <iostream>
#include <X11/Xlib.h> //X window系统库
#include <assert.h>  //断言检查
#include "math.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include "MvCameraControl.h" //海康相机控制库

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pthread.h>    //POSIX线程库

extern cv::Mat HIKimage;
extern std::mutex HIKframemtx;

int HIKcamtask();

#endif