#pragma once
#include<list>
using namespace std;

class Bullet
{
	friend class BulletList;

private:
	double x, y;

public:
	Bullet(const Bullet& p);
	
	Bullet();

	Bullet(int row, int col);
};

class BulletList
{
private:
	list<Bullet> l;

public:

	BulletList();

	void Add(int row, int col);

	void Move();

	void Clean();

	void Draw();
};
