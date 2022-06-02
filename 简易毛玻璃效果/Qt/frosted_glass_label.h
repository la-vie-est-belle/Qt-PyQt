#ifndef FROSTEDGLASSLABEL_H
#define FROSTEDGLASSLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class FrostedGlassLabel : public QLabel
{
    Q_OBJECT

public:
    FrostedGlassLabel(QWidget *parent = nullptr);
    ~FrostedGlassLabel();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void setBackgroundColor();                  // 设置窗口背景颜色
    void blur();                                // 模糊

private:
    float startX;                               // 这两个变量用来移动窗口
    float startY;

};
#endif // FROSTEDGLASSLABEL_H
