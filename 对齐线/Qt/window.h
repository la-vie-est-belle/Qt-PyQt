#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>
#include <QPen>

#include "button.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
    void checkPos(Button *movingBtn);                   // 检查按钮位置

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void changeBtnNum(int newNum);                      // 改变按钮数量

private:
    void drawVerticalCenterLine(QPainter &painter);     // 绘制垂直中心线
    void drawHorizontalCenterLine(QPainter &painter);   // 绘制水平中心线
    void drawBtnLeftLine(QPainter &painter);            // 绘制按钮左侧线
    void drawBtnTopLine(QPainter &painter);             // 绘制按钮顶部线
    void checkBtnTopLine(Button *movingBtn);            // 比对当前移动按钮和其他按钮顶部的位置
    void checkBtnLeftLine(Button *movingBtn);           // 比对当前移动按钮和其他按钮左侧的位置
    void checkWindowCenterLines(Button *movingBtn);     // 比对按钮和中心线的位置

private:
    QSpinBox *spinBox;
    QList<Button *> btnList;

    int lineShowThresholdValue;                         // 线条显示阈值
    int lineAdsorbThresholdValue;                       // 线条吸附阈值
    bool isVerticalCenterLineShown;                     // 是否显示中心竖线
    bool isHorizontalCenterLineShown;                   // 是否显示中心横线
    bool isBtnLeftLineShown;                            // 是否显示按钮左侧线条
    bool isBtnTopLineShown;                             // 是否显示按钮顶部线条

    int btnLeftLineX;                                   // 按钮左侧线x坐标
    int btnTopLineY;                                    // 按钮顶部线y坐标

    QPen pen1;                                          // 用来绘制中心对齐线
    QPen pen2;                                          // 用来绘制按钮间的对齐线
};
#endif // WINDOW_H
