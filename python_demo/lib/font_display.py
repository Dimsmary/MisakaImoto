import cv2


class stack:
    def __init__(self):
        self.times = 0
        self.preset = 0
        self.mode = 0
        self.act_font = 0
        self.act_graph = 0

    def clean_sta(self):
        if self.times <= 0:
            self.act_font = 0
            self.times = 0

    # 更改显示参数
    def display(self, times, preset, mode):
        self.times = times
        self.preset = preset
        if mode == 'font':
            self.act_font = 1
        elif mode == 'graph':
            self.act_graph = 1

    # 显示字体
    def stack_font(self, img):
        # 如果没有未完成的任务
        if self.times == 0 or self.act_font == 0:
            return img
        else:
            self.times -= 1
            # 清除活跃标志
            self.clean_sta()
            return cv2.putText(img, 'TEXT', (50, 50), cv2.FONT_ITALIC, 1, (255, 255, 0), 1)

    def stack_graph(self, img):
        # 如果没有未完成的任务
        if self.times == 0 or self.act_graph == 0:
            return img
        else:
            self.times -= 30
            # 清除活跃标志
            self.clean_sta()
            return cv2.rectangle(img, (0, 0), (320, self.times), (255, 255, 255), cv2.FILLED)

