import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QColor, QLinearGradient, QGradient
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QHBoxLayout, QVBoxLayout, QGraphicsDropShadowEffect



class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.resize(300, 600)
        self.btn1 = QPushButton('BUTTON 1')
        self.btn1.setObjectName('btn1')

        self.btn2 = QPushButton('BUTTON 2')
        self.btn2.setObjectName('btn2')
        shadow_effect = QGraphicsDropShadowEffect()
        shadow_effect.setOffset(0, 0)
        shadow_effect.setBlurRadius(20)
        shadow_effect.setColor(QColor('#21304e'))
        self.btn2.setGraphicsEffect(shadow_effect)

        self.btn3 = QPushButton('BUTTON 3')
        self.btn3.setObjectName('btn3')
        self.btn3.setFixedSize(100, 100)

        self.btn4 = QPushButton()
        self.btn4.setObjectName('btn4')
        self.btn4.setFixedSize(100, 100)

        v_layout = QVBoxLayout()
        v_layout.addWidget(self.btn1)
        v_layout.addWidget(self.btn2)
        h_layout = QHBoxLayout()
        h_layout.addWidget(self.btn3)
        v_layout.addLayout(h_layout)
        h_layout2 = QHBoxLayout()
        h_layout2.addWidget(self.btn4)
        v_layout.addLayout(h_layout2)
        self.setLayout(v_layout)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    with open('button.qss', encoding='utf-8') as f:
        qss = f.read()
    app.setStyleSheet(qss)

    window = Window()
    window.show()
    sys.exit(app.exec())