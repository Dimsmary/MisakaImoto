//
// Created by 79937 on 2020/7/31.
//

#ifndef DISPLAYIMAGE_VOLTAGE_DETECT_HPP
#define DISPLAYIMAGE_VOLTAGE_DETECT_HPP

#include <iostream>
class voltage_detect {
    void write_value(bool value);
    float voltage;
    int times;
    bool isRead;
    int storage[3];
    int counter;
    int storage_which;

    int SDA;
    int SCL;
public:
    voltage_detect(int sda, int scl);
    void bind_internal_function(void (*function)());
    void data_process();
    float get_voltage();
};


#endif //DISPLAYIMAGE_VOLTAGE_DETECT_HPP
