import sys
from PyQt5.QtGui import QColor, QLinearGradient, QGradient
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QGraphicsDropShadowEffect



class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.resize(300, 600)
        self.btn1 = QPushButton('BUTTON')
        self.btn1.setObjectName('btn1')

        self.btn2 = QPushButton('BUTTON')
        self.btn2.setObjectName('btn2')
        shadow_effect = QGraphicsDropShadowEffect()
        shadow_effect.setOffset(0, 0)
        shadow_effect.setBlurRadius(20)
        shadow_effect.setColor(QColor('#21304e'))
        self.btn2.setGraphicsEffect(shadow_effect)

        v_layout = QVBoxLayout()
        v_layout.addWidget(self.btn1)
        v_layout.addWidget(self.btn2)
        self.setLayout(v_layout)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    with open('button.qss', encoding='utf-8') as f:
        qss = f.read()
    app.setStyleSheet(qss)

    window = Window()
    window.show()
    sys.exit(app.exec())