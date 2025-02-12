import os
import numpy as np

from ctypes import cdll
from ChessBoard import ChessBoard


def get_data(path="/", number=500):
    """生成数据集"""
    # 加载动态链接库 变量准备
    ass = cdll.LoadLibrary(
        r'C:/Users/王欣哲/Desktop/codes/人工智能基础/问题3 进化学习/1.构建预训练数据集/Assessment.dll')
    ass.init()
    chess = ChessBoard()
    res = []
    _path = path
    # 保存路径
    if not os.path.exists(_path):
        os.makedirs(_path)
    # 生成棋盘
    for p in range(number):
        chess.reset()  # 棋盘重制
        chessNum = np.random.binomial(225, 0.01, 1)[0]
        for q in range(chessNum):
            i = np.random.binomial(14, 0.5, 1)[0]
            j = np.random.binomial(14, 0.5, 1)[0]
            while chess.get_XY_state(i, j) != chess.EMPTY:
                i = np.random.binomial(14, 0.5, 1)[0]
                j = np.random.binomial(14, 0.5, 1)[0]
            chess.draw_XY(i, j)

        _label = ass.assessment(
            np.ctypeslib.as_ctypes(chess.board), chess.turn)  # 使用动态链接库打分
        _chess = np.array(chess.board).reshape(225)
        _res = np.append(_chess, _label)
        res.append(_res)
    np.savetxt(_path+'/'+'train_4.csv', res, fmt='%.1f', delimiter=',')


if __name__ == "__main__":
    # 生成数据集
    get_data(
        path="C:/Users/王欣哲/Desktop/codes/人工智能基础/问题3 进化学习/dataset", number=5000)
