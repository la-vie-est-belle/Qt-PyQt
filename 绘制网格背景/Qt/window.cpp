#include "window.h"
#include <QColor>
#include <QPalette>
#include <QPointF>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    this->minGap = 4;
    this->maxGap = 14;
    this->gap = (this->minGap + this->maxGap) / 2;
    this->startX = this->width() / 2;
    this->startY = this->height() / 2;
    this->lightPen = QPen(QColor(222, 222, 222));
    this->darkPen = QPen(QColor(222, 222, 222));
    this->darkPen.setWidth(2);

    this->setBackgroundColor();
}

Window::~Window()
{
}

void Window::setBackgroundColor() {
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(250, 250, 250));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void Window::drawRowLines(QPainter *painter) {
    int lineCount = 0;
    float biggerY = this->startY;
    float smallerY = this->startY;

    painter->setPen(this->darkPen);

    while (true) {
        painter->drawLine(QPointF(0.0, biggerY), QPointF(this->width(), biggerY));
        painter->drawLine(QPointF(0.0, smallerY), QPointF(this->width(), smallerY));

        biggerY += this->gap;
        smallerY -= this->gap;
        if (smallerY <= 0 || biggerY >= this->height()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的横线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(this->darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(this->lightPen);
        }
    }

}

void Window::drawColLines(QPainter *painter) {
    int lineCount = 0;
    float biggerX = this->startX;
    float smallerX = this->startX;

    painter->setPen(this->darkPen);

    while (true) {
        painter->drawLine(QPointF(biggerX, 0.0), QPointF(biggerX, this->height()));
        painter->drawLine(QPointF(smallerX, 0.0), QPointF(smallerX, this->height()));

        biggerX += this->gap;
        smallerX -= this->gap;
        if (smallerX <= 0 || biggerX >= this->width()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的竖线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(this->darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(this->lightPen);
        }
    }

}

void Window::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    this->drawRowLines(&painter);
    this->drawColLines(&painter);
}

void Window::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    if (event->angleDelta().y() > 0) {
        this->gap += 0.1;
    }
    else if (event->angleDelta().y() < 0) {
        this->gap -= 0.1;
    }

    if (this->gap >= this->maxGap) {
        this->gap = this->minGap;
    }
    else if (this->gap <= this->minGap) {
        this->gap = this->maxGap;
    }

    this->update();
}

void Window::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this->startX = this->width() / 2;
    this->startY = this->height() / 2;
    this->update();
}
