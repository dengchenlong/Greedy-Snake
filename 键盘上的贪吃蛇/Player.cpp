#include <iostream>
#include "Player.h"
using namespace std;
int Player::_num = 0;
int Player::_highest = 0;
void Player::setName(char* name)
{
	int i = 0;
	while (name[i])
	{
		_name[i] = name[i];
		i++;
	}
	_name[i] = '\0';
}
void Player::setAccount(int account)
{
	_account = account;
}
void Player::setPassword(char* password)
{
	int i = 0;
	while (password[i])
	{
		_password[i] = password[i];
		i++;
	}
	_password[i] = '\0';
}
void Player::setRecord(int record)
{
	_record = record;
}
void Player::setNum(int num)
{
	_num = num;
}
char* Player::name()
{
	return _name;
}
int Player::account()
{
	return _account;
}
char* Player::password()
{
	return _password;
}
int Player::record()
{
	return _record;
}
int Player::num()
{
	return _num;
}
int Player::highest()
{
	return _highest;
}
void Player::setHighest(int highest)
{
	_highest = highest;
}
