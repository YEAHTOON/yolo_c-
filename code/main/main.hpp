#ifndef __MAIN_
#define __MAIN_

#include "../realsense/wrr.hpp"

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <opencv4/opencv2/opencv.hpp>

#include <python3.10/Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <python3.10/numpy/arrayobject.h>


//输入图像的尺寸规定
#define INPUTIMG_COLS 640
#define INPUTIMG_ROWS 480

/**
 * 进程内的全局变量
*/
struct 
{
    u_char source_pic[INPUTIMG_COLS * INPUTIMG_ROWS * 3];   //图像暂存区
    pthread_mutex_t updateFrame_mutex;              //从存储图像的内存空间读取数据或写入数据要上锁
} PRO_VAR;

#endif