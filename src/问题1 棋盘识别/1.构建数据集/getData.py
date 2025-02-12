# 构建数据集
#
# 从棋盘图片、棋子图片生成棋盘数据集

# 数据格式；
# 	图片为.jpg文件，按序号编号从0号开始
#   标签为.csv文件，每一行为图像中落子的标签
# 生成函数：
# 	get_Discrete_chess()函数生成随机的棋盘
# 	get_Continue_chess()函数生成随机落子、连续的棋盘
#
# 王欣哲 2020/12/5

import os
import numpy as np
import random
from PIL import Image

from ChessBoard import ChessBoard

WIDTH = 540
HEIGHT = 540
MARGIN = 22
GRID = (WIDTH - 2 * MARGIN) / (15 - 1)
PIECE = 34
BLACK = 0
EMPTY = 1
WHITE = 2

PICTURE_SIZE = 96

black = Image.open(
    "./img/black.png")
white = Image.open(
    "./img/white.png")
background = Image.open(
    "./img/chess.png")

# 将棋盘预先转化为灰度图
background = background.convert('L')

# 棋盘
chessboard = ChessBoard()


def get_Discrete_chess(path="/", new_chess_number=500):
    """生成数据集"""
    res = []	 # 记录的数组
    _path = path + "/"  # 存储路径
    if not os.path.exists(_path):
        os.makedirs(_path)
    # 生成棋盘
    for p in range(new_chess_number):
        # 棋盘初始化
        back = background.copy()    # 拷贝棋盘副
        chessboard.reset()  # 初始化棋盘

        chessNum = random.randint(0, 225)
        # 产生一个棋盘
        for q in range(chessNum):
            # 生成随机坐标
            i = random.randint(0, 14)
            j = random.randint(0, 14)
            while chessboard.get_XY_state(i, j) != chessboard.EMPTY:
                i = random.randint(0, 14)
                j = random.randint(0, 14)

            # 获取像素坐标
            x, y = MARGIN + j * GRID - PIECE / 2, MARGIN + i * GRID - PIECE / 2
            # 绘制图像
            if chessboard.turn == BLACK:
                back.paste(black, (int(x), int(y)), black)
            else:
                back.paste(white, (int(x), int(y)), white)
            # 更新棋盘
            chessboard.draw_XY(i, j)
        # 生成数据
        label = np.array(chessboard.board).reshape(225)
        img = back.resize((PICTURE_SIZE, PICTURE_SIZE), Image.ANTIALIAS)

        # 保存数据
        img.save(_path + '/' + str(p) + '.jpg')
        res.append(label)
    np.savetxt(_path+'/'+'label.csv', res, fmt='%.1f', delimiter=',')


if __name__ == "__main__":
    # 生成训练集
    get_Discrete_chess(path='./chess_database/train',
                       new_chess_number=10)

    # 生成测试集合
    get_Discrete_chess(path='./chess_database/test',
                       new_chess_number=5)
