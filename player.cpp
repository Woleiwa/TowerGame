#include "player.h"
#include "md5.h"
#include <fstream>
#include <qDebug>
Player::Player()
{

}

Player::Player(string username,string password, string phonenum)
{
    this->username = username;
    this->phonenum = phonenum;
    unsigned int* md5 = MD5_2(password.c_str());
    for(int i = 0; i < 4; i++)
    {
        this->md5[i] = md5[i];
    }
    this->getmy_info();
}

Player::Player(player_info info)
{
    this->username = info.username;
    this->phonenum = info.phonenum;
    for(int i = 0; i < 4; i++)
    {
        this->md5[i] = info.md5[i];
    }
}

player_info Player::get_info()
{
    player_info res;
    res.username = this->username;
    res.phonenum = this->phonenum;
    for(int i = 0; i < 4; i++)
    {
        res.md5[i] = this->md5[i];
    }
    return res;
}

void Player::regist()
{
    PlayerList plist;
    plist.readFromTxt();
    plist.regist(this->get_info());
    plist.writeToTxt();
}

bool Player::sigin(string username, string password)
{
    bool j1 =(username == this->username);
    bool j2 = true;
    unsigned int * md5 = MD5_2(password.c_str());
    for(int i = 0; i < 4; i++)
    {
        if(md5[i] != this->md5[i])
        {
            j2 = false;
            break;
        }
    }
    return j1 & j2;
}

void Player::modifyPass(string password)
{
    unsigned int* md5 = MD5_2(password.c_str());
    for(int i = 0; i < 4; i++)
    {
        this->md5[i] = md5[i];
    }
    PlayerList plist;
    plist.readFromTxt();
    plist.modifyPass(this->get_info());
    plist.writeToTxt();
}

vector<game_info> Player::getmy_info()
{
    vector<game_info> res;

    ifstream userfile("E://code/test/player/" + this->username + ".txt");
    if (!userfile.is_open())
    {
        return res;
    }
    while(!userfile.fail())
    {
        char buffer[256];
        userfile.getline(buffer, 255);
        if (strlen(buffer) <= 1)
        {
            break;
        }
        string info(buffer);
        qDebug() << QString::fromStdString(info);
        int split = info.find(" ");
        string level(info,0 , split);
        string score(info, split + 1, info.length() - split - 1);
        game_info g_info;
        g_info.level = stoi(level);
        g_info.score = stoi(score);
        glist.push_back(g_info);
    }
    res = this->glist;
    return res;
}

int Player::find_max_level()
{
    int max = 0;
    for(int i = 0; i < glist.size(); i++)
    {
        if(glist[i].level > max)
        {
            max = glist[i].level;
        }
    }
    return max;
}

void Player::insert_game_info(int level, int score)
{
    game_info ginfo;
    ginfo.level = level;
    ginfo.score = score;
    this->glist.push_back(ginfo);
    this->writeTotxt();
}

void Player::writeTotxt()
{
    ofstream userfile("E://code/test/player/" + this->username + ".txt");
    if (!userfile.is_open())
    {
        return;
    }
    for(int i = 0; i < this->glist.size(); i++)
    {
        string info = to_string(glist[i].level) + " " + to_string(glist[i].score);
        userfile << info << "\n";
    }
}
