#include <iostream>
// ʱ�亯��time���������ͷ�ļ�
#include <time.h>
#include "Food.h"
#include "Obstacle.h"
using namespace std;

extern int map[HEIGHT][WIDTH];
extern Obstacle* obstacle[10];
void setLocation(int, int);
void setColor(Color);

int Obstacle::_num = 0;

int Obstacle::num()
{
	return _num;
}


// ����_next
Obstacle* Obstacle::getNext()
{
	return _next;
}


// ����_next
void Obstacle::setNext(Obstacle* next)
{
	_next = next;
}


// �����ϰ���
void Obstacle::createObstacle(int id)
{
	int len;
	Obstacle* p = obstacle[id];
	// ������ɳ���
	srand((unsigned)time(NULL));
	len = rand() % 5 + 5;
	// ������ɵ�һ������
	do {
		p->setPosition((Point&)Point(rand() % (WIDTH - 5) + 2, rand() % (HEIGHT - 5) + 2));
		// �ж��Ƿ���Ϲ���,��������������������
	} while (!isValid(id));
	// ˢ�´��ں�map
	map[_position.getY()][_position.getX()] = id * 10 + 3;
	setLocation(p->_position.getX(), p->_position.getY());
	setColor(Color::OBSTACLE);
	cout << "��";
	// ѭ����������
	for(int i=1;i<len;i++)
	{
		int times = 0;
		// ���������һ����
		p->_next = new Obstacle();
		do {
			p->setPosition(p->_position.getX() + rand() % 3 - 1, p->_position.getY() + rand() % 2);
			times++;
		} while ((!p->_next->isValid(id)) && times < 5);
		// �ж��Ƿ�Ϸ�.���Ϸ���������������
		// ���������Դ���,��ֹͣѭ��
		if (times == 5)
		{
			p->_next = NULL;
			break;
		}
		// ˢ�´��ں�map
		p = p->_next;
		map[p->_position.getY()][p->_position.getX()] = id * 10 + 3;
		setLocation(p->_position.getX(), p->_position.getY());
		setColor(Color::OBSTACLE);
		cout << "��";
	}
}


void Obstacle::createObstacles()
{
	// ��������ϰ�������
	srand((unsigned)time(NULL));
	_num = rand() % 6 + 5;
	// ���������ϰ���
	for (int i = 0; i < 3; i++)
	{
		obstacle[i] = new Obstacle();
	}
	obstacle[0]->createLogo();
	// ��������ϰ���
	for (int i = 3; i < _num; i++)
	{
		obstacle[i] = new Obstacle();
		obstacle[i]->createObstacle(i);
	}
}


bool Obstacle::isValid(int id)
{
	// �������Ϊ��
	if (map[_position.getY()][_position.getX()] != 0)
		return false;
	// ��Χû��ǽ�ڻ�����
	else if (map[_position.getY() + 1][_position.getX()] == 1 || map[_position.getY()][_position.getX() + 1] == 1 || map[_position.getY() + 1][_position.getX() + 1] == 1 || map[_position.getY() - 1][_position.getX()] == 1 || map[_position.getY()][_position.getX() - 1] == 1 || map[_position.getY() - 1][_position.getX() - 1] == 1 || map[_position.getY() - 1][_position.getX() + 1] == 1 || map[_position.getY() + 1][_position.getX() - 1] == 1
		|| map[_position.getY() + 1][_position.getX()] == 2 || map[_position.getY()][_position.getX() + 1] == 2 || map[_position.getY() + 1][_position.getX() + 1] == 2 || map[_position.getY() - 1][_position.getX()] == 2 || map[_position.getY()][_position.getX() - 1] == 2 || map[_position.getY() - 1][_position.getX() - 1] == 2 || map[_position.getY() - 1][_position.getX() + 1] == 2 || map[_position.getY() + 1][_position.getX() - 1] == 2)
		return false;
	// ��Χû�������ϰ���
	else if ((map[_position.getY() + 1][_position.getX()] % 10 == 3 && map[_position.getY() + 1][_position.getX()] / 10 != id) || (map[_position.getY()][_position.getX() + 1] % 10 == 3 && map[_position.getY()][_position.getX() + 1] / 10 != id) || (map[_position.getY() + 1][_position.getX() + 1] % 10 == 3 && map[_position.getY() + 1][_position.getX() + 1] / 10 != id) || (map[_position.getY() - 1][_position.getX()] % 10 == 3 && map[_position.getY() - 1][_position.getX()] / 10 != id) || (map[_position.getY()][_position.getX() - 1] % 10 == 3 && map[_position.getY()][_position.getX() - 1] / 10 != id) || (map[_position.getY() - 1][_position.getX() - 1] % 10 == 3 && map[_position.getY() - 1][_position.getX() - 1] / 10 != id) || (map[_position.getY() - 1][_position.getX() + 1] % 10 == 3 && map[_position.getY() - 1][_position.getX() + 1] / 10 != id) || (map[_position.getY() + 1][_position.getX() - 1] % 10 == 3 && map[_position.getY() + 1][_position.getX() - 1] / 10 != id))
		return false;
	return true;
}


// ���������ϰ���
void Obstacle::createLogo()
{
	Obstacle* o;
	o = obstacle[0];
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (D[i][j])
			{
				if (o != obstacle[0])
				{
					o->_next = new Obstacle();
					o = o->_next;
				}
				o->setPosition(j + 7, i + 15);
				map[i + 15][j + 7] = 3;
				setLocation(j + 7, i + 15);
				setColor(Color::OBSTACLE);
				cout << "��";
			}
		}
	}
	o = obstacle[1];
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (C[i][j])
			{
				if (o != obstacle[0])
				{
					o->_next = new Obstacle();
					o = o->_next;
				}
				o->setPosition(j + 7, i + 15);
				map[i + 15][j + 17] = 13;
				setLocation(j + 17, i + 15);
				setColor(Color::OBSTACLE);
				cout << "��";
			}
		}
	}
	o = obstacle[2];
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (L[i][j])
			{
				if (o != obstacle[0])
				{
					o->_next = new Obstacle();
					o = o->_next;
				}
				o->setPosition(j + 7, i + 15);
				map[i + 15][j + 27] = 23;
				setLocation(j + 27, i + 15);
				setColor(Color::OBSTACLE);
				cout << "��";
			}
		}
	}
}
