#include "frosted_glass_label.h"
#include <Qt>
#include <QPalette>
#include <QColor>
#include <QGraphicsBlurEffect>

FrostedGlassLabel::FrostedGlassLabel(QWidget *parent)
    : QLabel(parent)
{
    this->resize(300, 100);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setBackgroundColor();
    this->blur();
}

FrostedGlassLabel::~FrostedGlassLabel()
{
}

void FrostedGlassLabel::setBackgroundColor() {
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(245, 245, 245, 250));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void FrostedGlassLabel::blur() {
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(30);
    blur->setBlurHints(QGraphicsBlurEffect::QualityHint);
    this->setGraphicsEffect(blur);
}

void FrostedGlassLabel::mousePressEvent(QMouseEvent *event) {
    QLabel::mousePressEvent(event);
    this->startX = event->x();
    this->startY = event->y();
}

void FrostedGlassLabel::mouseMoveEvent(QMouseEvent *event) {
    QLabel::mouseMoveEvent(event);
    float disX = event->x() - this->startX;
    float disY = event->y() - this->startY;
    this->move(this->x()+disX, this->y()+disY);
}
