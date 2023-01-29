#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QWidget>
#include "mypushbutton.h"
#include "player.h"
#include "stringlabel.h"

class SelectLevel : public QWidget
{
    Q_OBJECT
    MyPushButton** buttons;
    MyPushButton* logout;
    MyPushButton* left;
    MyPushButton* right;
    Player* player;
    StringLabel** label;
    int page = 1;
public:
    explicit SelectLevel(QWidget *parent = nullptr, Player* player = nullptr);

signals:

public slots:
    void TurnLeft();
    void TurnRight();
    void startGame(int i);
    void logOut();
    void reShow();
    void update(int level, int score);
};

#endif // SELECTLEVEL_H
