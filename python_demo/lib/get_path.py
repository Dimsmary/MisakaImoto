import sys
import os

# 获取文件所在目录
application_path = ''
if getattr(sys, 'frozen', False):
    application_path = os.path.dirname(sys.executable)
elif __file__:
    application_path = os.path.dirname(__file__)
base_dir_back = os.path.abspath(os.path.join(application_path, os.path.pardir))
base_dir = application_path


# 获取文件目录
def get_file_path():
    return base_dir


# 获取文件上一级目录
def get_file_back_path():
    return base_dir_back


# with open(os.path.join(base_dir, 'GPIO_0.txt'), 'w') as f:
#     f.write('0')
#
# with open(os.path.join(base_dir, 'GPIO_0.txt'), 'r') as f:
#     if f.read() == '0':
#         print('0')
