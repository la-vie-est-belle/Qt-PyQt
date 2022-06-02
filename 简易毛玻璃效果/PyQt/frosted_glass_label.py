import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPalette, QColor
from PyQt5.QtWidgets import QApplication, QLabel, QGraphicsBlurEffect


class FrostedGlassLabel(QLabel):
    def __init__(self):
        super(FrostedGlassLabel, self).__init__()
        self.resize(300, 100)
        self.setWindowFlags(Qt.FramelessWindowHint)     # 去除边框

        # 这两个变量用来移动窗口
        self.start_x = None
        self.start_y = None

        self.set_background_color()
        self.blur()

    def set_background_color(self):
        """设置窗口背景颜色"""
        palette = QPalette()
        palette.setColor(QPalette.Background, QColor(245, 245, 245, 250))
        self.setPalette(palette)
        self.setAutoFillBackground(True)

    def blur(self):
        """模糊"""
        blur = QGraphicsBlurEffect()
        blur.setBlurRadius(30)
        blur.setBlurHints(QGraphicsBlurEffect.QualityHint)
        self.setGraphicsEffect(blur)

    def mousePressEvent(self, event):
        super(FrostedGlassLabel, self).mousePressEvent(event)
        self.start_x = event.x()
        self.start_y = event.y()

    def mouseMoveEvent(self, event):
        super(FrostedGlassLabel, self).mouseMoveEvent(event)
        dis_x = event.x() - self.start_x
        dis_y = event.y() - self.start_y
        self.move(self.x() + dis_x, self.y() + dis_y)


if __name__ == '__main__':
    app = QApplication([])
    fg_label = FrostedGlassLabel()
    fg_label.show()
    sys.exit(app.exec())