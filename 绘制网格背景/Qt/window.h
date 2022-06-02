#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void setBackgroundColor();              // 设置窗口背景颜色
    void drawRowLines(QPainter *painter);   // 绘制横线
    void drawColLines(QPainter *painter);   // 绘制竖线

private:
   int minGap;                              // 最小线间隔
   int maxGap;                              // 最大线间隔
   float gap;                               // 当前线间隔
   float startX;                            // 竖线初始x坐标（从窗口中间开始）
   float startY;                            // 横线初始y坐标（从窗口中间开始）
   QPen lightPen;                           // 细一点的画笔
   QPen darkPen;                            // 粗一点的画笔
};
#endif // WINDOW_H
