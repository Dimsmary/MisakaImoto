
// C++标准库
#include <iostream>

// 其他库
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/lambda/bind.hpp>

// 个人编写的库
#include <fb-pusher.hpp>
#include <gpio_status.hpp>
#include <video_player.hpp>
#include <frame_stacker.hpp>
#include <voltage_detect.hpp>

// opencv 基本库
#include <opencv2/opencv.hpp>

// opencv 人脸识别需要的库
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// 树莓派基于WiringPi库的引脚定义
#define KEY0 23
#define KEY1 24
#define KEY2 25
#define KEY3 29
#define LED 28
#define SIGNAL 22

#define SDA 8
#define SCL 9

// namespace
using namespace cv;
using namespace std;
using namespace boost::filesystem;
using namespace boost::lambda;

// 创建GPIO扫描对象
gpio_status gpio(KEY0, KEY1, KEY2, KEY3, LED, SIGNAL);

// 创建ADC数据传输处理对象
voltage_detect adc(SDA, SCL);

// 加载人脸识别模型
CascadeClassifier face_cascade;

// 创建文本叠对象
frame_stacker stacker1;
frame_stacker stacker2;


// 创建中断处理函数
void gpioInterrupt0(){
    gpio.gpioInterrupt(0);

    // 显示提示文本
    if(gpio.get_menu()){
        // 菜单B下的开关指示灯
        if(gpio.return_led()){
            stacker1.fill_text("Light ON");
        }
        else{
            stacker1.fill_text("LIGHT OFF");
        }
    }else{
        // 菜单A下的切换摄像头
        if(gpio.get_camera()){
            stacker1.fill_text("Camera IR");
        }else{
            stacker1.fill_text("Camera NORM");
        }
    }
    stacker1.fill_times(50);
}

void gpioInterrupt1(){
    gpio.gpioInterrupt(1);
    if(gpio.get_menu()){
    }else{
        if(gpio.get_zoom()){
            stacker1.fill_text("Zoom 2X");
        }else{
            stacker1.fill_text("Zoom 1X");
        }
    }
    stacker1.fill_times(50);
}

void gpioInterrupt2(){
    gpio.gpioInterrupt(2);
    if(gpio.get_menu()){
        if(gpio.get_rec()){
            stacker1.fill_text("REC Begin");
        }else{
            stacker1.fill_text("REC End");
        }

    }else{
        switch(gpio.get_status()){
            case 0:
                stacker1.fill_text("Normal Mode");
                break;
            case 1:
                stacker1.fill_text("Gray Scale");
                break;
            case 2:
                stacker1.fill_text("Canny");
                break;
            case 3:
                stacker1.fill_text("Face Detect");
                break;
        }
    }
    stacker1.fill_times(50);
}

void gpioInterrupt3(){
    gpio.gpioInterrupt(3);
    if(gpio.get_menu()){
        stacker1.fill_text("Menu B");
        stacker1.fill_times(50);
    }else{
        stacker1.fill_text("Menu A");
        stacker1.fill_times(50);
    }

}

void gpioInterrupt_adc(){
    adc.data_process();
    // 获取电压
    string vol = to_string(adc.get_voltage());

    // 字符串处理
    vol = vol.substr(0, 4);
    vol = vol + "V";

    // 显示电压
    stacker2.fill_text(vol);
    stacker2.fill_times(1000);
}


// ==================主函数================ //
int main(){

    // 初始化文字堆叠对象

    stacker1.fill_text("Dimsmary");
    stacker1.fill_times(100);
    stacker1.set_fontscale(0.5);


    stacker2.set_origin(15);
    stacker2.set_color(0xff, 0xff, 0xff);
    stacker2.set_fontscale(0.5);

    // 创建framebuffer显示对象
    fb fb;

    // 绑定中断函数
    gpio.bind_internal_function(
            gpioInterrupt0,
            gpioInterrupt1,
            gpioInterrupt2,
            gpioInterrupt3);

    adc.bind_internal_function(gpioInterrupt_adc);

    // 创建摄像头对象
    VideoCapture cap0(0);
    VideoCapture cap1(2);
    // 创建图像容器
    Mat frame;
    Mat display;

    // 创建opencv功能对象
    Size dsize = Size(320, 240);    // 用于缩放图片
    Rect dcut(120, 160, 320, 240);  // 用于裁切图片

    // 绑定人脸识别模型
    face_cascade.load("haarcascade_frontalface_default.xml");

    // 示意单片机启动成功
    gpio.SIGNAL_UP();

    // 打印启动信息
    cout << "Main Process: Program Initialize Success." << endl;

    //开头动画
    {
        video_player vp;
        vp.video_play(fb);
    }


    while(true){

        // 切换摄像头
        if(gpio.get_camera()){
            cap1.read(frame);

        }else{
            cap0.read(frame);
        }

        // 切换放大状态
        if(gpio.get_zoom()){
            // 将原始图片进行裁切
            frame = frame(dcut);
        }else{
            // 将原始图像进行缩放
            resize(frame, frame, dsize);
        }

        // 切换工作模式
        int now_status = gpio.get_status();


        //==========此前图像的名称为frame==============//
        //==========模式切换==============//
        // 正常模式
        if(now_status == 0){
            display = frame;
        }

        // 灰度显示模式
        else if(now_status == 1){
            cvtColor(frame, frame, CV_BGR2GRAY);
            cvtColor(frame, display, CV_GRAY2BGR);
        }

        // 边缘检测模式
        else if(now_status == 2){
            Canny(frame, display, 100, 100);
            cvtColor(display, display, CV_GRAY2BGR);
        }
        else if(now_status == 3){
            std::vector<Rect> faces;
            face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
            for( int i = 0; i < faces.size(); i++ )
            {
                Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
                ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
            }
            display = frame;
        }



        //==========堆叠文字==============//
        stacker1.stack(display);
        stacker2.stack(display);

        // 录像
        if(gpio.get_rec()){

            // 存储路径
            path the_path( "rec" );

            // 获取文件个数
            int cnt = std::count_if(
                    directory_iterator(the_path),
                    directory_iterator(),
                    static_cast<bool(*)(const path&)>(is_regular_file) );

            // 生成文件名
            string cnt_str = to_string(cnt);
            string save_name = "rec/" + cnt_str + ".jpg";

            // 保存图片
            imwrite(save_name, display);

            cout << "Image Saved :" << save_name << endl;
        }


        // 推送至Framebufer
        fb.push_frame(display);
    }

    return 0;
}