#pragma once
#include "Const.h"
#include "Point.h"
// �������
enum class Direction { UP, DOWN, LEFT, RIGHT };
// ���������
enum class EndCondition { WALL, BITE, END, OBSTACLE, LIVE };

// ���࣬�������ߵĻ���Ԫ�غ��ߵ����л�����������������ɵ�
class Snake
{
	Point _position;
	Point _offset;
	// ʹ��������ɣ����������򣬴�ź�x��y���ꡣһ��ָ���򣬴�����Ӻ�������ڵ�ĵ�ַ
	Snake* _next;
public:
	Snake() :_position(), _next(NULL), _offset() {}
	Point& getPosition();
	Snake* getNext();
	// ���ƶ�
	bool move();
	void setPosition(int x, int y)
	{
		_position = (Point&)Point(x, y);
	}
	void setNext(Snake* snake);
	// �߳�ʳ��
	void eatFood();
	// ������
	static void createSnake();
};
