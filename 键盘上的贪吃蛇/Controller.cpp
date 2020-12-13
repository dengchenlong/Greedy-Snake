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
	// ��������
	PlaySound(TEXT("ready.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	// ��������̨���ڴ�С
	char strCmd[32];
	sprintf_s(strCmd, "mode con cols=%d lines=%d", WIDTH * 2 + 40, HEIGHT);
	system(strCmd);

	// ����������ɫ
	system("color f0");

	// �رչ����˸
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}


void Controller::donghua()
{
	// ��ӭ����
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 - 2);
	printf("��ӭ����̰������Ϸ��");
	// ��������

	system("cls");
	setLocation(WIDTH / 2 + 4, HEIGHT / 2 + 2);
	system("pause");
}


void Controller::denglu(Data& data)
{
	// �ֲ�����������ʱ����
	char* buf1 = new char[50];
	char* buf2 = new char[50];
	int temp, i;
	vector<Player>* p = data.getPlayer();

	// ��¼
	system("cls");
	setLocation(WIDTH / 2 - 1, HEIGHT / 2 - 2);
	printf("�������˺ţ����û���˺ſ�ֱ�Ӵ�������");
	cin >> temp;
	// ����˺��Ƿ����
	i = 0;
	while (i < Player::num())
	{
		if ((*p)[i].account() == temp)
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
				_id = i;
				// ����account
				(*p)[i].setAccount(temp);
				// ��������
				(*p)[i].setPassword(buf1);
				// �����ǳ�
				system("cls");
				setLocation(WIDTH / 2 + 6, HEIGHT / 2 - 2);
				cout << "�������ǳƣ�";
				cin >> buf1;
				(*p)[i].setName(buf1);
				// ��ʼ����ʷ��¼
				(*p)[i].setRecord(0);
				// ͬ���ļ�
				data.write();
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
			// ������ȷ����id
			if (equal)
			{
				_id = i;
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

	system("cls");
}


void Controller::menu()
{

}
