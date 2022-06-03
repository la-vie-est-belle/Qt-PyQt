import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPen, QPainter
from PyQt5.QtWidgets import QApplication, QWidget
from point_button import PointButton


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.resize(500, 500)

        self.pen = QPen(Qt.black)
        self.x1 = None                  # x1和y1是矩形左上角坐标
        self.y1 = None
        self.x2 = None                  # x2和y2是矩形右下角坐标
        self.y2 = None

        self.top_left_btn = PointButton(self)
        self.top_right_btn = PointButton(self)
        self.bottom_left_btn = PointButton(self)
        self.bottom_right_btn = PointButton(self)
        self.hide_corner_btns()

    def mousePressEvent(self, event):
        super(Window, self).mousePressEvent(event)

        self.x1 = None
        self.y1 = None
        self.x2 = None
        self.y2 = None
        self.hide_corner_btns()

        self.x1 = event.x()
        self.y1 = event.y()
        self.update()

    def mouseMoveEvent(self, event):
        super(Window, self).mouseMoveEvent(event)

        if self.top_left_btn.is_pressed or self.top_right_btn.is_pressed or \
           self.bottom_left_btn.is_pressed or self.bottom_right_btn.is_pressed:
           return

        self.x2 = event.x()
        self.y2 = event.y()
        self.update()

    def paintEvent(self, event):
        """绘制矩形并更新边角拖曳按钮"""
        super(Window, self).paintEvent(event)

        if self.x1 is None or self.y1 is None or self.x2 is None or self.y2 is None:
            return

        # 绘制矩形
        painter = QPainter(self)
        painter.setPen(self.pen)
        width = self.x2 - self.x1
        height = self.y2 - self.y1
        painter.drawRect(self.x1, self.y1, width, height)

        # 设置边角按钮位置并显示
        self.show_corner_btns()

    def hide_corner_btns(self):
        """隐藏边角拖曳按钮"""
        self.top_left_btn.hide()
        self.top_right_btn.hide()
        self.bottom_left_btn.hide()
        self.bottom_right_btn.hide()

    def show_corner_btns(self):
        """设置边角拖曳按钮位置并显示"""
        half_width = int(self.top_left_btn.width() / 2)
        half_height = int(self.top_left_btn.height() / 2)
        self.top_left_btn.move(self.x1-half_width, self.y1-half_height)
        self.top_right_btn.move(self.x2-half_width, self.y1-half_height)
        self.bottom_left_btn.move(self.x1-half_width, self.y2-half_height)
        self.bottom_right_btn.move(self.x2-half_width, self.y2-half_height)

        self.top_left_btn.show()
        self.top_right_btn.show()
        self.bottom_left_btn.show()
        self.bottom_right_btn.show()

    def change_size(self):
        """改变矩形尺寸"""
        if self.top_left_btn.is_pressed:
            self.x1 = int(self.top_left_btn.x()+self.top_left_btn.width()/2)
            self.y1 = int(self.top_left_btn.y()+self.top_left_btn.height()/2)
        elif self.top_right_btn.is_pressed:
            self.x2 = int(self.top_right_btn.x()+self.top_right_btn.width()/2)
            self.y1 = int(self.top_right_btn.y()+self.top_right_btn.height()/2)
        elif self.bottom_left_btn.is_pressed:
            self.x1 = int(self.bottom_left_btn.x()+self.bottom_left_btn.width()/2)
            self.y2 = int(self.bottom_left_btn.y()+self.bottom_left_btn.height()/2)
        elif self.bottom_right_btn.is_pressed:
            self.x2 = int(self.bottom_right_btn.x()+self.bottom_right_btn.width()/2)
            self.y2 = int(self.bottom_right_btn.y()+self.bottom_right_btn.height()/2)

        self.update()


if __name__ == '__main__':
    app = QApplication([])
    window = Window()
    window.show()
    sys.exit(app.exec())

