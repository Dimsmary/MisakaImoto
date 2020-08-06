//
// Created by 79937 on 2020/7/31.
//

#ifndef DISPLAYIMAGE_FRAME_STACKER_HPP
#define DISPLAYIMAGE_FRAME_STACKER_HPP

#include <opencv2/opencv.hpp>

using namespace std;


class frame_stacker {
    string text;
    int times;

    // 文字属性

    bool back_ground;
    int font_face;
    double font_scale;
    int thickness;
    cv::Point origin;
    int b;
    int g;
    int r;
public:
    frame_stacker():
        times(0),
        back_ground(false),
        text(""),
        font_face(cv::FONT_HERSHEY_COMPLEX),
        font_scale(0.8),
        thickness(1),
        b(0),
        g(255),
        r(255)
        {origin.x = 0; origin.y = 235;};
    void stack(cv::Mat &frame);
    void fill_times(int Times);
    void fill_text(string Text);
    void set_origin(int Y);
    void set_color(int B, int G, int R);
    void set_fontscale(double scale);
};


#endif //DISPLAYIMAGE_FRAME_STACKER_HPP
