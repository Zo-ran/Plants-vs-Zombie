#pragma once
#include<list>
using namespace std;
class Zombie
{
	friend class ZombieList;
protected:
	double x, y;
	int blood;
public:	
	Zombie();
};

class ZombieList
{
protected:
	list<Zombie* > zombies_list;

public:
	ZombieList();
	
	virtual void Add();
	
	void Move();

	bool BeHit(double x, double y);

	virtual void Draw();

	bool Over();      //
};