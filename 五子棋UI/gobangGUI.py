import sys
import time
import random

from PIL import ImageGrab
from PyQt5.QtMultimedia import QSound
from PyQt5.QtGui import QPixmap, QIcon, QPalette, QPainter
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QMessageBox
from PyQt5 import QtCore, QtGui

# from ai import searcher
from ChessBoard import ChessBoard

WIDTH = 540
HEIGHT = 540
MARGIN = 22
GRID = (WIDTH - 2 * MARGIN) / (15 - 1)
PIECE = 34

BLACK = 0
WHITE = 1
EMPTY = 2

# 重写标签类


class Label(QLabel):
    def __init__(self, parent):
        super().__init__(parent)
        self.setMouseTracking(True)

    def enter_Event(self, e):
        e.ignore()


class GoBang(QWidget):
    def __init__(self):
        super().__init__()

        # 棋局参数
        self.piece_Now = BLACK
        self.step = 0
        self.x, self.y = 100, 100

        # 窗口初始化
        self.initUI()

    def initUI(self):
        # 棋盘类
        self.chessboard = ChessBoard()

        # 窗口大小
        self.resize(WIDTH, HEIGHT)
        self.setMinimumSize(QtCore.QSize(WIDTH, HEIGHT))
        self.setMaximumSize(QtCore.QSize(WIDTH, HEIGHT))
        # 窗口位置
        self.move(100, 62)

        # 窗口名称
        self.setWindowTitle("五子棋")
        # 窗口图标
        self.setWindowIcon(
            QIcon("C: \\Users\\王欣哲\\Desktop\\codes\\人工智能基础\\五子棋UI\\img\\black.png"))

        # 加载棋子图片
        self.black = QPixmap(
            "C:\\Users\\王欣哲\\Desktop\\codes\\人工智能基础\\五子棋UI\\img\\black.png")
        self.white = QPixmap(
            "C:\\Users\\王欣哲\\Desktop\\codes\\人工智能基础\\五子棋UI\\img\\white.png")

        # 棋盘背景
        palette = QPalette()
        palette.setBrush(self.backgroundRole(), QtGui.QBrush(
            QtGui.QPixmap("C:\\Users\\王欣哲\\Desktop\\codes\\人工智能基础\\五子棋UI\\img\\chess.png")))
        self.setPalette(palette)

        # 鼠标指针样式为 手
        self.setCursor(Qt.PointingHandCursor)

        # 鼠标焦点图片
        # self.mouse_Point = Label(self)
        # self.mouse_Point.setScaledContents(True)
        # self.mouse_Point.setPixmap(self.black)  # 加载黑棋
        # self.mouse_Point.setGeometry(270, 270, PIECE, PIECE)
        # self.mouse_Point.raise_()  # 鼠标始终在最上层

        self.pieces = [Label(self) for i in range(225)]  # 新建棋子标签，准备在棋盘上绘制棋子
        for piece in self.pieces:
            piece.setVisible(True)  # 图片可视
            piece.setScaledContents(True)  # 图片大小根据标签大小可变

        self.setMouseTracking(True)

        # 显示窗口
        self.show()

    # def mouseMoveEvent(self, e):  # 黑色棋子随鼠标移动
    #     """鼠标移动事件"""
    #     self.mouse_Point.move(e.x() - 16, e.y() - 16)

    def mousePressEvent(self, e):
        """鼠标按键响应函数"""
        if e.button() == Qt.LeftButton:
            x, y = e.x(), e.y()  # 鼠标坐标
            i, j = self.coordinate_transform_pixel2map(x, y)  # 对应棋盘坐标

            if not i is None and not j is None:  # 棋子落在棋盘上，排除边缘
                # 棋子落在空白处
                if self.chessboard.get_XY_state(i, j) == EMPTY:
                    # 落子
                    self.draw(i, j)

                    # 判断是否有某方胜利
                    winner = self.chessboard.judge_Win()
                    if winner != EMPTY:
                        self.gameover(winner)

                    # # 交换棋子
                    # if self.piece_Now == BLACK:
                    #     self.mouse_Point.setPixmap(self.black)  # 加载白棋
                    # else:
                    #     self.mouse_Point.setPixmap(self.white)  # 加载黑棋

    def randomMove(self):
        """随机移动槽函数"""
        # 如果棋盘满了
        if self.chessboard.num == 225:
            self.chessboard.reset()
            self.step = 0
            for piece in self.pieces:
                piece.setPixmap(QPixmap(""))

        # 生成随机坐标
        i = random.randint(0, 14)
        j = random.randint(0, 14)
        while self.chessboard.get_XY_state(i, j) != EMPTY:
            i = random.randint(0, 14)
            j = random.randint(0, 14)

        # 落子
        self.draw(i, j)

    def draw(self, i, j):
        x, y = self.coordinate_transform_map2pixel(i, j)

        if self.piece_Now == BLACK:
            self.pieces[self.step].setPixmap(self.black)  # 放置黑色棋子
            self.piece_Now = WHITE
            self.chessboard.draw_XY(i, j)
        else:
            self.pieces[self.step].setPixmap(self.white)  # 放置白色棋子
            self.piece_Now = BLACK
            self.chessboard.draw_XY(i, j)

        self.pieces[self.step].setGeometry(x, y, PIECE, PIECE)  # 画出棋子
        self.step += 1

    def coordinate_transform_map2pixel(self, i, j):
        # 从 chessMap 里的逻辑坐标到 UI 上的绘制坐标的转换
        return MARGIN + j * GRID - PIECE / 2, MARGIN + i * GRID - PIECE / 2

    def coordinate_transform_pixel2map(self, x, y):
        # 从 UI 上的绘制坐标到 chessMap 里的逻辑坐标的转换
        i, j = int(round((y - MARGIN) / GRID)
                   ), int(round((x - MARGIN) / GRID))
        # 有MAGIN, 排除边缘位置导致 i,j 越界
        if i < 0 or i >= 15 or j < 0 or j >= 15:
            return None, None
        else:
            return i, j

    def gameover(self, winner):
        if winner == BLACK:
            reply = QMessageBox.question(self, 'You Win!', 'Continue?',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        else:
            reply = QMessageBox.question(self, 'You Lost!', 'Continue?',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.No)

        if reply == QMessageBox.Yes:  # 复位
            self.piece_now = BLACK
            self.step = 0
            for piece in self.pieces:
                piece.clear()
            self.chessboard.reset()
            self.update()
        else:
            self.close()

    def rand(self):
        i = 0
        while True:
            c = input("press any key to continue")
            self.randomMove()
            # 截屏
            img = ImageGrab.grab(bbox=(100, 100, 640, 640))
            img = img.convert('L')
            name = "C:/Users/王欣哲/Desktop/data/"+str(i)+".jpg"
            img.save(name)
            print(i)

            i += 1


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = GoBang()
   # ex.rand()
    sys.exit(app.exec_())
