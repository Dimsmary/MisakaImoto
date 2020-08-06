//
// Created by 79937 on 2020/7/31.
//

#include <wiringPi.h>
#include "voltage_detect.hpp"

using namespace std;

voltage_detect::voltage_detect(int sda, int scl) {
    // 赋值GPIO序号
    SDA = sda;
    SCL = scl;

    // 初始化数据
    voltage = 0;
    isRead = false;
    times = 0;
    for(int i = 0; i < 3 ; i++){
        storage[i] = 0;
    }
    counter = 0;
    storage_which = 0;

    // 配置为输入
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);
}

// 绑定中断处理函数
void voltage_detect::bind_internal_function(void (*function)()) {
    wiringPiISR (SCL, INT_EDGE_FALLING, function) ;
}

void voltage_detect::write_value(bool value) {
    // 计算是否算满4位
    if(counter != 4){
        counter ++;
    }else{
        // 计次归位1
        counter = 1;
        storage_which ++;
    }

    // 读取数据
    if(value){
        storage[storage_which] = (storage[storage_which] << 1) | 1;
    }else{
        storage[storage_which] = (storage[storage_which] << 1) | 0;
    }

    // 如果已经读取完成
    if(storage_which == 2 and counter == 4){
        cout << storage[0] << storage[1] << storage[2] << endl;
        voltage = storage[0] + storage[1] / 10.0 + storage[2] / 100.0;
        cout << "Voltage Read: " << voltage << endl;
        isRead = false;
        times = 0;
        for(int i = 0; i < 3 ; i++){
            storage[i] = 0;
        }
        counter = 0;
        storage_which = 0;
    }
}

// 数据处理函数
void voltage_detect::data_process(){
    if(isRead){
        // 读取到为高电平
        write_value(digitalRead(SDA));
    }
    // 如果没有读取到完整的头
    else{
        if(digitalRead(SDA)){
            times = 0;
        }else{
            times++;

        }

        // 如果连续读取到12个低电平
        if(times == 12){
            isRead = true;
        }
    }
}

float voltage_detect::get_voltage() {
    return voltage;
}
