#pragma once
#include "Const.h"
#include "Point.h"
// ��ɫ
enum class Color { FOOD, SNAKE, HILIGHT, TEXT, BLOCK, HOLE, OBSTACLE ,HEAD};
// ʳ����
class Food
{
	Point _position;
public:
	// �������ʳ��
	void createFood();
	void setPosition(Point&);
	Point& getPosition();
};
