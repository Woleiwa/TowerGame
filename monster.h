#ifndef MONSTER_H
#define MONSTER_H
#include "attackable.h"
#include <string>
using namespace std;
class Monster:public Attackable
{
    int speed;
    string name;
    string direction;
    int value;
    int frequence;
    int rank;
    string bullet = "";
public:
    Monster(int attack, int hp, int scale,Tile position, int speed, string direction, string name, int value, int frequence);
    Monster(string name,Tile position);
    void readFromTxt();
    int getSpeed();
    int getRank() {return this->rank;};
    void setRank(int i) {this->rank = i;};
    int getValue(){return this->value;};
    int getFrequence() {return this->frequence;};
    string getDirection() {return this->direction;};
    string getType() {return this->bullet;};
    string getName() {return this->name;};
    bool runned = false;
    void changeDirection(string direction) {this->direction = direction;};
    void beAttacked(Attackable& enemy) {this->Attackable::beAttacked(enemy);};
    void attackEnenmy(Attackable& enemy) {this->Attackable::attackEnenmy(enemy);};
};

#endif // MONSTER_H
