#pragma once
#include "Const.h"
#include "Point.h"
// �涴��
class Hole
{
private:
	// ������������
	Point _point[2];
	static int _num;
public:
	// ���ɳ涴
	static void createHoles();
	static int num();

	void createHole(int id);
	Point& getPoint(int i);
	// ��������涴
	void createNecessity();
};

