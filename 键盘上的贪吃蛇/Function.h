#pragma once
#include "Const.h"

class Player;
class Snake;
class Obstacle;
class Hole;
class Food;

// ö������
// �������
enum class Direction;
// ��ɫ
enum class Color;
// ���������
enum class EndCondition;

// ȫ�ֱ�������
extern int add;
// ˢ�¼���������ٶ�
extern int sleeptime;
// �������
extern Direction direction;
// ��Ϸ�������
extern EndCondition endcondition;
// ���id
extern int id;
// ʳ��
extern Food* food;
// ��
extern Snake* head;
// ����
extern int score;

// ȫ�ֺ�������
// ������ɫ
void setColor(Color color);
// ��λ���������������ù���λ��
void setLocation(int x, int y);
// ������ͼ
void createWall();
// ��ͣ�����������¿ո񣬱�ʾҪ��ͣ��Ϸ
void pause();
// ��Ϸ��¼
void log();
// ������Ϸ
void playing();
// ��Ϸ����
void end();
void write(Player* player);
void read(Player* player);
