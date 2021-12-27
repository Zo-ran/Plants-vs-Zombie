#include "Thorns.h"
#include "MapPlants.h"
#include "DrawMap.h"

extern Plants MapPlants[5][10];
ThornsList thornslist;

Thorns::Thorns(int x, int y) : Plant(x, y, 20000) { }

ThornsList::ThornsList() {
	plants.resize(0);
}

bool ThornsList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = thorns;
		Thorns* p = new Thorns(x, y);
		plants.push_back(p);

		return true;
	}
}

void ThornsList::Draw(Plant* plant, int x, int y) {
	DrawThorns(x + 20, y + 10);
}