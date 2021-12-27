#pragma once
#include"Zombie.h"
#include<list>
using namespace std;

class FireZombie : public Zombie
{
	friend class FireZombieList;
public:
	FireZombie();
private:
	int gap;
};

class ZombieBullet
{
	friend class FireZombieList;
private:
	double x, y;
public:
	ZombieBullet(double x, double y);

	ZombieBullet(): x(0), y(0) { }
};

class FireZombieList : public ZombieList
{
private:
	list<ZombieBullet> bullets_list;

public:
	void Fire();

	FireZombieList();

	void Draw();

	void MoveBullets();
};

