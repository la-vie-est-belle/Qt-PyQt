#include "window.h"
#include <Qt>
#include <QString>
#include <cstdlib>

Window::Window(QWidget *parent): QWidget(parent)
{
    this->resize(500, 500);
    this->spinBox = new QSpinBox(this);
    this->spinBox->setValue(0);
    this->spinBox->move(10, 10);
    connect(this->spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Window::changeBtnNum);

    this->lineShowThresholdValue = 5;
    this->lineAdsorbThresholdValue = 3;

    this->isVerticalCenterLineShown = false;
    this->isHorizontalCenterLineShown = false;
    this->isBtnLeftLineShown = false;
    this->isBtnTopLineShown = false;

    this->btnLeftLineX = 0;
    this->btnTopLineY = 0;

    this->pen1 = QPen(Qt::darkBlue);
    this->pen2 = QPen(Qt::gray);
}

Window::~Window()
{
}

void Window::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(this->pen1);

    if (this->isVerticalCenterLineShown) {
        this->drawVerticalCenterLine(painter);
    }

    if (this->isHorizontalCenterLineShown) {
        this->drawHorizontalCenterLine(painter);
    }

    painter.setPen(this->pen2);
    if (this->isBtnLeftLineShown) {
        this->drawBtnLeftLine(painter);
    }

    if (this->isBtnTopLineShown) {
        this->drawBtnTopLine(painter);
    }
}

void Window::drawVerticalCenterLine(QPainter &painter) {
    int verticalCenterValue = int(this->width() / 2);
    painter.drawLine(verticalCenterValue, 0, verticalCenterValue, this->height());
}

void Window::drawHorizontalCenterLine(QPainter &painter) {
    int horizontalCenterValue = int(this->height() / 2);
    painter.drawLine(0, horizontalCenterValue, this->width(), horizontalCenterValue);
}

void Window::drawBtnLeftLine(QPainter &painter) {
    int x = this->btnLeftLineX;
    painter.drawLine(x, 0, x, this->height());
}

void Window::drawBtnTopLine(QPainter &painter) {
    int y = this->btnTopLineY;
    painter.drawLine(0, y, this->width(), y);
}

void Window::checkPos(Button *movingBtn) {
    this->checkBtnTopLine(movingBtn);
    this->checkBtnLeftLine(movingBtn);
    this->checkWindowCenterLines(movingBtn);
    this->update();
}

void Window::checkBtnTopLine(Button *movingBtn) {
    int x = movingBtn->x();
    int y = movingBtn->y();

    for (int i=0; i<this->btnList.size(); i++) {
        Button *btn = this->btnList.at(i);
        if (btn == movingBtn) {
            continue;
        }

        if (y>btn->y()-this->lineShowThresholdValue && y<btn->y()+this->lineShowThresholdValue) {
            this->isBtnTopLineShown = true;
            this->btnTopLineY = btn->y();

            if (y>btn->y()-this->lineAdsorbThresholdValue && y<btn->y()+this->lineAdsorbThresholdValue) {
                movingBtn->move(x, btn->y());
            }
            return;
        }
        else {
            this->isBtnTopLineShown = false;
            this->btnTopLineY = 0;
        }
    }
}

void Window::checkBtnLeftLine(Button *movingBtn) {
    int x = movingBtn->x();
    int y = movingBtn->y();

    for (int i=0; i<this->btnList.size(); i++) {
        Button *btn = this->btnList.at(i);
        if (btn == movingBtn) {
            continue;
        }

        if (x>btn->x()-this->lineShowThresholdValue && x<btn->x()+this->lineShowThresholdValue) {
            this->isBtnLeftLineShown = true;
            this->btnLeftLineX = btn->x();

            if (x>btn->x()-this->lineAdsorbThresholdValue && x<btn->x()+this->lineAdsorbThresholdValue) {
                movingBtn->move(btn->x(), y);
            }
            return;
        }
        else {
            this->isBtnLeftLineShown = false;
            this->btnLeftLineX = 0;
        }
    }
}

void Window::checkWindowCenterLines(Button *movingBtn) {
    int x = movingBtn->x();
    int y = movingBtn->y();

    int verticalCenterValue = int(this->width()/2) - int(movingBtn->width()/2);
    int horizontalCenterValue = int(this->width()/2) - int(movingBtn->height()/2);

    // 判断是否显示中心竖线
    if (x>verticalCenterValue-this->lineShowThresholdValue && x<verticalCenterValue+this->lineShowThresholdValue) {
        this->isVerticalCenterLineShown = true;

        // 判断是否吸附
        if (x>verticalCenterValue-this->lineAdsorbThresholdValue && x<verticalCenterValue+this->lineAdsorbThresholdValue) {
            movingBtn->move(verticalCenterValue, y);
        }
    }
    else {
        this->isVerticalCenterLineShown = false;
    }

    // 判断是否显示中心横线
    if (y>horizontalCenterValue-this->lineShowThresholdValue && y<horizontalCenterValue+this->lineShowThresholdValue) {
        this->isHorizontalCenterLineShown = true;

        // 判断是否吸附
        if (y>horizontalCenterValue-this->lineAdsorbThresholdValue && y<horizontalCenterValue+this->lineAdsorbThresholdValue) {
            movingBtn->move(x, horizontalCenterValue);
        }
    }
    else {
        this->isHorizontalCenterLineShown = false;
    }
}

void Window::changeBtnNum(int newNum) {
    int currentNum = this->btnList.size();

    if (currentNum < newNum) {
        int diff = newNum - currentNum;
        for (int i=0; i<diff; i++) {
            QString text = QString("button%1").arg(currentNum);
            Button *btn = new Button(text, this);
            int x = rand() % (this->width()-btn->width()+1);
            int y = rand() % (this->height()-btn->width()+1);
            btn->move(x, y);
            btn->show();
            this->btnList.append(btn);
        }
    }
    else if (currentNum > newNum) {
        int diff = currentNum - newNum;
        for (int i=0; i<diff; i++) {
            Button *btn = this->btnList.takeLast();
            btn->deleteLater();
        }
    }
}

