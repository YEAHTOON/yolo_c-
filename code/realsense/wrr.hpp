#ifndef __WRR_H_
#define __WRR_H_

#include <librealsense2/rs.hpp>

/**
 * 帧集
*/
class wrr_frameset
{
public:
    wrr_frameset():align2color(RS2_STREAM_COLOR)
    {
        //数据流配置
        rs2::config c;
        c.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
        c.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
        c.disable_stream(RS2_STREAM_ACCEL);
        c.disable_stream(RS2_STREAM_GYRO); 

        //开启数据流
        this->pipeline.start(c);  
    }

    //更新图像
    void update(void)
    {
        this->frameset = this->pipeline.wait_for_frames();
        this->alignedFrameset =  this->align2color.process(this->frameset);
    }

    //获得彩色图像数据
    const void *get_colordata(void)
    {
        return this->alignedFrameset.get_color_frame().get_data();
    }

private:
    rs2::pipeline   pipeline;           //数据管道
    rs2::align      align2color;        //对齐器
    rs2::frameset   frameset;           //帧集
    rs2::frameset   alignedFrameset;    //对齐后的帧集
};


#endif
