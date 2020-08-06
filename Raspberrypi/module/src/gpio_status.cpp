//
// Created by 79937 on 2020/7/28.
//

#include <wiringPi.h>
#include "gpio_status.hpp"
#include <iostream>



using namespace std;


void gpio_status::print() {
    cout << "wdnmd" << endl;
}


// 对象构造函数
gpio_status::gpio_status(int gpio0, int gpio1, int gpio2, int gpio3, int led, int signal) {

    wiringPiSetup();

    // GPIO编号赋值到数组
    gpio_list[0] = gpio0;
    gpio_list[1] = gpio1;
    gpio_list[2] = gpio2;
    gpio_list[3] = gpio3;
    LED = led;
    SIGNAL = signal;
    if_rec = false;


    // 初始化GPIO
    for(int i = 0; i < 3 ; i++ ){
        pinMode(gpio_list[i], INPUT);
    }

    // 初始化其他端口
    pinMode(LED, OUTPUT);
    pinMode(SIGNAL, OUTPUT);
}

// 绑定中断函数
void gpio_status::bind_internal_function(
        void (*function0)(),
        void (*function1)(),
        void (*function2)(),
        void (*function3)()
        ) {
    // 绑定中断函数，设置下降沿触发
    wiringPiISR (gpio_list[0], INT_EDGE_FALLING, function0) ;
    wiringPiISR (gpio_list[1], INT_EDGE_FALLING, function1) ;
    wiringPiISR (gpio_list[2], INT_EDGE_FALLING, function2) ;
    wiringPiISR (gpio_list[3], INT_EDGE_FALLING, function3) ;

}

void gpio_status::toggle(int port) {
    if(status_list[port]) {
        status_list[port] = 0;
    }else{
        status_list[port] = 1;
    }
}

// 中断处理函数
void gpio_status::gpioInterrupt(int port) {

    cout << "TouchPad: Detected port:" << port << endl;

    // 如果处于菜单A
    if(status_list[3] == 0){
        // 切换工作模式
        if(port == 2){
            if(status_list[port] == work_mode) {
                status_list[port] = 0;
            }
            else{
                status_list[port] ++;
            }
        }

        // 切换放大倍数、摄像头
        else{
            toggle(port);
        }
    }

    // 如果处于菜单B
    else{
        switch(port){
            // 翻转LED
            case 0:
                LED_toggle();
                break;
            // 关机
            case 1:
                system("shutdown -P now");
                break;
            // 录像
            case 2:
                if_rec = !if_rec;
                break;
            // 翻转菜单
            case 3:
                toggle(port);
                break;
        }

    }
}

// 返回状态列表值
int gpio_status::get_camera() {
    return status_list[0];
}

// 返回放大状态
int gpio_status::get_zoom() {
    return status_list[1];
}

// 返回工作模式
int gpio_status::get_status() {
    return status_list[2];
}

// 返回菜单
int gpio_status::get_menu() {
    return status_list[3];
}


// 激活signal
void gpio_status::SIGNAL_UP() {
    digitalWrite(SIGNAL, LOW);
}

// 释放signal
void gpio_status::SIGNAL_DOWN() {
    digitalWrite(SIGNAL, HIGH);
}

// 翻转LED
void gpio_status::LED_toggle() {
    if(digitalRead(LED)){
        digitalWrite(LED, LOW);
    }
    else{
        digitalWrite(LED, HIGH);
    }
}

int gpio_status::return_led() {
    return digitalRead(LED);
}

bool gpio_status::get_rec(){
    return if_rec;
}