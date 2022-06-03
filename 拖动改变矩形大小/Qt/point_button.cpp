#include "point_button.h"
#include <QString>
#include "window.h"

PointButton::PointButton(QWidget *parent): QPushButton(parent) {
    this->resize(10, 10);
    this->isPressed = false;
    this->setQss();
}

PointButton::~PointButton() {

}

void PointButton::setQss() {
    QString qss = "QPushButton {\n"
                  "border-radius: 5px;\n"
                  "border: 1px solid black;"
                  "background-color: rgb(255, 255, 255);\n"
                  "}\n"
                  "QPushButton:hover {\n"
                  "border-width: 2px;\n"
                  "}";

    this->setStyleSheet(qss);
}

void PointButton::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event);
    this->startX = event->x();
    this->startY = event->y();
    this->isPressed = true;
}

void PointButton::mouseMoveEvent(QMouseEvent *event) {
    QPushButton::mouseMoveEvent(event);
    float disX = event->x() - this->startX;
    float disY = event->y() - this->startY;
    this->move(this->x()+disX, this->y()+disY);
    Window *parent = (Window*) this->parent();
    parent->changeSize();
}

void PointButton::mouseReleaseEvent(QMouseEvent *event) {
    QPushButton::mouseReleaseEvent(event);
    this->isPressed = false;
}

