#include "Data.h"
#include "Player.h"
#include <fstream>
Data::Data() :_player() {}


void Data::read()
{
	// 加载玩家信息
	auto_ptr<Player> p(new Player());
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
		p->setAccount(temp);
		infile >> buf;
		p->setName(buf);
		infile >> buf;
		p->setPassword(buf);
		infile >> temp;
		p->setRecord(temp);
		_player.push_back(*p);
		i++;
	}
	infile.close();
	delete[]buf;
}

void Data::write()
{
	ofstream outfile;
	char* buf = new char[20];
	outfile.open("player.dat");
	outfile << "num\thighest\n" << Player::num() << '\t' << Player::highest() << endl
		<< "account\tname\tpassword\trecord" << endl;
	for (int i = 0; i < Player::num(); i++)
	{
		outfile << _player[i].account() << '\t' << _player[i].name() << '\t' << _player[i].password() << '\t' << _player[i].record() << endl;
	}
	outfile.close();
	delete[]buf;
}
