#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Obstacle.h"
#include "Food.h"
#include "Hole.h"
using namespace std;

extern Hole hole[10];
extern Obstacle* obstacle[10];
extern int map[HEIGHT][WIDTH];
extern char symbol[10][3];

void setLocation(int, int);
void setColor(Color);

int Hole::_num = 0;

// ���ɳ涴
void Hole::createHoles()
{
	// ������ɳ涴����
	srand((unsigned)time(NULL));
	_num = rand() % 3 + 1;
	//_num = 3;
	// ����ָ���涴
	Sleep(1000);
	hole[0].createNecessity();
	// ��������涴
	for (int i = 1; i < _num; i++)
	{
		Sleep(1000);
		hole[i].createHole(i);
	}
	Sleep(1000);
}


void Hole::createHole(int id)
{
	int cycle, j;
	srand((unsigned)time(NULL));
	Obstacle* o;
	// ��һ������
	do {
		// ��������ϰ���
		o = obstacle[rand() % (Obstacle::num() - 3) + 3];
		// ���ѭ������
		cycle = rand() % 9;
		for (j = 0; j < cycle; j++)
		{
			// ��������ϰ���,����ǰ�˳�ѭ��
			if (o->getNext() == NULL)
			{
				break;
			}
			o = o->getNext();
		}
		hole[id]._point[0] = o->getPosition();
		// ����Ѿ�Ϊ�涴,�����¶�λ
	} while (map[hole[id]._point[0].getY()][hole[id]._point[0].getX() % 10] == 4);
	// ˢ��map���Ӵ�
	map[hole[id]._point[0].getY()][hole[id]._point[0].getX()] = id * 100 + 0 * 10 + 4;
	setLocation(hole[id]._point[0].getX(), hole[id]._point[0].getY());
	setColor(Color::HOLE);
	cout << symbol[id];
	// �ڶ�������
	do {
		// ��������ϰ���
		o = obstacle[rand() % (Obstacle::num() - 3) + 3];
		// ���ѭ������
		cycle = rand() % 9;
		for (j = 0; j < cycle; j++)
		{
			// ��������ϰ���,����ǰ�˳�ѭ��
			if (o->getNext() == NULL)
			{
				break;
			}
			o = o->getNext();
		}
		hole[id]._point[1] = o->getPosition();
		// ����Ѿ�Ϊ�涴,�����¶�λ
	} while (map[hole[id]._point[1].getY()][hole[id]._point[1].getX() % 10] == 4);
	// ˢ��map���Ӵ�
	map[hole[id]._point[1].getY()][hole[id]._point[1].getX()] = id * 100 + 1 * 10 + 4;
	setLocation(hole[id]._point[1].getX(), hole[id]._point[1].getY());
	setColor(Color::HOLE);
	cout << symbol[id];
}


Point& Hole::getPoint(int i)
{
	return _point[i];
}

// ��������涴
void Hole::createNecessity()
{
	// ��һ������
	hole[0].getPoint(0)(8, 20);
	map[hole[0].getPoint(0).getY()][hole[0].getPoint(0).getX()] = 0 * 100 + 0 * 10 + 4;
	setLocation(hole[0].getPoint(0).getY(), hole[0].getPoint(0).getX());
	setColor(Color::HOLE);
	cout << symbol[0];
	// �ڶ�������
	hole[0]._point[1](28, 20);
	map[hole[0]._point[1].getY()][hole[0]._point[1].getX()] = 0 * 100 + 1 * 10 + 4;
	setLocation(hole[0]._point[1].getX(), hole[0]._point[1].getY());
	setColor(Color::HOLE);
	cout << symbol[0];
}


int Hole::num()
{
	return _num;
}
