#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "playerlist.h"
using namespace std;
struct game_info
{
    int level;
    int score;
};

class Player
{
    string username;
    unsigned int md5[4];
    string phonenum;
    bool login = false;
    vector<game_info> glist;
public:
    Player();
    Player(string username,string password, string phonenum);
    Player(player_info info);
    player_info get_info();
    vector<game_info> getmy_info();
    int find_max_level();
    void regist();
    bool sigin(string username, string password);
    void modifyPass(string password);
    void insert_game_info(int level, int score);
    void writeTotxt();
};

#endif // PLAYER_H
