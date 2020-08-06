import os
import lib.get_path as get_path


class GPIO:
    def __init__(self):
        self.interrupt = [0, 0, 0, 0]
        base_path = get_path.base_dir_back
        # 添加IO文件目录
        self.io_path = []
        for i in range(4):
            filename = 'GPIO_' + str(i) + '.txt'
            self.io_path.append(os.path.join(base_path, filename))

    def io_update(self):
        # 打开文件判断IO状态
        for i in range(4):
            with open(self.io_path[i]) as f:
                if f.read() == '1':
                    self.interrupt[i] = 1
                    print('GPIO: IO ' + str(i) +' has been turned.')
            if self.interrupt[i] == 1:
                with open(self.io_path[i], 'w') as f:
                    f.write('0')

    # 读取中断接口
    def get_interrupt(self, i):
        return self.interrupt[i]

    # 中断置位接口
    def reset_interrupt(self, i):
        self.interrupt[i] = 0




