from PyQt5.QtWidgets import QPushButton


class Button(QPushButton):
    def __init__(self, text, parent):
        super(Button, self).__init__(text, parent)
        self.start_x = None
        self.start_y = None
        
    def mousePressEvent(self, event):
        super(Button, self).mousePressEvent(event)
        self.start_x = event.x()
        self.start_y = event.y()
        
    def mouseMoveEvent(self, event):
        super(Button, self).mouseMoveEvent(event)
        dis_x = event.x() - self.start_x
        dis_y = event.y() - self.start_y
        self.move(self.x()+dis_x, self.y()+dis_y)

        self.parent().check_pos(self)

    def mouseReleaseEvent(self, event):
        super(Button, self).mouseReleaseEvent(event)
        self.parent().is_vertical_center_line_shown = False
        self.parent().is_horizontal_center_line_shown = False
        self.parent().is_btn_left_line_shown = False
        self.parent().is_btn_top_line_shown = False
        self.parent().update()
