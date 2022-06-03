#ifndef POINTBUTTON_H
#define POINTBUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QMouseEvent>

class PointButton : public QPushButton
{
public:
    PointButton(QWidget *parent);
    ~PointButton();

public:
    bool isPressed;                                 // 用来判断用户是否正按在拖曳按钮上

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void setQss();                                  // 设置拖曳按钮样式

private:
    float startX;                                   // 用来移动拖曳按钮
    float startY;
};

#endif // POINTBUTTON_H
