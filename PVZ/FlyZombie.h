#pragma once
#include<list>
using namespace std;
class FlyZombie 
{
	friend class FlyZombieList;

protected:
	double x, y;

	int blood;

	bool fly;    //用于判断该僵尸是否被击落

public:
	FlyZombie();
};

class FlyZombieList
{
protected:
	list<FlyZombie *> l;

	virtual void setcolor();

	virtual void d(FlyZombie *t) { };
public:
	virtual void Add();
	
	FlyZombieList();

	void Move();   //僵尸的向前移动
		
	bool RowJudge(int row);

	void Draw(); //在地图上绘制僵尸

	bool BeHit(double x, double y);

	bool Over();
};

