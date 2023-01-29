#ifndef BUFF_H
#define BUFF_H
#include <string>
#include <QTimer>
using namespace std;

class buff
{
    string buff_name;
    bool temporary;
    int last_time;
    bool atk_or_not;
    string attach_buff;
    QTimer* timer =nullptr;
public:
    buff(string buff_name);
    void readFromTxt();
    string getName() {return buff_name;};
    bool getTemporary() {return temporary;};
    int getLastTime() {return last_time;};
    string getAttachBuff() {return this->attach_buff;};
    QTimer* getTimer() {return this->timer;};
    bool getAtkFlag() {return this->atk_or_not;};
    void setTimer(QTimer* timer) {this->timer = timer;};
    bool operator== (buff& another){return this->buff_name == another.buff_name;};
    void updateBuff(int i);
    bool isEnd(){return this->last_time == 0;};
};

#endif // BUFF_H
