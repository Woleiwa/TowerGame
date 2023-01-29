#include "playerlist.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "md5.h"

PlayerList::PlayerList()
{

}

void string_to_md5(string md5, player_info& res)
{
    int head = 0;
    int rear = 0;
    rear = md5.find(' ', head);
    string num1(md5, head, rear - head);

    head = rear + 1;
    rear = md5.find(' ', head);
    string num2(md5, head, rear - head);

    head = rear + 1;
    rear = md5.find(' ', head);
    string num3(md5, head, rear - head);

    head = rear + 1;
    rear = md5.length();
    string num4(md5, head, rear - head);

    res.md5[0] = (unsigned)stoll(num1);
    res.md5[1] = (unsigned)stoll(num2);
    res.md5[2] = (unsigned)stoll(num3);
    res.md5[3] = (unsigned)stoll(num4);
}

string md5_to_string(player_info info)
{
    string num1 = to_string(info.md5[0]);
    string num2 = to_string(info.md5[1]);
    string num3 = to_string(info.md5[2]);
    string num4 = to_string(info.md5[3]);
    string res = num1 + ' ' + num2 + ' ' + num3 + ' ' + num4;
    return res;
}

player_info string_to_info(string st)
{
    int head = 0;
    int rear = 0;
    player_info res;
    rear = st.find(',', head);
    string username(st, head, rear - head);

    head = rear + 1;
    rear = st.find(',', head);
    string md5_code(st, head, rear - head);

    head = rear + 1;
    rear = st.length();
    string phonenum(st, head, rear - head);

    res.username = username;
    res.phonenum = phonenum;
    string_to_md5(md5_code,res);
    return res;
}

string info_to_string (player_info info)
{
    string res;
    string md5_code = md5_to_string(info);
    res = info.username + ',' + md5_code + ',' + info.phonenum;
    return res;
}

void PlayerList::readFromTxt()
{
    this->list.clear();
    ifstream userfile("E://code/test/player.txt");
    if (!userfile.is_open())
    {
        return;
    }
    char buffer[256];
    while(!userfile.eof())
    {
        userfile.getline(buffer, 255);
        if (strlen(buffer) <= 1)
        {
            break;
        }
        string info(buffer);
        player_info user_info = string_to_info(info);
        this->list.push_back(user_info);
    }
    userfile.close();
}

void PlayerList::writeToTxt()
{
    int size = this->list.size();
    ofstream userfile("E://code/test/player.txt");
    if (!userfile.is_open())
    {
        return;
    }
    for(int i = 0; i < size; i++)
    {
        string info = info_to_string(this->list[i]);
        userfile << info + '\n';
    }
    userfile.close();
}

bool PlayerList::isEmpty()
{
    return list.empty();
}

bool PlayerList::find(string username)
{
    int size = this->list.size();
    bool res = false;
    for(int i = 0; i < size; i++)
    {
        if(this->list[i].username == username)
        {
            res = true;
            break;
        }
    }
    return res;
}

player_info PlayerList::search_for_user(string username)
{
    int size = this->list.size();
    player_info res;
    for(int i = 0; i < size; i++)
    {
        if(this->list[i].username == username)
        {
            res = this->list[i];
            break;
        }
    }
    return res;
}

void PlayerList::regist(string username, string password, string phonenum)
{
    player_info new_player;
    new_player.username = username;
    new_player.phonenum = phonenum;
    unsigned int* md5 = MD5_2(password.c_str());
    for(int i = 0; i < 4; i++)
    {
        new_player.md5[i] = md5[i];
    }
    this->list.push_back(new_player);
}

void PlayerList::regist(player_info info)
{
    this->list.push_back(info);
}

void PlayerList::modifyPass(player_info info)
{
    int size = list.size();
    for(int i = 0; i < size; i++)
    {
        if(list[i].username == info.username)
        {
            list[i] = info;
            break;
        }
    }
}
