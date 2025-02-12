# 五子棋类
#
# 完成了五子棋的各项基本操作，包括落子、判胜、
# 棋盘状态更新、获取等功能
#
# 王欣哲 2020/12/5

import numpy as np


class ChessBoard(object):
    BLACK = 0
    WHITE = 1
    EMPTY = 2

    DIR = [[1, 0], [0, 1], [1, 1], [1, -1]]

    def __init__(self):
        self.num = 0
        self.turn = self.BLACK
        self.winner = self.EMPTY
        self.premove = [-1, -1]
        self.board = np.zeros([15, 15])
        self.board[:, :] = self.EMPTY
        self.dir = [[(-1, 0), (1, 0)], [(0, -1), (0, 1)],
                    [(-1, 1), (1, -1)], [(-1, -1), (1, 1)]]

    def judge_Legal(self, x, y):
        return (x >= 0 and x < 15) and (y >= 0 and y < 15)

    def board(self):
        return self.board

    def draw_XY(self, x, y):
        if (not self.judge_Legal(x, y)):
            return False
        self.board[x][y] = self.turn
        self.num += 1
        self.turn = self.turn ^ 1  # 更换落子方
        self.premove = (x, y)
        return True

    def get_XY_state(self, x, y):
        """获取(x,y)的状态"""
        return self.board[x][y]

    def get_XY_on_dir(self, x, y, dir):
        x += dir[0]
        y += dir[1]

        if not self.judge_Legal(x, y):
            return False
        else:
            return x, y

    def judge_Win(self):
        x = 0
        y = 0
        cnt = 0
        color = self.EMPTY
        # 遍历四个方向
        for d in range(4):
            color = self.EMPTY
            cnt = 0
            # 遍历9颗连续棋子
            for k in range(-4, 5):
                x = self.premove[0] + self.DIR[d][0] * k
                y = self.premove[1] + self.DIR[d][1] * k
                if self.judge_Legal(x, y):
                    if self.board[x][y] == self.EMPTY:
                        color = self.EMPTY
                        cnt = 0
                    else:
                        if self.board[x][y] == color:
                            cnt += 1
                        else:
                            color = self.board[x][y]
                            cnt = 1
                else:
                    if k > 0:
                        break
                if cnt == 5:
                    self.winner = color
                    return color
        return self.EMPTY

    def reset(self):
        self.num = 0
        self.turn = self.BLACK
        self.winner = self.EMPTY
        self.board[:, :] = self.EMPTY
