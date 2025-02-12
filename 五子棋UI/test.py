import sys

from PyQt5.QtMultimedia import QSound
from PyQt5.QtGui import QPixmap, QIcon, QPalette, QPainter
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QMessageBox
from PyQt5 import QtCore, QtGui

app = QApplication(sys.argv)

WIDTH = 540
HEIGHT = 540
MARGIN = 22
GRID = (WIDTH - 2 * MARGIN) / (15 - 1)
PIECE = 34
EMPTY = 0
BLACK = 1
WHITE = 2


class Windo(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(WIDTH, HEIGHT)
        self.setMinimumSize(QtCore.QSize(WIDTH, HEIGHT))
        self.setMaximumSize(QtCore.QSize(WIDTH, HEIGHT))

        self.setWindowTitle("五子棋")  # 窗口名称

        # 棋盘背景
        palette = QPalette()
        palette.setBrush(self.backgroundRole(), QtGui.QBrush(
            QtGui.QPixmap("C:\\Users\\王欣哲\\Desktop\\codes\\人工智能基础\\五子棋UI\\img\\chess.png")))
        self.setPalette(palette)

        self.show()

    def mousePressEvent(self, e):
        """鼠标按键响应函数"""
        print("Got a press!")
        if e.buttons() == Qt.LeftButton:
            print("Here!")


ex = Windo()
sys.exit(app.exec_())
