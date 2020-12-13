#include <iostream>
// ��������Ͱ��������ͷ�ļ�
#include <stdlib.h>
// ʱ�亯��time���������ͷ�ļ�
#include <time.h>
// HANDLE�ࣨ����ࣩ��COORD�ࣨ�����ࣩ���������ͷ�ļ�
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <Mmsystem.h>
#include "Player.h"
#include "Snake.h"
#include "Obstacle.h"
#include "Hole.h"
#include "Food.h"
#include "Function.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

// ȫ�ֱ�������
int add = 1;
// ˢ�¼���������ٶ�
int sleeptime = 250 / add;
// �������
Direction direction = Direction::UP;
// ��Ϸ�������
EndCondition endcondition = EndCondition::LIVE;
// ���id
int id;
// ʳ��
Food* food;
// ��
Snake* head;
// ����
int score = 0;
// ��ͼ���飬0Ϊ�գ�1Ϊǽ��2Ϊ�ߣ�x3Ϊ�ϰ���x4Ϊ�����ţ�5Ϊʳ��
int map[HEIGHT][WIDTH] = {};
// ���
Player player[10];
// �ϰ���
Obstacle* obstacle[10];
// �涴
Hole hole[10];
// ���߳̽����ı�־
volatile bool g_bEndMusicThread = false;
// �٢ڢۢܢݢޢߢ��
char symbol[10][3] = { "��","��","��","��" ,"��" ,"��" ,"��" ,"��" ,"��"};

