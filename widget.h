#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "myqlabel.h"
#include "mypushbutton.h"
#include "storyscene.h"
#include "player.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    MyPushButton *bt;
    MyPushButton *bt2;
    MyQLabel *title;
    StoryScene* st;
    Player* p = nullptr;
private slots:
    void signIn();
    void playerRegister();
    void start(Player* player);
    void storyscene();
    void selectLevel();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
