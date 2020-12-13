#include <iostream>
// 随机函数就包含在这个头文件
#include <stdlib.h>
// 时间函数time包含在这个头文件
#include <time.h>
// HANDLE类（句柄类）与COORD类（坐标类）包含在这个头文件
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

// 全局变量定义
int add = 1;
// 刷新间隔，控制速度
int sleeptime = 250 / add;
// 按键情况
Direction direction = Direction::UP;
// 游戏结束情况
EndCondition endcondition = EndCondition::LIVE;
// 玩家id
int id;
// 食物
Food* food;
// 蛇
Snake* head;
// 分数
int score = 0;
// 地图数组，0为空，1为墙，2为蛇，x3为障碍，x4为传送门，5为食物
int map[HEIGHT][WIDTH] = {};
// 玩家
Player player[10];
// 障碍物
Obstacle* obstacle[10];
// 虫洞
Hole hole[10];
// 让线程结束的标志
volatile bool g_bEndMusicThread = false;
// ①②③④⑤⑥⑦⑧⑨
char symbol[10][3] = { "①","②","③","④" ,"⑤" ,"⑥" ,"⑦" ,"⑧" ,"⑨"};

// 全局函数定义
void inputPassword(char* str) 
{
	char c;
	int count = 0;
	while ((c = _getch()) != '\r') 
	{
		// 退格
		if (c == 8)
		{ 
			if (count == 0) 
			{
				continue;
			}
			putchar('\b'); // 回退一格
			putchar(' '); // 输出一个空格将原来的*隐藏
			putchar('\b'); // 再回退一格等待输入
			count--;
		}
		// 最大长度为50
		if (count == 50)
		{ 
			continue;
		}
		// 密码只可包含数字和字母
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
		{ 
			// 接收到一个字符后, 打印一个*
			putchar('*');
			str[count] = c;
			count++;
		}
	}
	str[count] = '\0';
}
// 设置颜色
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
	// 设置光标位置 SetConsoleCursorPosition（）
	// 第一个参数为控制台的句柄 可由 GetStdHandle（）得到  STD_OUTPUT_HANDLE为输出
	// 第二个参数为坐标结构体
	// 创建坐标类对象pos 
	COORD pos;
	// 创建句柄
	HANDLE hOutput;
	// 对象成员赋值 
	pos.X = position.getX() * 2;
	// 对象成员赋值 
	pos.Y = position.getY();
	// 得到窗口句柄 
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置光标位置
	SetConsoleCursorPosition(hOutput, pos);
}
// 定位函数，作用是设置光标的位置
void setLocation(int x, int y)
{
	// 设置光标位置 SetConsoleCursorPosition（）
	// 第一个参数为控制台的句柄 可由 GetStdHandle（）得到  STD_OUTPUT_HANDLE为输出
	// 第二个参数为坐标结构体
	// 创建坐标类对象pos 
	COORD pos;
	// 创建句柄
	HANDLE hOutput;
	// 对象成员赋值 
	pos.X = x * 2;
	// 对象成员赋值 
	pos.Y = y;
	// 得到窗口句柄 
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置光标位置
	SetConsoleCursorPosition(hOutput, pos);
}
// 创建围墙
void createWall()
{
	// 循环控制变量 
	int i;
	// 打印上下边框
	setColor(Color::BLOCK);
	for (i = 0; i < HEIGHT; i += 1)
	{
		map[0][i] = 1;
		// 设置光标位置 
		setLocation(i, 0);
		printf("■");
		map[HEIGHT - 1][i] = 1;
		// 设置光标位置 
		setLocation(i, HEIGHT - 1);
		printf("■");
	}
	// 打印左右边框
	for (i = 1; i < WIDTH; i++)
	{
		map[i][0] = 1;
		// 设置光标位置 
		setLocation(0, i);
		printf("■");
		map[i][WIDTH - 1] = 1;
		// 设置光标位置 
		setLocation(WIDTH - 1, i);
		printf("■");
	}
}
// 暂停函数，当按下空格，表示要暂停游戏
void pause()
{
	while (1)
	{
		// 延时函数，1000表示延时1s
		Sleep(200);
		// 异步获取键盘按键行为，这里判断是空格按键
		if (GetAsyncKeyState(VK_SPACE))
		{
			// 如果按键是SPACE，就继续游戏 
			break;
		}
		// 如果按键是ESC，就结束游戏
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
	// 调整控制台窗口大小
	char strCmd[32];
	sprintf_s(strCmd, "mode con cols=%d lines=%d", WIDTH * 2 + 40, HEIGHT);
	system(strCmd);
	// 调整背景颜色
	system("color f0");
	// 初始化属性
	add = 1;
	sleeptime = 250 / add;
	direction = Direction::UP;
	endcondition = EndCondition::LIVE;
	food = new Food();
	score = 0;
	read(player);
	// 欢迎界面
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 - 2);
	printf("欢迎来到贪吃蛇游戏！");
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 + 2);
	system("pause");
	// 局部变量用于临时保存
	char* buf1 = new char[50];
	char* buf2 = new char[50];
	int temp, i;
	// 登录
	system("cls");
	setLocation(WIDTH / 2 - 1, HEIGHT / 2 - 2);
	printf("请输入账号（如果没有账号可直接创建）：");
	cin >> temp;
	// 检查账号是否存在
	i = 0;
	while (i < Player::num())
	{
		if (player[i].account() == temp)
		{
			break;
		}
		i++;
	}
	// 如果没有账号，则创建账号
	if (i == Player::num())
	{
		while (1)
		{
			// 设置密码
			system("cls");
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
			cout << "请设置密码：";
			//cin >> buf1;
			inputPassword(buf1);
			// 再次输入密码
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 + 2);
			cout << "请确认密码：";
			//cin >> buf2;
			inputPassword(buf2);
			// 判断两次输入是否一致
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
			// 如果一致，则添加新账号
			if (equal)
			{
				// 账号数加1
				Player::setNum(i + 1);
				id = i;
				// 保存account
				player[i].setAccount(temp);
				// 保存密码
				player[i].setPassword(buf1);
				// 输入昵称
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "请输入昵称：";
				cin >> buf1;
				player[i].setName(buf1);
				// 初始化历史纪录
				player[i].setRecord(0);
				// 同步文件
				write(player);
				break;
			}
			// 如果不一致,则重新设置密码
			else
			{
				setLocation(WIDTH / 2 + 3, HEIGHT / 2 + 4);
				cout << "两次输入不一致，请重设密码";
				setLocation(WIDTH / 2 + 5, HEIGHT / 2 + 6);
				system("pause");
			}
		}
	}
	// 如果账号已存在，则验证密码
	else
	{
		while (1)
		{
			// 输入密码
			system("cls");
			setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
			cout << "请输入密码：";
			//cin >> buf1;
			inputPassword(buf1);
			// 验证密码
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
			// 密码正确则导入id
			if (equal)
			{
				id = i;
				break;
			}
			// 密码错误则重新输入密码
			else
			{
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "密码错误！";
				setLocation(WIDTH / 2 + 5, HEIGHT / 2 + 2);
				system("pause");
			}
		}
	}
	delete[]buf1;
	delete[]buf2;
}
// 进行游戏
void playing()
{
	// 关闭光标闪烁
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	// 获取控制台光标信息
	GetConsoleCursorInfo(handle, &CursorInfo);
	// 隐藏控制台光标
	CursorInfo.bVisible = false;
	// 设置控制台光标状态
	SetConsoleCursorInfo(handle, &CursorInfo);
	// 清屏
	system("cls");
	// 调整背景颜色
	system("color f0");
	// 创建围墙
	createWall();
	// 输出信息面板
	setLocation(WIDTH + 1, HEIGHT / 2 - 6);
	setColor(Color::TEXT);
	cout << "玩家：";
	setLocation(WIDTH + 1, HEIGHT / 2 - 4);
	setColor(Color::TEXT);
	cout << "我的最高分：";
	setLocation(WIDTH + 1, HEIGHT / 2 - 3);
	setColor(Color::TEXT);
	cout << "历史最高分：";
	setLocation(WIDTH + 1, HEIGHT / 2 - 2);
	setColor(Color::TEXT);
	cout << "得分：";
	setLocation(WIDTH + 1, HEIGHT / 2);
	setColor(Color::TEXT);
	cout << "速度：";
	setLocation(WIDTH + 1, HEIGHT / 2 + 1);
	setColor(Color::TEXT);
	cout << "障碍物个数：";
	setLocation(WIDTH + 1, HEIGHT / 2 + 2);
	setColor(Color::TEXT);
	cout << "每个食物得分：";
	// 游戏说明
	setLocation(WIDTH + 1, HEIGHT / 2 + 4);
	cout << "上下左右控制方向";
	setLocation(WIDTH + 1, HEIGHT / 2 + 5);
	cout << "Ctrl加速并增加食物得分";
	setLocation(WIDTH + 1, HEIGHT / 2 + 6);
	cout << "Shift减速并降低食物得分";
	setLocation(WIDTH + 1, HEIGHT / 2 + 7);
	cout << "空格暂停，ESC退出";
	// 初始化蛇身
	Snake::createSnake();
	// 生成障碍物
	Obstacle::createObstacles();
	PlaySoundW(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// 创建虫洞
	Hole::createHoles();
	// 随机生成食物
	food->createFood();
	// 开始游戏
	while (1)
	{
		setLocation(WIDTH + 4, HEIGHT / 2 - 6);
		setColor(Color::HILIGHT);
		cout << player[id].name();
		setLocation(WIDTH + 7, HEIGHT / 2 - 4);
		setColor(Color::HILIGHT);
		cout << player[id].record();
		setColor(Color::TEXT);
		cout << "分　";
		setLocation(WIDTH + 7, HEIGHT / 2 - 3);
		setColor(Color::HILIGHT);
		cout << Player::highest();
		setColor(Color::TEXT);
		cout << "分　";
		setLocation(WIDTH + 4, HEIGHT / 2 - 2);
		setColor(Color::HILIGHT);
		cout << score;
		setColor(Color::TEXT);
		cout << "分　";
		setLocation(WIDTH + 4, HEIGHT / 2);
		setColor(Color::HILIGHT);
		cout << 1000 / sleeptime;
		setColor(Color::TEXT);
		cout << "cps　";
		setLocation(WIDTH + 7, HEIGHT / 2 + 1);
		setColor(Color::HILIGHT);
		cout << Obstacle::num();
		setLocation(WIDTH + 8, HEIGHT / 2 + 2);
		setColor(Color::HILIGHT);
		cout << add;
		setColor(Color::TEXT);
		cout << "分　";
		// 如果按键是SPACE就暂停
		if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		// 如果按键是ESC就结束并退出循环
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endcondition = EndCondition::END;
			end();
			break;
		}
		// 上
		else if (GetAsyncKeyState(VK_UP) && direction != Direction::DOWN)
		{
			direction = Direction::UP;
		}
		// 下
		else if (GetAsyncKeyState(VK_DOWN) && direction != Direction::UP)
		{
			direction = Direction::DOWN;
		}
		// 左
		else if (GetAsyncKeyState(VK_LEFT) && direction != Direction::RIGHT)
		{
			direction = Direction::LEFT;
		}
		// 右
		else if (GetAsyncKeyState(VK_RIGHT) && direction != Direction::LEFT)
		{
			direction = Direction::RIGHT;
		}
		// 速度控制
			// ctrl加速
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL))
		{
			if (add < 10)
			{
				add++;
				sleeptime = 250 / add;
			}
		}
		// shift减速
		else if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
		{
			if (add > 1)
			{
				add--;
				sleeptime = 250 / add;
			}
		}
		// 蛇移动,死亡则退出循环
		if (!head->move())
			break;
		Sleep(sleeptime);
	}
}
// 游戏结束
void end()
{
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 - 1);
	setColor(Color::TEXT);
	cout << "游戏结束\n";
	setLocation(WIDTH / 2 - 6, HEIGHT / 2);
	switch (endcondition)
	{
	case EndCondition::WALL:
		cout << "您因撞墙而死！\n";
		break;
	case EndCondition::BITE:
		cout << "您因自杀而死！\n";
		break;
	case EndCondition::END:
		cout << "您已退出游戏！\n";
		break;
	case EndCondition::OBSTACLE:
		cout << "您因障碍而死！\n";
		break;
	}
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 + 1);
	cout << "您的最终得分是：";
	setColor(Color::HILIGHT);
	cout << score;
	setColor(Color::TEXT);
	cout << "分";
	// 刷新玩家信息
	write(player);
	setLocation(WIDTH / 2 - 6, HEIGHT / 2 + 2);
	cout << "重新开始游戏请按空格键，退出游戏请按ESC";
	while (1)
	{
		// 如果按键是SPACE就重新开始游戏
		if (GetAsyncKeyState(VK_SPACE))
		{
			// 清楚痕迹
			for (int i = 1; i < HEIGHT - 1; i++)
			{
				for (int j = 1; j < WIDTH - 1; j++)
				{
					map[i][j] = 0;
				}
			}
			// 重置信息
			add = 1;
			sleeptime = 250 / add;
			direction = Direction::UP;
			endcondition = EndCondition::LIVE;
			score = 0;
			// 开始游戏
			playing();
		}
		// 如果按键是ESC就结束
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
	// 加载玩家信息
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
