#ifndef TOWERLABEL_H
#define TOWERLABEL_H
#include "myqlabel.h"
#include "tower.h"
#include "monster.h"

class TowerLabel:public MyQLabel
{
    Q_OBJECT
    Tower* tower;
    Monster* monster_enemy = nullptr;
    bool find_enemy = false;
    QLabel* hplabel;
    QTimer* attacktimer;
    MyQLabel* levelup;
    MyQLabel* Madbuff;
    bool emit_death = false;
    bool stop = false;
public:
    TowerLabel(QWidget *parent = nullptr, QString file = "",int x = 0, int y = 0, int width = 0, int height = 0, Tower* tower = nullptr);
    Tower* getTower() {return this->tower;};
    bool findEnemy() {return this->find_enemy;};
    void action();
    void getEnemy(Monster* mst);
    void updateHp();
    void getEnemy();
    void stopTower();
    void restart(){this->stop = false;}
    void handlebuff(string buffname);
signals:
    void killedEnemy(int i);
    void died(int i);
    void attack(int i);
    void launchBullet(int i,int t);
public slots:
    void attackEnemy();
    void levelUp();
    void recover();
    void updateMad();
};

#endif // TOWERLABEL_H
