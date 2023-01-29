#ifndef MONSTERLABEL_H
#define MONSTERLABEL_H
#include "myqlabel.h"
#include "monster.h"
#include <QProgressBar>
#include "tower.h"
class MonsterLabel:public MyQLabel
{
    Q_OBJECT
    Monster* monster;
    std::vector<Tile> route;
    int step = 0;
    QLabel* hplabel;
    bool blocked = false;
    bool find_enemy = false;
    bool emit_death = false;
    bool stop = false;
    Tower* tower_enemy = nullptr;
    bool runned = false;
    QTimer* movetimer;
    QTimer* attacktimer;
    MyQLabel* sldbuff;
    MyQLabel* firebuff;
    MyQLabel* light;
    MyQLabel* frozenbuff;
    bool frozen = false;
public:
    MonsterLabel(QWidget *parent = nullptr, QString file = "",int x = 0, int y = 0, int width = 0, int height = 0, Monster* monster = nullptr);
    void set(std::vector<Tile> route) {this->route = route;};
    void setRank(int i){this->monster->setRank(i);};
    void changeDirection();
    Monster* getMonster(){return this->monster;};
    void action();
    Tile getNext();
    void block() {this->blocked = true;};
    void setfree() {this->blocked = false;};
    bool findEnemy() {return this->find_enemy;};
    void getEnemy(Tower* tw);
    void updateHp();
    void stopMonster();
    void restart(){this->stop = false;}
    void handleSlowDown();
    void handleFire();
    bool isRunned() {return this->runned;};
    void getAttackByBullet(bullet * bptr);
    void getlighted();
    void handlebuff(string buffname);
public slots:
    void monsterMove();
    void monsterAttack(){};
    void monsterDied(){};
    void attackEnemy();
    void updateSlowDown();
    void updateFire();
    void updateFrozen();
    void updateMad();
signals:
    void runed(int i);
    void moved(int i);
    void attack(int i);
    void killedEnemy(int i);
    void died(int i);
    void launchBullet(int i, int target);
};

#endif // MONSTERLABEL_H
