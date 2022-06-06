#include "button.h"
#include "window.h"

Button::Button(QString text, QWidget *parent):QPushButton(text, parent)
{

}

Button::~Button() {

}

void Button::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event);
    this->startX = event->x();
    this->startY = event->y();
}

void Button::mouseMoveEvent(QMouseEvent *event) {
    QPushButton::mouseMoveEvent(event);
    int disX = event->x() - this->startX;
    int disY = event->y() - this->startY;
    this->move(this->x()+disX, this->y()+disY);

    Window *win = (Window*) this->parent();
    win->checkPos(this);
}

void Button::mouseReleaseEvent(QMouseEvent *event) {
    QPushButton::mouseReleaseEvent(event);
}
