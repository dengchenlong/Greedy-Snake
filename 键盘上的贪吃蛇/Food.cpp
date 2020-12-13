#include <iostream>
// 时间函数time包含在这个头文件
#include <time.h>
#include "Food.h"
using namespace std;
extern int map[HEIGHT][WIDTH];
void setLocation(int , int );
void setColor(Color);

// 随机生成食物
void Food::createFood()
{
	int x, y;
	// 随机生成食物
	srand((unsigned)time(NULL));
	do
	{
		_position(x = rand() % (WIDTH - 2) + 1, y = rand() % (HEIGHT - 2) + 1);
	} while (map[y][x] != 0);
	map[y][x] = 5;
	// 设置光标位置
	setLocation(x, y);
	setColor(Color::FOOD);
	cout << "■";
}


void Food::setPosition(Point& position)
{
	_position=position;
}


Point& Food::getPosition()
{
	return _position;
}