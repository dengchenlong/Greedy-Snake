#include <iostream>
// ʱ�亯��time���������ͷ�ļ�
#include <time.h>
#include "Food.h"
using namespace std;
extern int map[HEIGHT][WIDTH];
void setLocation(int , int );
void setColor(Color);

// �������ʳ��
void Food::createFood()
{
	int x, y;
	// �������ʳ��
	srand((unsigned)time(NULL));
	do
	{
		_position(x = rand() % (WIDTH - 2) + 1, y = rand() % (HEIGHT - 2) + 1);
	} while (map[y][x] != 0);
	map[y][x] = 5;
	// ���ù��λ��
	setLocation(x, y);
	setColor(Color::FOOD);
	cout << "��";
}


void Food::setPosition(Point& position)
{
	_position=position;
}


Point& Food::getPosition()
{
	return _position;
}