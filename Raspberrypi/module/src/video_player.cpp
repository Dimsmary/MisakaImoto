//
// Created by 79937 on 2020/7/30.
//

#include "video_player.hpp"
using namespace std;

void video_player::video_play(fb &fb) {
    cv::VideoCapture cap(VID_PATH);
    cv::Mat frame;
    bool bSuccess = cap.read(frame);


    cout << "Video Player Begin" << endl;
    // 循环读取视频直至结束
    while(bSuccess){
        fb.push_frame(frame);
        cv::waitKey(30);
        bSuccess = cap.read(frame);
    }

}