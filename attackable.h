#ifndef ATTACKABLE_H
#define ATTACKABLE_H
#include "tile.h"
#include <QMutex>
#include "buff.h"
#include "bullet.h"
class Attackable
{
    int attack = 0;
    int hp = 0;
    int max_hp = 0;
    int scale = 0;
    Tile position;
    QMutex hplock;
    buff* bufflist[3] = {nullptr, nullptr, nullptr};
public:
    Attackable(){};
    Attackable(int attack, int hp, int scale, Tile position);
    int getAttack();
    int getHp(){return this->hp;};
    int getScale(){return this->scale;};
    int getMaxHp(){return this->max_hp;};
    int getDistance(const Attackable& another);
    Tile getPosition() {return this->position;};
    void setAttack(int attack);
    void setHp(int hp);
    void setScale(int scale);
    void setPosition(Tile position);
    void setMaxHp(int maxhp);
    bool isDead(){return this->hp == 0;};
    virtual bool insideScale(Attackable& another);
    virtual void beAttacked(Attackable& enemy);
    virtual void attackEnenmy(Attackable& enemy);
    void getAttackByBullet(bullet* bptr);
    buff* getBuff(int i);
    void insertBuff(buff* bptr);
    int getSlowDown();
    int getFire();
    int getMad();
    int getFrozen();
    void clearBuff(int i) {this->bufflist[i] = nullptr;};
    buff* getAtkBuff();
};

#endif // ATTACKABLE_H
