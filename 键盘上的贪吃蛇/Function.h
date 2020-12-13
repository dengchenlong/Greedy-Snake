#pragma once
#include "Const.h"

class Player;
class Snake;
class Obstacle;
class Hole;
class Food;

// 枚举声明
// 方向控制
enum class Direction;
// 颜色
enum class Color;
// 结束的情况
enum class EndCondition;

// 全局变量声明
extern int add;
// 刷新间隔，控制速度
extern int sleeptime;
// 按键情况
extern Direction direction;
// 游戏结束情况
extern EndCondition endcondition;
// 玩家id
extern int id;
// 食物
extern Food* food;
// 蛇
extern Snake* head;
// 分数
extern int score;

// 全局函数声明
// 设置颜色
void setColor(Color color);
// 定位函数，作用是设置光标的位置
void setLocation(int x, int y);
// 创建地图
void createWall();
// 暂停函数，当按下空格，表示要暂停游戏
void pause();
// 游戏登录
void log();
// 进行游戏
void playing();
// 游戏结束
void end();
void write(Player* player);
void read(Player* player);
