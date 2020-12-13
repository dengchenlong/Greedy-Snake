#pragma once
#include "Const.h"
class Point
{
	int _x;
	int _y;
public:
	Point() :_x(0), _y(0) {};
	Point(int x, int y) :_x(x), _y(y) {};
	// ����==
	bool operator==(Point& point);
	// ����+�����
	Point& operator+(Point& point);
	// ����-�����
	Point& operator-(Point& point)
	{
		_x -= point._x;
		_y -= point._y;
		return *this;
	}
	// ����=�����
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

