//
// Created by 79937 on 2020/7/27.
//

#include <iostream> // for std::cerr
#include <opencv2/imgproc/imgproc.hpp>  // for cv::cvtColor
#include <opencv2/highgui/highgui.hpp> // for cv::VideoCapture
#include <fstream> // for std::ofstream
#include <boost/timer/timer.hpp> // for boost::timer::cpu_timer
#include <string>

// C的INCLUDE
#include <stdint.h> // for uint32_t
#include <sys/ioctl.h> // for ioctl
#include <linux/fb.h> // for fb_
#include <fcntl.h> // for O_RDWR

#ifndef DISPLAYIMAGE_FB_PUSHER_HPP
#define DISPLAYIMAGE_FB_PUSHER_HPP

// C的INCLUDE结束

#define FB_DIR "/dev/fb1"

using namespace std;

class fb {
    struct framebuffer_info {
        uint32_t bits_per_pixel; uint32_t xres_virtual;
    };
    framebuffer_info fb_info;

    framebuffer_info get_framebuffer_info(const char* framebuffer_device_path);
public:
    void push_frame(cv::Mat &frame);
    fb():fb_info(get_framebuffer_info(FB_DIR)){};
};

#endif //DISPLAYIMAGE_FB_PUSHER_HPP
