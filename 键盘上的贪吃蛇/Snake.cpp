#include <iostream>
#include <windows.h>
#include <Mmsystem.h>
#include "Food.h"
#include "Hole.h"
#include "Player.h"
#include "Snake.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

extern int map[HEIGHT][WIDTH];
extern int score;
extern Food* food;
extern Snake* head;
extern Player player[10];
extern Hole hole[10];
extern char symbol[10][3];
extern int add;
extern int id;
extern Direction direction;
extern EndCondition endcondition;
Point u(0, -1);
Point d(0, 1);
Point l(-1, 0);
Point r(1, 0);
void end();
void setLocation(int, int);
void setColor(Color);


Point& Snake::getPosition()
{
	return _position;
}


Snake* Snake::getNext()
{
	return _next;
}


// 蛇移动
bool Snake::move()
{
	Snake* q = head;
	switch (direction)
	{
	case Direction::UP:
		head = new Snake();
		head->_position = q->_position + _offset + u;
		head->_next = q;
		break;
	case Direction::DOWN:
		head = new Snake();
		head->_position = q->_position + _offset + d;
		head->_next = q;
		break;
	case Direction::LEFT:
		head = new Snake();
		head->_position = q->_position + _offset + l;
		head->_next = q;
		break;
	case Direction::RIGHT:
		head = new Snake();
		head->_position = q->_position + _offset + r;
		head->_next = q;
		break;
	}
	// 刷新蛇的尾部map
	while (q->getNext()->getNext())
		q = q->getNext();
	map[q->getNext()->getPosition().getY()][q->getNext()->getPosition().getY()] = 0;
	// 判断蛇的状态
	switch (map[head->getPosition().getY()][head->getPosition().getX()] % 10)
	{
	case 0:// 正常
		setLocation(q->getNext()->getPosition().getX(), q->getNext()->getPosition().getY());
		setColor(Color::TEXT);
		cout << "　";
		delete q->getNext();
		q->setNext(NULL);
		break;
	case 1:// 撞墙
		endcondition = EndCondition::WALL;
		PlaySound(TEXT("die.wav"), NULL, SND_FILENAME | SND_ASYNC);
		end();
		return false;
	case 2:// 咬到自己
		endcondition = EndCondition::BITE;
		PlaySound(TEXT("die.wav"), NULL, SND_FILENAME | SND_ASYNC);
		end();
		return false;
	case 3:// 障碍
		endcondition = EndCondition::OBSTACLE;
		PlaySound(TEXT("die.wav"), NULL, SND_FILENAME | SND_ASYNC);
		end();
		return false;
	case 4:// 传送门
		switch (map[head->getPosition().getY()][head->getPosition().getX()] % 100 / 10)
		{
		case 0:
			_offset= hole[map[head->getPosition().getY()][head->getPosition().getX()] / 100].getPoint(1) - hole[map[head->getPosition().getY()][head->getPosition().getX()] / 100].getPoint(0);
			head->_position= head->_position + _offset;
			break;
		case 1:
			_offset = hole[map[head->getPosition().getY()][head->getPosition().getX()] / 100].getPoint(0) - hole[map[head->getPosition().getY()][head->getPosition().getX()] / 100].getPoint(1);
			head->_position = head->_position + _offset;
			break;
		}
		break;
	case 5:// 吃到食物
		map[q->getNext()->getPosition().getY()][q->getNext()->getPosition().getX()] = 2;
		eatFood();
		break;
	}
	// 刷新虫洞
	int i = 0;
	while (i < Hole::num())
	{
		if (map[hole[i].getPoint(0).getY()][hole[i].getPoint(0).getX()] == 0)
		{
			map[hole[i].getPoint(0).getY()][hole[i].getPoint(0).getX()] = i * 100 + 0 * 10 + 4;
			setLocation(hole[i].getPoint(0).getX(), hole[i].getPoint(0).getY());
			setColor(Color::HOLE);
			cout << symbol[i];
		}
		if (map[hole[i].getPoint(1).getY()][hole[i].getPoint(1).getX()] == 0)
		{
			map[hole[i].getPoint(1).getY()][hole[i].getPoint(1).getX()] = i * 100 + 1 * 10 + 4;
			setLocation(hole[i].getPoint(1).getX(), hole[i].getPoint(1).getY());
			setColor(Color::HOLE);
			cout << symbol[i];
		}
		i++;
	}
	// 如果蛇存活,刷新画面
	map[head->getPosition().getY()][head->getPosition().getX()] = 2;
	setLocation(head->getPosition().getX(), head->getPosition().getY());
	setColor(Color::HEAD);
	cout << "■";
	setLocation(head->_next->getPosition().getX(), head->_next->getPosition().getY());
	setColor(Color::SNAKE);
	cout << "■";
	return true;
}


void Snake::setNext(Snake* snake)
{
	_next = snake;
}


// 蛇吃食物
void Snake::eatFood()
{
	PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
	food->createFood();
	score += add;
	if (score > Player::highest())
	{
		PlaySound(TEXT("highest.wav"), NULL, SND_FILENAME | SND_ASYNC);
		player[id].setRecord(score);
		Player::setHighest(score);
	}
	else if (score > player[id].record())
	{
		PlaySound(TEXT("record.wav"), NULL, SND_FILENAME | SND_ASYNC);
		player[id].setRecord(score);
	}
}


// 创建蛇
void Snake::createSnake()
{
	head = new Snake();
	head->setPosition(2, HEIGHT / 2);
	map[HEIGHT / 2][2] = 2;
	setLocation(head->getPosition().getX(), head->getPosition().getY());
	setColor(Color::HEAD);
	cout << "■";
	Snake* q = head;
	for (int i = 0; i < 3; i++)
	{
		q->setNext(new Snake());
		q->getNext()->setPosition(q->getPosition().getX(), q->getPosition().getY() + 1);
		q = q->getNext();
		map[q->getPosition().getY()][q->getPosition().getX()] = 2;
		setLocation(q->getPosition().getX(), q->getPosition().getY());
		setColor(Color::SNAKE);
		cout << "■";
	}
}
