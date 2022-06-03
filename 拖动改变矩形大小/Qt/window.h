#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPen>

#include "point_button.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
    void changeSize();                              // 改变矩形尺寸
    void hideCornerBtns();                          // 隐藏边角拖曳按钮
    void showCornerBtns();                          // 设置边角拖曳按钮位置并显示

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    int x1;                                         // x1和y1是矩形左上角坐标
    int y1;
    int x2;                                         // x2和y2是矩形右下角坐标
    int y2;

    QPen pen;

    PointButton *topLeftBtn;
    PointButton *topRightBtn;
    PointButton *bottomLeftBtn;
    PointButton *bottomRightBtn;
};
#endif // WINDOW_H
