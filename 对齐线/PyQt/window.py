import sys
import random
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPen, QPainter
from PyQt5.QtWidgets import QApplication, QWidget, QSpinBox
from button import Button


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.resize(500, 500)
        self.spin_box = QSpinBox(self)
        self.spin_box.setValue(0)
        self.spin_box.move(10, 10)
        self.spin_box.valueChanged.connect(self.change_btn_num)

        self.btn_list = []

        self.line_show_threshold_value = 5                      # 线条显示阈值
        self.line_adsorb_threshold_value = 3                    # 线条吸附阈值

        self.is_vertical_center_line_shown = False              # 是否显示中心竖线
        self.is_horizontal_center_line_shown = False            # 是否显示中心横线
        self.is_btn_left_line_shown = False                     # 是否显示按钮左侧线条
        self.is_btn_top_line_shown = False                      # 是否显示按钮顶部线条

        self.btn_left_line_x = 0                                # 按钮左侧线x坐标
        self.btn_top_line_y = 0                                 # 按钮顶部线y坐标

        self.pen1 = QPen(Qt.darkBlue)                           # 用来绘制中心对齐线
        self.pen2 = QPen(Qt.gray)                               # 用来绘制按钮间的对齐线

    def paintEvent(self, event):
        super(Window, self).paintEvent(event)
        painter = QPainter(self)
        painter.setPen(self.pen1)

        if self.is_vertical_center_line_shown:
            self.draw_vertical_center_line(painter)

        if self.is_horizontal_center_line_shown:
            self.draw_horizontal_center_line(painter)

        painter.setPen(self.pen2)
        if self.is_btn_left_line_shown:
            self.draw_btn_left_line(painter)

        if self.is_btn_top_line_shown:
            self.draw_btn_top_line(painter)

    def draw_vertical_center_line(self, painter):
        """绘制垂直中心线"""
        vertical_center_value = int(self.width() / 2)
        painter.drawLine(vertical_center_value, 0, vertical_center_value, self.height())

    def draw_horizontal_center_line(self, painter):
        """绘制水平中心线"""
        horizontal_center_value = int(self.height() / 2)
        painter.drawLine(0, horizontal_center_value, self.width(), horizontal_center_value)

    def draw_btn_left_line(self, painter):
        """绘制按钮左侧线"""
        x = self.btn_left_line_x
        painter.drawLine(x, 0, x, self.height())

    def draw_btn_top_line(self, painter):
        """绘制按钮顶部线"""
        y = self.btn_top_line_y
        painter.drawLine(0, y, self.width(), y)

    def check_pos(self, moving_btn):
        """检查按钮位置"""
        self.check_btn_top_line(moving_btn)
        self.check_btn_left_line(moving_btn)
        self.check_window_center_lines(moving_btn)
        self.update()

    def check_btn_top_line(self, moving_btn):
        """比对当前移动按钮和其他按钮顶部的位置"""
        x = moving_btn.x()
        y = moving_btn.y()

        for btn in self.btn_list:
            if btn is moving_btn:
                continue

            if y>btn.y()-self.line_show_threshold_value and y<btn.y()+self.line_show_threshold_value:
                self.is_btn_top_line_shown = True
                self.btn_top_line_y = btn.y()

                if y>btn.y()-self.line_adsorb_threshold_value and y<btn.y()+self.line_adsorb_threshold_value:
                    moving_btn.move(x, btn.y())

                return
            else:
                self.is_btn_top_line_shown = False
                self.btn_top_line_y = 0

    def check_btn_left_line(self, moving_btn):
        """比对当前移动按钮和其他按钮左侧的位置"""
        x = moving_btn.x()
        y = moving_btn.y()

        for btn in self.btn_list:
            if btn is moving_btn:
                continue

            if x>btn.x()-self.line_show_threshold_value and x<btn.x()+self.line_show_threshold_value:
                self.is_btn_left_line_shown = True
                self.btn_left_line_x = btn.x()

                # 判断是否吸附
                if x>btn.x()-self.line_adsorb_threshold_value and x<btn.x()+self.line_adsorb_threshold_value:
                    moving_btn.move(btn.x(), y)

                return
            else:
                self.is_btn_left_line_shown = False
                self.btn_left_line_x = 0

    def check_window_center_lines(self, moving_btn):
        """比对按钮和中心线的位置"""
        x = moving_btn.x()
        y = moving_btn.y()

        vertical_center_value = int(self.width()/2) - int(moving_btn.width()/2)
        horizontal_center_value = int(self.height()/2) - int(moving_btn.height()/2)

        # 判断是否显示中心竖线
        if x>vertical_center_value-self.line_show_threshold_value and x<vertical_center_value+self.line_show_threshold_value:
            self.is_vertical_center_line_shown = True

            # 判断是否吸附
            if x>vertical_center_value-self.line_adsorb_threshold_value and x<vertical_center_value+self.line_adsorb_threshold_value:
                moving_btn.move(vertical_center_value, y)
        else:
            self.is_vertical_center_line_shown = False

        # 判断是否显示中心横线
        if y>horizontal_center_value-self.line_show_threshold_value and y<horizontal_center_value+self.line_show_threshold_value:
            self.is_horizontal_center_line_shown = True

            # 判断是否吸附
            if y>horizontal_center_value-self.line_adsorb_threshold_value and y<horizontal_center_value+self.line_adsorb_threshold_value:
                moving_btn.move(x, horizontal_center_value)
        else:
            self.is_horizontal_center_line_shown = False

    def change_btn_num(self, new_num):
        """改变按钮数量"""
        current_num = len(self.btn_list)

        if current_num < new_num:
            diff = new_num - current_num
            for i in range(diff):
                text = f'button {1+i+current_num}'
                btn = Button(text, self)
                x = random.randint(0, self.width()-btn.width())
                y = random.randint(0, self.height()-btn.height())
                btn.move(x, y)
                btn.show()
                self.btn_list.append(btn)
        elif current_num > new_num:
            for i in range(current_num - new_num):
                btn = self.btn_list.pop()
                btn.deleteLater()


if __name__ == '__main__':
    app = QApplication([])
    window = Window()
    window.show()
    sys.exit(app.exec())