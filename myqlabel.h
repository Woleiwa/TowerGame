#ifndef MYQLABEL_H
#define MYQLABEL_H
#include <QTimer>
#include <QWidget>
#include <QLabel>
class MyQLabel : public QLabel
{
    Q_OBJECT
    QString file;
    QTimer* timer;
    double opacity = 1.0;
    double apopacity = 0;
    int x;
    int y;
    int height;
    int width;
    bool disappearflag = false;
protected:
    QTimer* qtimer;
    int i = 0;
public:
    MyQLabel(QWidget *parent = nullptr, QString file = "",int x = 0, int y = 0, int width = 0, int height = 0);
    void comeOut();
    void disappear();
    void appear();
    virtual void mousePressEvent(QMouseEvent *event);
    void zoom1();
    void zoom2();
    void test();
    int get_x() {return x;};
    int get_y() {return y;};
    int get_width() {return width;};
    int get_height() {return height;};
    void setPosition(int x, int y);
    void switchPicture(QString newfile);
    void set_i(int i){this->i = i;};
signals:
    void clicked();
    void clicked(int);
public slots:
    void fadeout();
    void appearin();
    void slottest();
};

#endif // MYQLABEL_H
