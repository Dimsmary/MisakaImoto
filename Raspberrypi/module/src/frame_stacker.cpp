//
// Created by 79937 on 2020/7/31.
//

#include "frame_stacker.hpp"

// 堆叠显示文字
void frame_stacker::stack(cv::Mat& frame) {

    if(times > 1) {
        cv::Scalar font_color(b, g, r);
        times--;
        cv::putText(frame, text, origin, font_face, font_scale, font_color, thickness, 8, 0);
    }
}


// 填充剩余时间
void frame_stacker::fill_times(int Times) {
    times = Times;
}

// 更改字体
void frame_stacker::fill_text(string Text) {
    text  = Text;
}

// 设置位置
void frame_stacker::set_origin(int Y) {
    origin.y = Y;
}

// 更换字体颜色
void frame_stacker::set_color(int B, int G, int R) {
    b = B;
    g = G;
    r = R;
}

// 改变字体大小
void frame_stacker::set_fontscale(double scale) {
    font_scale = scale;
}