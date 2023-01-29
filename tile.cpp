#include "tile.h"

bool Tile::insideScale(Tile another, int scale)
{
    int dispow = (this->x - another.x) * (this->x - another.x) + (this->y - another.y) * (this->y - another.y);
    if(dispow > scale * scale)
    {
        return false;
    }
    return true;
}

Tile& Tile::operator= (const Tile& another)
{
    this->x = another.x;
    this->y = another.y;
    return *this;
}

bool Tile::operator==(const Tile& another)
{
    return ((this->x == another.x) & (this->y == another.y));
}

int Tile::get_distance(const Tile& another)
{
    int dx = this->x - another.x;
    int dy = this->y - another.y;
    return (dx * dx + dy * dy);
}
