#pragma once
#include"Plant.h"
using namespace std;

class HighShooter: public Plant
{
	friend class HighShooterList;
private:
	int gap;
public:
	HighShooter(int x, int y);
};

class FlyBullet
{
	friend class HighShooterList;

private:
	double x, y;
	bool fly;
public:
	FlyBullet(double x, double y, bool fly);
	FlyBullet();
};

class HighShooterList: public PlantsList
{
private:
	list<FlyBullet> bullets_list;

public:
	HighShooterList();

	bool Add(int x, int y);

	void Fire();

	void MoveBullet();

	void Draw(Plant* plant, int x, int y);

	void DrawBullet();
};