//
// Created by 79937 on 2020/7/28.
//

#ifndef DISPLAYIMAGE_GPIO_STATUS_HPP
#define DISPLAYIMAGE_GPIO_STATUS_HPP

// 定义工作模式的个数
#define work_mode 3

class gpio_status {
    // status list属性：摄像头/
    int status_list[4] = {0, 0, 0, 0};
    int gpio_list[6] = {0, 0, 0, 0};
    int LED;
    int SIGNAL;
    bool if_rec;
    void toggle(int port);
public:
    gpio_status(int gpio0, int gpio1, int gpio2, int gpio3, int led, int signal);
    void print();
    void bind_internal_function(
            void (*function0)(),
            void (*function1)(),
            void (*function2)(),
            void (*function3)()
            );
    void gpioInterrupt(int port);
    int get_camera();
    int get_zoom();
    int get_status();
    int get_menu();
    void SIGNAL_UP();
    void SIGNAL_DOWN();
    void LED_toggle();
    int return_led();
    bool get_rec();
};


#endif //DISPLAYIMAGE_GPIO_STATUS_HPP
