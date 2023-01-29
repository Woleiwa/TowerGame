#include "map.h"
#include <fstream>
using namespace std;

Map::Map(int level, QWidget* parent)
{
    this->level = level;
    this->parent = parent;
    this->readFromTxt();
}

Tile getTileFromString(string str_tile)
{
    int mid = str_tile.find(",");
    int end = str_tile.find(")");
    string str_x(str_tile, 1, mid - 1);
    string str_y(str_tile, mid + 1, end - mid - 1);
    qDebug() << QString::fromStdString(str_tile);
    int x = stoi(str_x);
    int y = stoi(str_y);
    Tile res(x, y);
    return res;
}

vector<Tile> getRouteFromString(string line)
{
    vector<Tile> route;
    int begin = line.find(" ") + 1;
    int end = line.find(" ", begin);
    while(end != - 1)
    {
        string index (line, begin, end - begin);
        begin = end + 1;
        end = line.find(" ", begin);
        Tile tile = getTileFromString(index);
        route.push_back(tile);
    }
    end = line.length();
    string index (line, begin, end - begin);
    Tile tile = getTileFromString(index);
    route.push_back(tile);
    return route;
}

void Map::readFromTxt()
{

    qDebug() << "Start reading file";
    string filename = "E://code/test/map/map";
    filename += to_string(this->level + 1);
    filename += ".txt";
    ifstream mapfile(filename);
    while(!mapfile.fail())
    {
        char buffer[1024];
        mapfile.getline(buffer,1023);
        string line(buffer);
        qDebug() << QString::fromStdString(line);
        string head (line,0,5);
        if(head == "route")
        {
            vector<Tile> new_route = getRouteFromString(line);
            this->route.push_back(new_route);
        }
        else if(head == "money")
        {
            string value(line , 6, line.length() - 6);
            this->money = stoi(value);
        }
        else if(head == "tigap")
        {
            string value(line , 6, line.length() - 6);
            this->gap = stoi(value);
        }
    }
}



