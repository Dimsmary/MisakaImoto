//
// Created by 79937 on 2020/7/30.
//

#ifndef DISPLAYIMAGE_VIDEO_PLAYER_HPP
#define DISPLAYIMAGE_VIDEO_PLAYER_HPP

#include <fb-pusher.hpp>
#include <opencv2/opencv.hpp>

#define VID_PATH "login.mp4"

class video_player {
public:
    void video_play(fb &fb_pusher);
};


#endif //DISPLAYIMAGE_VIDEO_PLAYER_HPP
