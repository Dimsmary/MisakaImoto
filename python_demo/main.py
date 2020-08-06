import cv2
import time
from lib.system_status import status
from lib.font_display import stack

# 创建状态对象
status = status()

# 创建层叠对象
stacker = stack()

# 开启摄像头
camera1 = cv2.VideoCapture(0)
camera2 = cv2.VideoCapture(2)

# 加载人脸识别预设
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# # 开机动画
# cap = cv2.VideoCapture('login.mp4')
# while True:
#     success, img = cap.read()
#     if not success:
#         break
#     cv2.imshow('WindowsName', img)
#     cv2.waitKey(30)
#
# # 过渡动画
# stacker.display(240, 0, 'graph')

while True:
    status.status_update()
    # 选择摄像头
    if status.get_camera():
        success, img = camera1.read()
    else:
        success, img = camera2.read()

    if success:
        # 图像放大
        if status.get_zoom():
            img = img[120:361, 160:481]
        else:
            img = cv2.resize(img, (320, 240))

        # 切换工作模式
        if status.get_work():
            if status.get_work() == 1:
                img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            else:
                img = cv2.Canny(img, 100, 100)

        # 人脸识别/颜色提取
        if status.get_face() and status.get_work() != 2:
            if status.get_face() == 1:
                # 判断是否提前进行了灰度转换
                if status.get_work() != 1:
                    Gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                else:
                    Gray = img
                # 探测人脸
                faces = face_cascade.detectMultiScale(Gray, 1.1, 4)
                # 绘制方框
                for (x, y, w, h) in faces:
                    cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
            else:
                pass

        # 堆叠文字等内容
        img = stacker.stack_font(img)

        # 堆叠图形
        img = stacker.stack_graph(img)

        # 显示
        cv2.imshow('WindowsName', img)
        cv2.waitKey(1)

