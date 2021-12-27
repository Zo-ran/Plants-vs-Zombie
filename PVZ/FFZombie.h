#pragma once
#include "FlyZombie.h"
#include <list>
using namespace std;

class FFZombie : public FlyZombie
{
	friend class FFZombieList;
public:
	FFZombie();
private:
	int gap;
};

class FFBlt
{
	friend class FFZombieList;
private:
	double begin_x, begin_y, end_x, end_y;
	double thickns;
public:
	FFBlt(double x1, double y1, double x2, double y2) : begin_x(x1), begin_y(y1), end_x(x2), end_y(y2), thickns(10) { }

	FFBlt() : begin_x(0), begin_y(0), end_x(0), end_y(0), thickns(10) { }
};


class FFZombieList : public FlyZombieList
{
private:
	list<FFBlt> blts;
	void setcolor();
	void d(FlyZombie *t);

public:
	FFZombieList();
	
	void Fire(); 
	
	void Add();

	void DrawBlt();
};