#include "Controller.h"
#include "Data.h"
#include "Player.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>


void setLocation(int, int);
void inputPassword(char*);


//void Controller::game()
//{
//	auto_ptr<Data> data(new Data());
//	data->read();
//	tiaochuangkou();
//	donghua();
//	denglu(*data);
//	menu();
//	draw();
//	playing();
//}


void Controller::tiaochuangkou()
{
	// 播放音乐
	PlaySound(TEXT("ready.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	// 调整控制台窗口大小
	char strCmd[32];
	sprintf_s(strCmd, "mode con cols=%d lines=%d", WIDTH * 2 + 40, HEIGHT);
	system(strCmd);

	// 调整背景颜色
	system("color f0");

	// 关闭光标闪烁
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}


void Controller::donghua()
{
	// 欢迎界面
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 - 2);
	printf("欢迎来到贪吃蛇游戏！");
	// 动画内容

	system("cls");
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 + 2);
	system("pause");
}


void Controller::denglu(Data& data)
{
	// 局部变量用于临时保存
	char* buf1 = new char[50];
	char* buf2 = new char[50];
	int temp, i;
	vector<Player>* p = data.getPlayer();

	// 登录
	system("cls");
	setLocation(WIDTH / 2 - 1, HEIGHT / 2 - 2);
	printf("请输入账号（如果没有账号可直接创建）：");
	cin >> temp;
	// 检查账号是否存在
	i = 0;
	while (i < Player::num())
	{
		if ((*p)[i].account() == temp)
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
				_id = i;
				// 保存account
				(*p)[i].setAccount(temp);
				// 保存密码
				(*p)[i].setPassword(buf1);
				// 输入昵称
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "请输入昵称：";
				cin >> buf1;
				(*p)[i].setName(buf1);
				// 初始化历史纪录
				(*p)[i].setRecord(0);
				// 同步文件
				data.write();
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
			while (buf1[j] || (*p)[i].password()[j])
			{
				if (buf1[j])
				{
					if (!(*p)[i].password()[j])
					{
						equal = false;
						break;
					}
					else if (buf1[j] != (*p)[i].password()[j])
					{
						equal = false;
						break;
					}
				}
				else if ((*p)[i].password()[j])
				{
					equal = false;
					break;
				}
				j++;
			}
			// 密码正确则导入id
			if (equal)
			{
				_id = i;
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

	system("cls");
}


void Controller::menu()
{

}
