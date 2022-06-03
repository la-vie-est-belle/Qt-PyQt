#include "window.h"
#include <Qt>
#include <QPainter>
#include <QDebug>


Window::Window(QWidget *parent): QWidget(parent) {
    this->pen = QPen(Qt::black);
    this->topLeftBtn = new PointButton(this);
    this->topRightBtn = new PointButton(this);
    this->bottomLeftBtn = new PointButton(this);
    this->bottomRightBtn = new PointButton(this);

    this->x1 = float(NULL);
    this->y1 = float(NULL);
    this->x2 = float(NULL);
    this->y2 = float(NULL);
    this->hideCornerBtns();
}

Window::~Window() {

}

void Window::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    this->x1 = float(NULL);
    this->y1 = float(NULL);
    this->x2 = float(NULL);
    this->y2 = float(NULL);
    this->hideCornerBtns();

    this->x1 = event->x();
    this->y1 = event->y();
    this->update();

}

void Window::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);

    if (this->topLeftBtn->isPressed || this->topRightBtn->isPressed ||
        this->bottomLeftBtn->isPressed || this->bottomRightBtn->isPressed)
        return;

    this->x2 = event->x();
    this->y2 = event->y();
    this->update();
}

void Window::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    if (this->x1==float(NULL) || this->y1==float(NULL) || this->x2==float(NULL) || this->y2==float(NULL)) {
        return;
    }

    QPainter painter(this);
    painter.setPen(this->pen);
    int width = this->x2 - this->x1;
    int height = this->y2 - this->y1;
    painter.drawRect(this->x1, this->y1, width, height);

    this->showCornerBtns();
}

void Window::hideCornerBtns() {
    this->topLeftBtn->hide();
    this->topRightBtn->hide();
    this->bottomLeftBtn->hide();
    this->bottomRightBtn->hide();
}

void Window::showCornerBtns() {
    int halfWidth = int(this->topLeftBtn->width() / 2);
    int halfHeight = int(this->topLeftBtn->height() / 2);
    this->topLeftBtn->move(this->x1-halfWidth, this->y1-halfHeight);
    this->topRightBtn->move(this->x2-halfWidth, this->y1-halfHeight);
    this->bottomLeftBtn->move(this->x1-halfWidth, this->y2-halfHeight);
    this->bottomRightBtn->move(this->x2-halfWidth, this->y2-halfHeight);

    this->topLeftBtn->show();
    this->topRightBtn->show();
    this->bottomLeftBtn->show();
    this->bottomRightBtn->show();
}

void Window::changeSize() {
    if (this->topLeftBtn->isPressed) {
        this->x1 = int(this->topLeftBtn->x() + this->topLeftBtn->width()/2);
        this->y1 = int(this->topLeftBtn->y() + this->topLeftBtn->height()/2);
    }
    else if (this->topRightBtn->isPressed) {
        this->x2 = int(this->topRightBtn->x() + this->topRightBtn->width()/2);
        this->y1 = int(this->topRightBtn->y() + this->topRightBtn->height()/2);
    }
    else if (this->bottomLeftBtn->isPressed) {
        this->x1 = int(this->bottomLeftBtn->x() + this->bottomLeftBtn->width()/2);
        this->y2 = int(this->bottomLeftBtn->y() + this->bottomLeftBtn->height()/2);
    }
    else if (this->bottomRightBtn->isPressed) {
        this->x2 = int(this->bottomRightBtn->x() + this->bottomRightBtn->width()/2);
        this->y2 = int(this->bottomRightBtn->y() + this->bottomRightBtn->height()/2);
    }
    this->update();
}

