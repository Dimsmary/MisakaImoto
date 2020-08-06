//
// Created by 79937 on 2020/7/27.
//

#include "fb-pusher.hpp"
#include <iostream>


fb::framebuffer_info fb::get_framebuffer_info(const char* framebuffer_device_path) {
    struct framebuffer_info info;
    struct fb_var_screeninfo screen_info;
    int fd = -1;
    fd = open(framebuffer_device_path, O_RDWR);
    if (fd >= 0) {
        if (!ioctl(fd, FBIOGET_VSCREENINFO, &screen_info)) {
            info.xres_virtual = screen_info.xres_virtual;
            info.bits_per_pixel = screen_info.bits_per_pixel;
        }
    }
    return info;
};

void fb::push_frame(cv::Mat &frame) {
//    framebuffer_info fb_info = get_framebuffer_info(FB_DIR);
    std::ofstream ofs(FB_DIR);
        if (frame.depth() != CV_8U) {
            std::cerr << "FB pusher: Not 8 bits per pixel and channel." << std::endl;
        } else if (frame.channels() != 3) {
            std::cerr << "FB pusher: Not 3 channels." << std::endl;
        } else {
            // 3 Channels (assumed BGR), 8 Bit per Pixel and Channel
            int framebuffer_width = fb_info.xres_virtual;
            int framebuffer_depth = fb_info.bits_per_pixel;
            cv::Size2f frame_size = frame.size();
            cv::Mat framebuffer_compat;
            switch (framebuffer_depth) {
                case 16:
                    cv::cvtColor(frame, framebuffer_compat, cv::COLOR_BGR2BGR565);
                    for (int y = 0; y < frame_size.height ; y++) {
                        ofs.seekp(y*framebuffer_width*2);
                        ofs.write(reinterpret_cast<char*>(framebuffer_compat.ptr(y)),frame_size.width*2);
                    }
                    break;
                case 32: {
                    std::vector<cv::Mat> split_bgr;
                    cv::split(frame, split_bgr);
                    split_bgr.push_back(cv::Mat(frame_size,CV_8UC1,cv::Scalar(255)));
                    cv::merge(split_bgr, framebuffer_compat);
                    for (int y = 0; y < frame_size.height ; y++) {
                        ofs.seekp(y*framebuffer_width*4);
                        ofs.write(reinterpret_cast<char*>(framebuffer_compat.ptr(y)),frame_size.width*4);
                    }
                } break;
                default:
                    std::cerr << "FB pusher: Unsupported depth of framebuffer." << std::endl;
                    std::cout << framebuffer_depth << std::endl;
            }
    }
        ofs.close();
}