// ȫ�ֺ�������
void inputPassword(char* str) 
{
	char c;
	int count = 0;
	while ((c = _getch()) != '\r') 
	{
		// �˸�
		if (c == 8)
		{ 
			if (count == 0) 
			{
				continue;
			}
			putchar('\b'); // ����һ��
			putchar(' '); // ���һ���ո�ԭ����*����
			putchar('\b'); // �ٻ���һ��ȴ�����
			count--;
		}
		// ��󳤶�Ϊ50
		if (count == 50)
		{ 
			continue;
		}
		// ����ֻ�ɰ������ֺ���ĸ
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
		{ 
			// ���յ�һ���ַ���, ��ӡһ��*
			putchar('*');
			str[count] = c;
			count++;
		}
	}
	str[count] = '\0';
}
// ������ɫ
void setColor(Color color)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (color)
	{
	case Color::SNAKE:
		SetConsoleTextAttribute(hOut, 10);
		break;
	case Color::FOOD:
		SetConsoleTextAttribute(hOut, 12);
		break;
	case Color::HILIGHT:
		SetConsoleTextAttribute(hOut, 224 | BACKGROUND_INTENSITY);
		break;
	case Color::TEXT:
		SetConsoleTextAttribute(hOut, 240);
		break;
	case Color::BLOCK:
		SetConsoleTextAttribute(hOut, 0);
		break;
	case Color::HOLE:
		SetConsoleTextAttribute(hOut, 223);
		break;
	case Color::OBSTACLE:
		SetConsoleTextAttribute(hOut, 85);
		break;
	case Color::HEAD:
		SetConsoleTextAttribute(hOut, 2);
		break;
	default:
		break;
	}
}
void setLocation(Point& position)
{
	// ���ù��λ�� SetConsoleCursorPosition����
	// ��һ������Ϊ����̨�ľ�� ���� GetStdHandle�����õ�  STD_OUTPUT_HANDLEΪ���
	// �ڶ�������Ϊ����ṹ��
	// �������������pos 
	COORD pos;
	// �������
	HANDLE hOutput;
	// �����Ա��ֵ 
	pos.X = position.getX() * 2;
	// �����Ա��ֵ 
	pos.Y = position.getY();
	// �õ����ھ�� 
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ù��λ��
	SetConsoleCursorPosition(hOutput, pos);
}
// ��λ���������������ù���λ��
void setLocation(int x, int y)
{
	// ���ù��λ�� SetConsoleCursorPosition����
	// ��һ������Ϊ����̨�ľ�� ���� GetStdHandle�����õ�  STD_OUTPUT_HANDLEΪ���
	// �ڶ�������Ϊ����ṹ��
	// �������������pos 
	COORD pos;
	// �������
	HANDLE hOutput;
	// �����Ա��ֵ 
	pos.X = x * 2;
	// �����Ա��ֵ 
	pos.Y = y;
	// �õ����ھ�� 
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ù��λ��
	SetConsoleCursorPosition(hOutput, pos);
}
// ����Χǽ
void createWall()
{
	// ѭ�����Ʊ��� 
	int i;
	// ��ӡ���±߿�
	setColor(Color::BLOCK);
	for (i = 0; i < HEIGHT; i += 1)
	{
		map[0][i] = 1;
		// ���ù��λ�� 
		setLocation(i, 0);
		printf("��");
		map[HEIGHT - 1][i] = 1;
		// ���ù��λ�� 
		setLocation(i, HEIGHT - 1);
		printf("��");
	}
	// ��ӡ���ұ߿�
	for (i = 1; i < WIDTH; i++)
	{
		map[i][0] = 1;
		// ���ù��λ�� 
		setLocation(0, i);
		printf("��");
		map[i][WIDTH - 1] = 1;
		// ���ù��λ�� 
		setLocation(WIDTH - 1, i);
		printf("��");
	}
}
// ��ͣ�����������¿ո񣬱�ʾҪ��ͣ��Ϸ
void pause()
{
	while (1)
	{
		// ��ʱ������1000��ʾ��ʱ1s
		Sleep(200);
		// �첽��ȡ���̰�����Ϊ�������ж��ǿո񰴼�
		if (GetAsyncKeyState(VK_SPACE))
		{
			// ���������SPACE���ͼ�����Ϸ 
			break;
		}
		// ���������ESC���ͽ�����Ϸ
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endcondition = EndCondition::END;
			end();
		}
	}
}
void log()
{
	PlaySound(TEXT("ready.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	// ��������̨���ڴ�С
	char strCmd[32];
	sprintf_s(strCmd, "mode con cols=%d lines=%d", WIDTH * 2 + 40, HEIGHT);
	system(strCmd);
	// ����������ɫ
	system("color f0");
	// ��ʼ������
	add = 1;
	sleeptime = 250 / add;
	direction = Direction::UP;
	endcondition = EndCondition::LIVE;
	food = new Food();
	score = 0;
	read(player);
	// ��ӭ����
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 - 2);
	printf("��ӭ����̰������Ϸ��");
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 + 2);
	system("pause");
	// �ֲ�����������ʱ����
	char* buf1 = new char[50];
	char* buf2 = new char[50];
	int temp, i;
	// ��¼
	system("cls");
	setLocation(WIDTH / 2 - 1, HEIGHT / 2 - 2);
	printf("�������˺ţ����û���˺ſ�ֱ�Ӵ�������");
	cin >> temp;
	// ����˺��Ƿ����
	i = 0;
	while (i < Player::num())
	{
		if (player[i].account() == temp)
		{
			break;
		}
		i++;
	}
	// ���û���˺ţ��򴴽��˺�
	if (i == Player::num())
	{
		while (1)
		{
			// ��������
			system("cls");
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
			cout << "���������룺";
			//cin >> buf1;
			inputPassword(buf1);
			// �ٴ���������
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 + 2);
			cout << "��ȷ�����룺";
			//cin >> buf2;
			inputPassword(buf2);
			// �ж����������Ƿ�һ��
			int j = 0;
			bool equal = true;
			while (buf1[j] || buf2[j])
			{
				if (buf1[j])
				{
					if (!buf2[j])
					{
						equal = false;
						break;
					}
					else if (buf1[j] != buf2[j])
					{
						equal = false;
						break;
					}
				}
				else if (buf2[j])
				{
					equal = false;
					break;
				}
				j++;
			}
			// ���һ�£���������˺�
			if (equal)
			{
				// �˺�����1
				Player::setNum(i + 1);
				id = i;
				// ����account
				player[i].setAccount(temp);
				// ��������
				player[i].setPassword(buf1);
				// �����ǳ�
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "�������ǳƣ�";
				cin >> buf1;
				player[i].setName(buf1);
				// ��ʼ����ʷ��¼
				player[i].setRecord(0);
				// ͬ���ļ�
				write(player);
				break;
			}
			// �����һ��,��������������
			else
			{
				setLocation(WIDTH / 2 + 3, HEIGHT / 2 + 4);
				cout << "�������벻һ�£�����������";
				setLocation(WIDTH / 2 + 5, HEIGHT / 2 + 6);
				system("pause");
			}
		}
	}
	// ����˺��Ѵ��ڣ�����֤����
	else
	{
		while (1)
		{
			// ��������
			system("cls");
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
			cout << "���������룺";
			//cin >> buf1;
			inputPassword(buf1);
			// ��֤����
			int j = 0;
			bool equal = true;
			while (buf1[j] || player[i].password()[j])
			{
				if (buf1[j])
				{
					if (!player[i].password()[j])
					{
						equal = false;
						break;
					}
					else if (buf1[j] != player[i].password()[j])
					{
						equal = false;
						break;
					}
				}
				else if (player[i].password()[j])
				{
					equal = false;
					break;
				}
				j++;
			}
			// ������ȷ����id
			if (equal)
			{
				id = i;
				break;
			}
			// ���������������������
			else
			{
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "�������";
				setLocation(WIDTH / 2 + 5, HEIGHT / 2 + 2);
				system("pause");
			}
		}
	}
	delete[]buf1;
	delete[]buf2;
}
// ������Ϸ
void playing()
{
	// �رչ����˸
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	// ��ȡ����̨�����Ϣ
	GetConsoleCursorInfo(handle, &CursorInfo);
	// ���ؿ���̨���
	CursorInfo.bVisible = false;
	// ���ÿ���̨���״̬
	SetConsoleCursorInfo(handle, &CursorInfo);
	// ����
	system("cls");
	// ����������ɫ
	system("color f0");
	// ����Χǽ
	createWall();
	// �����Ϣ���
	setLocation(WIDTH + 1, HEIGHT / 2 - 6);
	setColor(Color::TEXT);
	cout << "��ң�";
	setLocation(WIDTH + 1, HEIGHT / 2 - 4);
	setColor(Color::TEXT);
	cout << "�ҵ���߷֣�";
	setLocation(WIDTH + 1, HEIGHT / 2 - 3);
	setColor(Color::TEXT);
	cout << "��ʷ��߷֣�";
	setLocation(WIDTH + 1, HEIGHT / 2 - 2);
	setColor(Color::TEXT);
	cout << "�÷֣�";
	setLocation(WIDTH + 1, HEIGHT / 2);
	setColor(Color::TEXT);
	cout << "�ٶȣ�";
	setLocation(WIDTH + 1, HEIGHT / 2 + 1);
	setColor(Color::TEXT);
	cout << "�ϰ��������";
	setLocation(WIDTH + 1, HEIGHT / 2 + 2);
	setColor(Color::TEXT);
	cout << "ÿ��ʳ��÷֣�";
	// ��Ϸ˵��
	setLocation(WIDTH + 1, HEIGHT / 2 + 4);
	cout << "�������ҿ��Ʒ���";
	setLocation(WIDTH + 1, HEIGHT / 2 + 5);
	cout << "Ctrl���ٲ�����ʳ��÷�";
	setLocation(WIDTH + 1, HEIGHT / 2 + 6);
	cout << "Shift���ٲ�����ʳ��÷�";
	setLocation(WIDTH + 1, HEIGHT / 2 + 7);
	cout << "�ո���ͣ��ESC�˳�";
	// ��ʼ������
	Snake::createSnake();
	// �����ϰ���
	Obstacle::createObstacles();
	PlaySoundW(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// �����涴
	Hole::createHoles();
	// �������ʳ��
	food->createFood();
	// ��ʼ��Ϸ
	while (1)
	{
		setLocation(WIDTH + 4, HEIGHT / 2 - 6);
		setColor(Color::HILIGHT);
		cout << player[id].name();
		setLocation(WIDTH + 7, HEIGHT / 2 - 4);
		setColor(Color::HILIGHT);
		cout << player[id].record();
		setColor(Color::TEXT);
		cout << "�֡�";
		setLocation(WIDTH + 7, HEIGHT / 2 - 3);
		setColor(Color::HILIGHT);
		cout << Player::highest();
		setColor(Color::TEXT);
		cout << "�֡�";
		setLocation(WIDTH + 4, HEIGHT / 2 - 2);
		setColor(Color::HILIGHT);
		cout << score;
		setColor(Color::TEXT);
		cout << "�֡�";
		setLocation(WIDTH + 4, HEIGHT / 2);
		setColor(Color::HILIGHT);
		cout << 1000 / sleeptime;
		setColor(Color::TEXT);
		cout << "cps��";
		setLocation(WIDTH + 7, HEIGHT / 2 + 1);
		setColor(Color::HILIGHT);
		cout << Obstacle::num();
		setLocation(WIDTH + 8, HEIGHT / 2 + 2);
		setColor(Color::HILIGHT);
		cout << add;
		setColor(Color::TEXT);
		cout << "�֡�";
		// ���������SPACE����ͣ
		if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		// ���������ESC�ͽ������˳�ѭ��
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endcondition = EndCondition::END;
			end();
			break;
		}
		// ��
		else if (GetAsyncKeyState(VK_UP) && direction != Direction::DOWN)
		{
			direction = Direction::UP;
		}
		// ��
		else if (GetAsyncKeyState(VK_DOWN) && direction != Direction::UP)
		{
			direction = Direction::DOWN;
		}
		// ��
		else if (GetAsyncKeyState(VK_LEFT) && direction != Direction::RIGHT)
		{
			direction = Direction::LEFT;
		}
		// ��
		else if (GetAsyncKeyState(VK_RIGHT) && direction != Direction::LEFT)
		{
			direction = Direction::RIGHT;
		}
		// �ٶȿ���
			// ctrl����
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL))
		{
			if (add < 10)
			{
				add++;
				sleeptime = 250 / add;
			}
		}
		// shift����
		else if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
		{
			if (add > 1)
			{
				add--;
				sleeptime = 250 / add;
			}
		}
		// ���ƶ�,�������˳�ѭ��
		if (!head->move())
			break;
		Sleep(sleeptime);
	}
}
// ��Ϸ����
void end()
{
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 - 1);
	setColor(Color::TEXT);
	cout << "��Ϸ����\n";
	setLocation(WIDTH / 2 - 6, HEIGHT / 2);
	switch (endcondition)
	{
	case EndCondition::WALL:
		cout << "����ײǽ������\n";
		break;
	case EndCondition::BITE:
		cout << "������ɱ������\n";
		break;
	case EndCondition::END:
		cout << "�����˳���Ϸ��\n";
		break;
	case EndCondition::OBSTACLE:
		cout << "�����ϰ�������\n";
		break;
	}
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 + 1);
	cout << "�������յ÷��ǣ�";
	setColor(Color::HILIGHT);
	cout << score;
	setColor(Color::TEXT);
	cout << "��";
	// ˢ�������Ϣ
	write(player);
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 + 2);
	cout << "���¿�ʼ��Ϸ�밴�ո�����˳���Ϸ�밴ESC";
	while (1)
	{
		// ���������SPACE�����¿�ʼ��Ϸ
		if (GetAsyncKeyState(VK_SPACE))
		{
			// ����ۼ�
			for (int i = 1; i < HEIGHT - 1; i++)
			{
				for (int j = 1; j < WIDTH - 1; j++)
				{
					map[i][j] = 0;
				}
			}
			// ������Ϣ
			add = 1;
			sleeptime = 250 / add;
			direction = Direction::UP;
			endcondition = EndCondition::LIVE;
			score = 0;
			// ��ʼ��Ϸ
			playing();
		}
		// ���������ESC�ͽ���
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			exit(0);
		}
		Sleep(200);
	}
}
void write(Player* player)
{
	ofstream outfile;
	char* buf = new char[20];
	outfile.open("player.dat");
	outfile << "num\thighest\n" << Player::num() << '\t' << Player::highest() << endl
		<< "account\tname\tpassword\trecord" << endl;
	for (int i = 0; i < Player::num(); i++)
	{
		outfile << player[i].account() << '\t' << player[i].name() << '\t' << player[i].password() << '\t' << player[i].record() << endl;
	}
	outfile.close();
	delete[]buf;
}
void read(Player* player)
{
	// ���������Ϣ
	ifstream infile;
	int i, temp;
	char* buf = new char[20];
	infile.open("player.dat", ios::in);
	infile >> buf >> buf >> temp;
	Player::setNum(temp);
	infile >> temp;
	Player::setHighest(temp);
	infile >> buf >> buf >> buf >> buf;
	i = 0;
	while (i < Player::num())
	{
		infile >> temp;
		player[i].setAccount(temp);
		infile >> buf;
		player[i].setName(buf);
		infile >> buf;
		player[i].setPassword(buf);
		infile >> temp;
		player[i].setRecord(temp);
		i++;
	}
	infile.close();
	delete[]buf;
}
