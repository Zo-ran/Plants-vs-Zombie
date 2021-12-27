#pragma once
#include<list>
using namespace std;
class Plant
{
	friend class PlantsList;

protected:
	int blood;
	int x, y;

public:
	Plant();
	Plant(int x, int y, int blood);
};

class PlantsList
{
protected:
	list<Plant *> plants;

public:
	virtual bool Add(int x, int y) = 0;

	bool Hurt(int row, int col);

	bool Hurt(int row, int col, int damage);

	bool InspectAlive(int row, int col);

	void DrawBloodStrip(int base);

	virtual void Draw(Plant* plant, int x, int y) { };

	PlantsList();
};