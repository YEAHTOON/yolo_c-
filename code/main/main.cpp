#include "main.hpp"

#define USE_REALSENSE


/**
 * realsense更新图片的线程
*/
#ifdef USE_REALSENSE
void *realsense_updateIMG(void *args)
{
    wrr_frameset f;         //创建帧
    while(1)
    {
        f.update();         //更新帧
        pthread_mutex_lock(&PRO_VAR.updateFrame_mutex);         //上锁
        memcpy(args, (void *)f.get_colordata(), sizeof(u_char) * INPUTIMG_ROWS * INPUTIMG_COLS * 3);        //传出帧
        pthread_mutex_unlock(&PRO_VAR.updateFrame_mutex);       //解锁
        // usleep(10000);
    }
}
#endif




/**
 * 滥觞
*/
int main(void)
{

//线程相关
    //初始化互斥锁、信号量
    pthread_mutex_init(&PRO_VAR.updateFrame_mutex, nullptr);

    //线程创建
    pthread_t pid[10];
    #ifdef USE_REALSENSE
    pthread_create(pid, NULL, realsense_updateIMG, (void *)PRO_VAR.source_pic);
    #endif


//python相关
    //配置python环境
    Py_Initialize();        //启动python解释器
    _import_array();        //初始化numpy
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("os.chdir(\'/home/yezhiteng/PROJECTS/PRODUCTS/RECOGNIZETION_SYSTEM/code/yolov5\')");       //设置python解释器地址
    PyRun_SimpleString("sys.path.append(\'.\')");
    PyRun_SimpleString("sys.path.append(\'/home/yezhiteng/anaconda3/envs/ROS2/lib/python3.10/site-packages\')");
    PyRun_SimpleString("import torch");
    PyRun_SimpleString("import mypacks");
    PyRun_SimpleString("import numpy");
    PyRun_SimpleString("import cv2");
    PyObject *detect_module     = PyImport_ImportModule("detect");                      //获得模块
    PyObject *detect_fun_dict   = PyModule_GetDict(detect_module);                      //获得函数字典集
    PyObject *load_model        = PyDict_GetItemString(detect_fun_dict, "load_model");  //获得函数句柄
    PyObject *model             = PyObject_CallObject(load_model, NULL);                //调用函数，获得模型
//初始化结束


    //主线程
    while(1)
    {
        //获得更新后的图像
        pthread_mutex_lock(&PRO_VAR.updateFrame_mutex);         //上锁
        npy_intp Dims[3]    = {480, 640, 3};
        PyObject* picture   = (PyObject*)PyArray_SimpleNewFromData(3, Dims, NPY_UINT8, (void *)PRO_VAR.source_pic);    //获得python中的numpy数组
        pthread_mutex_unlock(&PRO_VAR.updateFrame_mutex);       //解锁

        //推理
        PyObject *detect_fun    = PyDict_GetItemString(detect_fun_dict, "detect_pic");  //检测函数
        PyObject *detect_args   = PyTuple_Pack(2, model, picture);                      //传入的参数
        PyObject *result        = PyObject_CallObject(detect_fun, detect_args);         //调用检测

        if(result != nullptr)
        {
            PyObject* item = PyTuple_GetItem(result, 0);  
            int a = PyLong_AsLong(item);
            std::cout << a+1 << std::endl;
        }
    }

    Py_Finalize();

    return 0;
}