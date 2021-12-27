#pragma once
#include"Plant.h"

class Dominator: public Plant
{
	friend class DominatorList;
public:
	Dominator(int x, int y);

private:
	int gap;
};

class DominatorList: public PlantsList
{
private:
	static int seed;

public:

	DominatorList();

	bool Add(int x, int y);

	void Summon();

	void Draw(Plant* plant, int x, int y);
};

