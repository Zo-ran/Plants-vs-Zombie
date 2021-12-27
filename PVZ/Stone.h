#pragma once
#include"Plant.h"
class Stone: public Plant
{
	friend class StoneList;
public:
	Stone();
	Stone(int x, int y);
};

class StoneList: public PlantsList
{
public:
	StoneList();

	bool Add(int x, int y);

	void Draw(Plant* plant, int x, int y);
};