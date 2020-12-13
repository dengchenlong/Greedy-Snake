#pragma once
#include "Const.h"
// ÕÊº“¿‡
class Player
{
	char _name[20];
	int _account;
	char _password[50];
	int _record;
	static int _num;
	static int _highest;
public:
	void setName(char* name);
	void setAccount(int account);
	void setPassword(char* password);
	void setRecord(int record);
	static void setNum(int num);
	char* name();
	int account();
	char* password();
	int record();
	static int num();
	static int highest();
	static void setHighest(int highest);
};
