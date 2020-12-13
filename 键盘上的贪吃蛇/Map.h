#pragma once
#include "Const.h"
#include <deque>
#include "Point.h"
using namespace std;
class Map
{
	int _kuan, _gao, _dakuan;
	deque<Point> _map;
public:
	Map();
	void initMap();
};

