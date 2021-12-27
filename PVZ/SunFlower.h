#pragma once
#include"Plant.h"

class Sun
{
	friend class SunList;
private:
	double x, y;   //坐标
	bool clicked;
public:
	Sun();                //不给出坐标, 随机在地图上生成一个太阳
	Sun(int x, int y);    //给出一个向日葵的坐标, 生成一个太阳
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