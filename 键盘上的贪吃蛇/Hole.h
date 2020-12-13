#pragma once
#include "Const.h"
#include "Point.h"
// 虫洞类
class Hole
{
private:
	// 两个洞口坐标
	Point _point[2];
	static int _num;
public:
	// 生成虫洞
	static void createHoles();
	static int num();

	void createHole(int id);
	Point& getPoint(int i);
	// 创建必需虫洞
	void createNecessity();
};

