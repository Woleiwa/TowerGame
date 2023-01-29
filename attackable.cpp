#include "attackable.h"
Attackable::Attackable(int attack, int hp, int scale, Tile position)
{
    this->attack = attack;
    this->hp = hp;
    this->scale = scale;
    this->position = position;
    this->max_hp = hp;
}

void Attackable::setAttack(int attack)
{
    this->attack = attack;
}

void Attackable::setHp(int hp)
{
    this->hplock.lock();
    this->hp = hp;
    if(this->hp > this->max_hp)
    {
        this->hp = this->max_hp;
    }
    else if(hp <= 0)
    {
        this->hp = 0;
    }
    this->hplock.unlock();
}

void Attackable::setMaxHp(int maxhp)
{
    this->max_hp = maxhp;
}

void Attackable::setScale(int scale)
{
    this->scale = scale;
}

void Attackable::setPosition(Tile position)
{
    this->position = position;
}

bool Attackable::insideScale(Attackable& another)
{
    return this->position.insideScale(another.position,this->scale);
}

void Attackable::attackEnenmy(Attackable& enemy)
{
    if(this->insideScale(enemy) && !enemy.isDead() && !this->isDead())
    {
        enemy.beAttacked(*this);
    }
}

void Attackable::beAttacked(Attackable& enemy)
{
    if(!enemy.isDead() && !this->isDead())
    {
        int myhp = this->getHp();
        int dhp = enemy.getAttack();
        if(myhp - dhp > 0)
        {
            this->setHp(myhp - dhp);
        }
        else
        {
            this->setHp(0);
        }
    }
}

int Attackable:: getDistance(const Attackable& another)
{
    return this->position.get_distance(another.position);
}

void Attackable:: getAttackByBullet(bullet* bptr)
{
    if(! this->isDead())
    {
        int myhp = this->getHp();
        int dhp = bptr->getAtk();
        if(myhp - dhp > 0)
        {
            this->setHp(myhp - dhp);
        }
        else
        {
            this->setHp(0);
        }
    }
}

buff* Attackable::getBuff(int i)
{
    if(i < 0 || i > 3)
    {
        return nullptr;
    }
    else
    {
        return this->bufflist[i];
    }
}

void Attackable::insertBuff(buff* bptr)
{
    for(int i = 0; i < 3; i++)
    {

        if(this->bufflist[i] != nullptr && *this->bufflist[i] == *bptr)
        {
            this->bufflist[i]->updateBuff(bptr->getLastTime() - this->bufflist[i]->getLastTime());
            return;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] == nullptr)
        {
            this->bufflist[i] = bptr;
            break;
        }
    }
}

int Attackable::getSlowDown()
{
    int res = -1;
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] != nullptr && this->bufflist[i]->getName() == "slowdown")
        {
            res = i;
            break;
        }
    }
    return res;
}

int Attackable::getFire()
{
    int res = -1;
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] != nullptr && this->bufflist[i]->getName() == "fire")
        {
            res = i;
            break;
        }
    }
    return res;
}

int Attackable::getMad()
{
    int res = -1;
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] != nullptr && this->bufflist[i]->getName() == "mad")
        {
            res = i;
            break;
        }
    }
    return res;
}

int Attackable::getFrozen()
{
    int res = -1;
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] != nullptr && this->bufflist[i]->getName() == "frozen")
        {
            res = i;
            break;
        }
    }
    return res;
}

buff* Attackable::getAtkBuff()
{
    for(int i = 0; i < 3; i++)
    {
        if(this->bufflist[i] != nullptr && this->bufflist[i]->getAtkFlag())
        {
            return this->bufflist[i];
        }
    }
    return nullptr;
}

int Attackable::getAttack()
{
    if(this->getMad() != -1)
    {
        return this->attack * 2;
    }
    return this->attack;
}
