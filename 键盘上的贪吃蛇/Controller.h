#pragma once
#include "Const.h"
class Map;
class Data;
class Obstacle;
class Snake;
class Controller
{
	int _sleeptime;
	int _add;
	int _id;
public:
	Controller() :_add(1), _sleeptime(250), _id(0) {}
	//void game();
	void tiaochuangkou();
	void donghua();
	void denglu(Data&);
	void menu();
	//void playing();
	//void draw();
	//void draw(Map& map);
	//void draw(Data& data);
	//void draw(Snake& snake);
	//void draw(Obstacle& obstacle);
	//void jieshouanjian();
	//void pause();
	//void end();
};

