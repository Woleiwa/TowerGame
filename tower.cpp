#include "tower.h"
#include <fstream>

Tower::Tower(int attack, int hp, int scale,Tile position, int frequence, int attack_up, int hp_up, int scale_up,int price , int price_for_level_up, string name)
{
    this->setAttack(attack);
    this->setMaxHp(hp);
    this->setHp(hp);  
    this->setScale(scale);
    this->setPosition(position);
    this->frequence = frequence;
    this->attack_up = attack_up;
    this->hp_up = hp_up;
    this->scale_up = scale_up;
    this->price = price;
    this->price_for_level_up = price_for_level_up;
    this->name = name;
}

Tower::Tower(string name)
{
    this->name = name;
    this->readFromTxt();
}

void Tower::level_up()
{
    int new_attack = this->getAttack() + this->attack_up;
    this->setAttack(new_attack);
    int new_hp = this->getMaxHp() + this->hp_up;
    this->setMaxHp(new_hp);
    this->setHp(new_hp);
    int new_scale = this->getScale() + this->scale_up;
    this->setScale(new_scale);
    this->level += 1;
    this->attack_up += this->attack_up/2;
    this->hp_up += this->hp_up/2;
    this->price_for_level_up += this->price/2;
    if(this->level == 3)
    {
        this->insertBuff(this->buff_level_up);
    }
}

void Tower::beAttacked(Attackable& enemy)
{
    if(this->isDead())
    {
        return;
    }
    int new_hp = this->getHp() - enemy.getAttack();
    if(new_hp > 0)
    {
        this->setHp(new_hp);
    }
    else
    {
        this->setHp(0);
    }
}

void Tower::attackEnenmy(Attackable& enemy)
{
    if(enemy.isDead() ||!this->insideScale(enemy))
    {
        return;
    }
    else
    {
        enemy.beAttacked(*this);
    }
}

void Tower::readFromTxt()
{
    string filename = "E://code/test/tower/setting/" + this->name + ".txt";
    ifstream file(filename);
    int attack,hp,scale, frequence,attack_up,hp_up,scale_up,price,price_for_level_up;
    file >> attack;
    file >> hp;
    file >> scale;
    file >> frequence;
    file >> attack_up;
    file >> hp_up;
    file >> scale_up;
    file >> price;
    file >> price_for_level_up;
    if(scale > 1)
    {
        file >> this->bullet;
    }
    file >> this->buffname;
    this->buff_level_up = new buff(this->buffname);
    this->setAttack(attack);
    this->setMaxHp(hp);
    this->setHp(hp);
    this->setScale(scale);
    this->frequence = frequence;
    this->attack_up = attack_up;
    this->hp_up = hp_up;
    this->scale_up = scale_up;
    this->price = price;
    this->price_for_level_up = price_for_level_up;
}

