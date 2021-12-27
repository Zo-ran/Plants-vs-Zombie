#pragma once
#include"Plant.h"

class Sun
{
	friend class SunList;
private:
	double x, y;   //����
	bool clicked;
public:
	Sun();                //����������, ����ڵ�ͼ������һ��̫��
	Sun(int x, int y);    //����һ�����տ�������, ����һ��̫��
};

class SunList
{
private:
	list<Sun> suns;
public:
	SunList();

	void Add(int x, int y);

	void Add();

	void Move();

	bool Clicked(int x, int y);

	void Draw();

	int TotalEnergy;
};

class SunFlower: public Plant
{	
	friend class SunFlowerList;
public:
	SunFlower();
	SunFlower(int x, int y);
private:
	int gap;
};

class SunFlowerList: public PlantsList
{
public:
	SunFlowerList();

	bool Add(int x, int y);

	void Routine();

	void GetEnergy();

	void Draw(Plant *plant, int x, int y);
};