#ifndef LEVELUP_H
#define LEVELUP_H

#include <QWidget>
#include "tower.h"
#include "mypushbutton.h"
#include <QLabel>
class LevelUp : public QWidget
{
    Q_OBJECT
    Tower* tower;
    MyPushButton* sure;
    MyPushButton* cancel;
    QLabel* message;
public:
    explicit LevelUp(QWidget *parent = nullptr, Tower* tower = nullptr);

signals:
    void levelup(int i);
public slots:
    void emitSignal();
    void closeWindow();
};

#endif // LEVELUP_H
