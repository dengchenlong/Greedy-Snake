#include "Point.h"


// ����==
bool Point::operator==(Point& point)
{
    if (point._y != _y || point._x != _x)
        return false;
    return true;
}


// ����+�����
Point& Point::operator+(Point& point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}
