#pragma once
#include "Const.h"
#include <vector>
using namespace std;
class Player;
class Data
{
	vector<Player> _player;
public:
	Data();
	void read();
	void write();
	vector<Player>* getPlayer()
	{
		return &_player;
	}
};

