#pragma once
#include "Const.h"
#include "Point.h"
// 方向控制
enum class Direction { UP, DOWN, LEFT, RIGHT };
// 结束的情况
enum class EndCondition { WALL, BITE, END, OBSTACLE, LIVE };

// 蛇类，包含了蛇的基本元素和蛇的所有活动，其中蛇是由链表构成的
class Snake
{
	Point _position;
	Point _offset;
	// 使用链表完成，两个数据域，存放横x纵y坐标。一个指针域，存放链接后续身体节点的地址
	Snake* _next;
public:
	Snake() :_position(), _next(NULL), _offset() {}
	Point& getPosition();
	Snake* getNext();
	// 蛇移动
	bool move();
	void setPosition(int x, int y)
	{
		_position = (Point&)Point(x, y);
	}
	void setNext(Snake* snake);
	// 蛇吃食物
	void eatFood();
	// 创建蛇
	static void createSnake();
};
