#pragma once
#include "Const.h"
#include "Point.h"
// 颜色
enum class Color { FOOD, SNAKE, HILIGHT, TEXT, BLOCK, HOLE, OBSTACLE ,HEAD};
// 食物类
class Food
{
	Point _position;
public:
	// 随机生成食物
	void createFood();
	void setPosition(Point&);
	Point& getPosition();
};
