#pragma once
#include "Const.h"
class Point
{
	int _x;
	int _y;
public:
	Point() :_x(0), _y(0) {};
	Point(int x, int y) :_x(x), _y(y) {};
	// 重载==
	bool operator==(Point& point);
	// 重载+运算符
	Point& operator+(Point& point);
	// 重载-运算符
	Point& operator-(Point& point)
	{
		_x -= point._x;
		_y -= point._y;
		return *this;
	}
	// 重载=运算符
	Point& operator=(Point& point)
	{
		_x = point._x;
		_y = point._y;
		return *this;
	}
	Point& operator()(int x, int y)
	{
		_x = x;
		_y = y;
		return *this;
	}
	int getX()
	{
		return _x;
	}
	int getY()
	{
		return _y;
	}
};

