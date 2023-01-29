#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
    QString file;
    int level;
    int x;
    int y;
public:
    MyPushButton(QWidget *parent = nullptr, QString file = "", int x = 0,int y = 0, int width = 0, int height = 0);
    void setLevel(int level);
    bool zoom1();
    void zoom2();
    void move(int end_x, int end_y);
    void mousePressEvent(QMouseEvent *event);
signals:
    void clicked(int i);
    void clicked();
};

#endif // MYPUSHBUTTON_H
