import sys
from PyQt5.QtCore import QPointF
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QPainter, QPen, QColor, QPalette


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.resize(600, 400)

        self.min_gap = 4                                    # 最小线间隔
        self.max_gap = 14                                   # 最大线间隔
        self.gap = (self.min_gap + self.max_gap) / 2        # 当前线间隔
        self.start_x = self.width() / 2                     # 竖线初始x坐标（从窗口中间开始）
        self.start_y = self.height() / 2                    # 横线初始y坐标（从窗口中间开始）
        self.light_pen = QPen(QColor(222, 222, 222))        # 两只粗细不同的画笔
        self.dark_pen = QPen(QColor(222, 222, 222))
        self.dark_pen.setWidth(2)

        self.set_background_color()

    def set_background_color(self):
        """设置窗口背景颜色"""
        palette = QPalette()
        palette.setColor(QPalette.Background, QColor(250, 250, 250))
        self.setPalette(palette)
        self.setAutoFillBackground(True)

    def draw_row_lines(self, painter):
        """画横线"""
        line_count = 0
        bigger_y = self.start_y
        smaller_y = self.start_y

        painter.setPen(self.dark_pen)

        while True:
            painter.drawLine(QPointF(0.0, bigger_y), QPointF(self.width(), bigger_y))
            painter.drawLine(QPointF(0.0, smaller_y), QPointF(self.width(), smaller_y))

            bigger_y += self.gap
            smaller_y -= self.gap
            if smaller_y <= 0 or bigger_y >= self.height():
                break

            # 每间隔一定数量的线，就画一条粗一点的横线
            line_count += 1
            if line_count == 10:
                painter.setPen(self.dark_pen)
                line_count = 0
            else:
                painter.setPen(self.light_pen)

    def draw_col_lines(self, painter):
        """画竖线"""
        line_count = 0
        bigger_x = self.start_x
        smaller_x = self.start_x

        painter.setPen(self.dark_pen)

        while True:
            painter.drawLine(QPointF(bigger_x, 0.0), QPointF(bigger_x, self.height()))
            painter.drawLine(QPointF(smaller_x, 0.0), QPointF(smaller_x, self.height()))

            bigger_x += self.gap
            smaller_x -= self.gap
            if smaller_x <= 0 or bigger_x >= self.width():
                break

            # 每间隔一定数量的线，就画一条粗一点的竖线
            line_count += 1
            if line_count == 10:
                painter.setPen(self.dark_pen)
                line_count = 0
            else:
                painter.setPen(self.light_pen)

    def paintEvent(self, event):
        super(Window, self).paintEvent(event)
        painter = QPainter(self)
        self.draw_row_lines(painter)
        self.draw_col_lines(painter)

    def wheelEvent(self, event):
        """滚轮控制线间隔"""
        super(Window, self).wheelEvent(event)
        if event.angleDelta().y() > 0:
            self.gap += 0.1
        elif event.angleDelta().y() < 0:
            self.gap -= 0.1

        if self.gap >= self.max_gap:
            self.gap = self.min_gap
        elif self.gap <= self.min_gap:
            self.gap = self.max_gap

        self.update()

    def resizeEvent(self, event):
        super(Window, self).resizeEvent(event)
        self.start_x = self.width() / 2
        self.start_y = self.height() / 2
        self.update()


if __name__ == '__main__':
    app = QApplication([])
    area = Window()
    area.show()
    sys.exit(app.exec())
