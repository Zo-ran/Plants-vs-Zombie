#pragma once
#include"Plant.h"
class Thorns: public Plant
{
	friend class ThornsList;
public:
	Thorns(int x, int y);
};

class ThornsList : public PlantsList
{
public:
	ThornsList();

	bool Add(int x, int y);

	void Draw(Plant* plant, int x, int y);
};
