#include "Stone.h"
#include "MapPlants.h"
#include "DrawMap.h"

extern Plants MapPlants[5][10];
StoneList stonelist;

Stone::Stone() {
	x = 0;
	y = 0;
	blood = 50000;
}

Stone::Stone(int x, int y): Plant(x, y, 30000) { }

StoneList::StoneList() {
	plants.resize(0);
}

bool StoneList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = stone;
		Stone* p = new Stone(x, y);
		plants.push_back(p);

		return true;
	}
}

void StoneList::Draw(Plant* plant, int x, int y) {
	setfillcolor(StoneColor);
	solidellipse(x + 15, 15 + y, x + 45, 60 + y);
}