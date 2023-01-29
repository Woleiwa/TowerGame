#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include<string>
#include<vector>
using namespace std;
struct player_info
{
    string username;
    string phonenum;
    unsigned int md5[4];
};

class PlayerList
{
    vector<player_info> list;
public:
    PlayerList();
    void readFromTxt();
    void writeToTxt();
    bool isEmpty();
    player_info search_for_user(string username);
    bool find(string username);
    void regist(string username, string password, string phonenum);
    void regist(player_info info);
    void modifyPass(player_info info);
};

#endif // PLAYERLIST_H
