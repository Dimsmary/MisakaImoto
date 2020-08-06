import lib.GPIO as GPIO


class status:
    def __init__(self):
        # 第一个变量为摄像头
        # 第二个为工作状态(普通、黑白、作战)
        # 第三个为放大状态
        # 第四个为人脸识别/颜色提取
        self.work_status = [0, 0, 0, 0]
        self.gpio = GPIO.GPIO()

    def get_camera(self):
        return self.work_status[0]

    def get_work(self):
        return self.work_status[1]

    def get_zoom(self):
        return self.work_status[2]

    def get_face(self):
        return self.work_status[3]

    def status_update(self):
        self.gpio.io_update()
        for i in range(4):
            sta = self.gpio.get_interrupt(i)
            # 中断处理
            # 处理模式切换
            if sta == 1:
                self.gpio.reset_interrupt(i)
                if i == 1:
                    if self.work_status[i] == 2:
                        self.work_status[i] = 0
                    else:
                        self.work_status[i] += 1
                # 处理人脸识别/颜色提取切换
                elif i == 3:
                    if self.work_status[i] == 2:
                        self.work_status[i] = 0
                    else:
                        self.work_status[i] += 1
                # 其他处理（放大、摄像头）
                else:
                    if self.work_status[i]:
                        self.work_status[i] = 0
                    else:
                        self.work_status[i] = 1
                print(self.work_status)


# sta = status()
# while True:
#     sta.status_update()

