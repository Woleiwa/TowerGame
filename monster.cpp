#include "monster.h"
#include <fstream>
Monster::Monster(int attack, int hp, int scale,Tile position, int speed, string direction, string name, int value, int frequence)
{
    this->setAttack(attack);
    this->setHp(hp);
    this->setScale(scale);
    this->setPosition(position);
    this->frequence = frequence;
    this->speed = speed;
    this->name = name;
    this->value = value;
    this->direction = direction;
}

Monster::Monster(string name, Tile position)
{
    this->name = name;
    this->setPosition(position);
    this->readFromTxt();
}

int Monster::getSpeed()
{
    /*if(this->getSlowDown() != -1)
    {
        return this->speed/2;
    }*/
    return this->speed;
}

void Monster::readFromTxt()
{
    string file = "E://code/test/monster_setting/";
    file += this->name + ".txt";
    ifstream monsterfile(file);
    int atk;
    int hp;
    int scale;
    int speed;
    int value;
    int frequence;
    monsterfile >> atk;
    monsterfile >> hp;
    monsterfile >> scale;
    monsterfile >> speed;
    monsterfile >> value;
    monsterfile >> frequence;
    if(scale > 1)
    {
        monsterfile >> this->bullet;
    }
    this->setAttack(atk);
    this->setMaxHp(hp);
    this->setHp(hp); 
    this->setScale(scale);
    this->value = value;
    this->frequence = frequence;
    this->speed = speed;
}
