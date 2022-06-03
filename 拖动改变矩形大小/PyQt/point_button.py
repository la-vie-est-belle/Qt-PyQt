from PyQt5.QtWidgets import QPushButton


class PointButton(QPushButton):
    def __init__(self, parent):
        super(PointButton, self).__init__(parent)
        self.resize(10, 10)

        self.start_x = None             # 用来移动拖曳按钮
        self.start_y = None
        self.is_pressed = False         # 用来判断用户是否正按在拖曳按钮上

        self.set_qss()

    def set_qss(self):
        """设置拖曳按钮样式"""
        qss = """
            QPushButton {
                border-radius: 5px;
                border: 1px solid black;
                background-color: rgb(255, 255, 255);
            }
            
            QPushButton:hover {
                border-width: 2px;
            }
        """
        self.setStyleSheet(qss)

    def mousePressEvent(self, event):
        super(PointButton, self).mousePressEvent(event)
        self.start_x = event.x()
        self.start_y = event.y()
        self.is_pressed = True

    def mouseMoveEvent(self, event):
        super(PointButton, self).mouseMoveEvent(event)
        dis_x = event.x() - self.start_x
        dis_y = event.y() - self.start_y
        self.move(self.x() + dis_x, self.y() + dis_y)
        self.parent().change_size()

    def mouseReleaseEvent(self, event):
        super(PointButton, self).mouseReleaseEvent(event)
        self.is_pressed = False



