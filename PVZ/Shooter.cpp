#include "Shooter.h"
#include "MapPlants.h"
#include "Bullet.h"
#include "DrawMap.h"

extern Plants MapPlants[5][10];
extern BulletList bulletlist;
ShooterList shooterlist;

Shooter::Shooter() {
	x = 0;
	y = 0;
	blood = 5000;
	gap = 0;
}

Shooter::Shooter(int x, int y) : Plant(x, y, 5000), gap(0) { }

ShooterList::ShooterList() {
	plants.resize(0);
}

bool ShooterList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = shooter;
		Shooter* p = new Shooter(x, y);
		plants.push_back(p);
		return true;
	}
}

void ShooterList::Routine() {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Shooter* p = (Shooter *)(*i);
		p->gap++;
	}
}

void ShooterList::Fire() {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Shooter* p = (Shooter*)(*i);
		if (p->gap >= 1500) {
			bulletlist.Add((p->y - 80) / 80, p->x / 60);
			p->gap = 0;
		}
	}
}

void ShooterList::Draw(Plant* plant, int x, int y) {
	Shooter* var = (Shooter*)plant;
	setfillcolor(ShooterColor);
	setlinecolor(ShooterColor);
	setlinestyle(PS_SOLID, 2);
	rectangle(x + 15, 25 + y, x + 45, y + 55);
	int offset = (30 * var->gap / 1500) / 2;
	solidrectangle(x + 30 - offset, y + 40 - offset, x + 30 + offset, y + 40 + offset);
}