#include "Plant.h"
#include "DrawMap.h"
Plant::Plant() {
	blood = 100;
	x = 0, y = 0;
}

Plant::Plant(int x, int y, int blood) {
	this->x = x;
	this->y = y;
	this->blood = blood;
}

PlantsList::PlantsList() {
	plants.resize(0);
}

bool PlantsList::InspectAlive(int row, int col) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Plant* p = *i;
		if (p->x / 60 == col && p->y / 80 - 1 == row) {
			if (p->blood > 0)
				return true;
			else {
				plants.erase(i);
				return false;
			}
		}
	}
}

bool PlantsList::Hurt(int row, int col) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Plant *p = *i;
		if (p->x / 60 == col && p->y / 80 - 1 == row) {
			p->blood -= 1;
			return true;
		}
	}
}

bool PlantsList::Hurt(int row, int col, int damage) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Plant *p = *i;
		if (p->x / 60 == col && p->y / 80 - 1 == row) {
			p->blood -= damage;
			return true;
		}
	}
}

void PlantsList::DrawBloodStrip(int base) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Plant* p = *i;
		int row = p->y / 80 - 1, col = p->x / 60;
		int x = col * 60, y = (row + 1) * 80;
		int offset = 40 * p->blood / base;
		setfillcolor(RED);
		setlinecolor(RED);
		rectangle(x + 10, y + 5, x + 50, y + 8);
		solidrectangle(x + 10, y + 5, x + 10 + offset, y + 8);
		Draw(p, x, y);
	}
}
