#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QMouseEvent>


class Button: public QPushButton
{
    Q_OBJECT

public:
    Button(QString text, QWidget *parent=nullptr);
    ~Button();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int startX;
    int startY;
};

#endif // BUTTON_H
