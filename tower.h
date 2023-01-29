#ifndef TOWER_H
#define TOWER_H
#include "attackable.h"
#include <string>
#include <buff.h>
using namespace  std;
class Tower:public Attackable
{
    int level = 1;
    int frequence;
    int attack_up;
    int hp_up;
    int scale_up;
    int price;
    int price_for_level_up;
    string name;
    int rank;
    string bullet = "";
    string buffname = "";
    buff* buff_level_up;
public:
    Tower();
    Tower(int attack, int hp, int scale,Tile position, int frequence, int attack_up, int hp_up, int scale_up, int price, int price_for_level_up, string name);
    Tower(string name);
    void setRank(int rank) {this->rank = rank;};
    int getRank() {return this->rank;};
    int getPrice(){return price;};
    int getPriceForLevelUp() {return price_for_level_up;};
    int getFrequence(){return this->frequence;};
    int getAttack_Up() {return this->attack_up;};
    int getHp_Up() {return this->hp_up;};
    int getScale_Up() {return this->scale_up;};
    string getType() {return this->bullet;};
    string getName() {return this->name;};
    int getLevel() {return this->level;};
    void level_up();
    void beAttacked(Attackable& enemy);
    void attackEnenmy(Attackable& enemy);
    void readFromTxt();
    buff* getBuff() {return this->buff_level_up;};
};

#endif // TOWER_H
