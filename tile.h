#ifndef TILE_H
#define TILE_H

class Tile
{
    int x = 0,y = 0;
public:
    Tile(){};
    Tile(const Tile& another){this->x = another.x, this->y = another.y;}
    Tile(int x,int y) {this->x = x, this->y = y;};
    int get_x(){return this->x;};
    int get_y(){return this->y;};
    int get_distance(const Tile& another);
    bool operator== (const Tile& another);
    bool operator!= (const Tile& another) {return ! (*this == another);}
    void Move(int speed, char direction);
    bool insideScale(Tile another, int scale);
    Tile& operator= (const Tile& another);
};

#endif // TILE_H
