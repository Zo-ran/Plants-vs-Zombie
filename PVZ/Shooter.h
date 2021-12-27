#pragma once
#include"Plant.h"
class Shooter: public Plant
{
	friend class ShooterList;
public:
	Shooter();
	Shooter(int x, int y);
private:
	int gap;
};

class ShooterList: public PlantsList
{
public:
	ShooterList();

	bool Add(int x, int y);

	void Routine();

	void Fire();

	void Draw(Plant* plant, int x, int y);
};

