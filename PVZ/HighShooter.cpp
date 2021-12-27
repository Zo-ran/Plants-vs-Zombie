#include "HighShooter.h"
#include "MapPlants.h"
#include "DrawMap.h"
#include "AllZombie.h"

#define fire_rate 1500
#define bullet_mov_length 0.1

extern Plants MapPlants[5][10];
HighShooterList highshooterlist;

FlyBullet::FlyBullet() {
	x = 0;
	y = 0;
	fly = false;
}

FlyBullet::FlyBullet(double x, double y, bool fly) {
	this->x = x;
	this->y = y;
	this->fly = fly;
}

HighShooter::HighShooter(int x, int y): Plant(x, y, 5000), gap(0){ }

HighShooterList::HighShooterList() {
	plants.resize(0);
	bullets_list.resize(0);
}

bool HighShooterList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = highshooter;
		HighShooter* p = new HighShooter(x, y);
		plants.push_back(p);
		return true;
	}
}

void HighShooterList::Fire() {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		HighShooter* p = (HighShooter*)(*i);
		if (p->gap >= fire_rate) {
			int row = (p->y - 80) / 80, col = p->x / 60;
			if (flyzombielist.RowJudge(row) || ffzombielist.RowJudge(row)) {
				FlyBullet b(col * 60 + 40, (row + 1) * 80 + 10, true);
				bullets_list.push_back(b);
			} else {
				FlyBullet b(col * 60 + 40, (row + 1) * 80 + 30, false);
				bullets_list.push_back(b);
			}
			p->gap = 0;
		}
		((HighShooter*)(*i))->gap++;
	}
}

void HighShooterList::DrawBullet() {
	for (auto i = bullets_list.begin(); i != bullets_list.end(); i++) {
		int x = i->x, y = i->y;
		setfillcolor(HighShooterColor);
		POINT ptr[3] = { {x, y}, {x + 15, y + 9}, {x, y + 18} };
		solidpolygon(ptr, 3);
	}
}


void HighShooterList::MoveBullet() {
	for (auto i = bullets_list.begin(); i != bullets_list.end(); ) {
		i->x += bullet_mov_length;
		if (i->fly) {
			if (flyzombielist.BeHit(i->x + 15, i->y) || ffzombielist.BeHit(i->x + 15, i->y)) {
				i = bullets_list.erase(i);
			} else {
				i++;
			}
		} else {
			if (zombielist.BeHit(i->x + 15, i->y) || firezombielist.BeHit(i->x + 15, i->y)) {
				i = bullets_list.erase(i);
			} else {
				i++;
			}
		}
	}
}

void HighShooterList::Draw(Plant* plant, int x, int y) {
	HighShooter* var = (HighShooter*)plant;
	setfillcolor(HighShooterColor);
	setlinecolor(HighShooterColor);
	setlinestyle(PS_SOLID, 2);
	rectangle(x + 20, y + 20, x + 40, y + 60);
	int offset = 20 * var->gap / fire_rate / 2;
	solidrectangle(x + 30 - offset, y + 40 - 2 * offset, x + 30 + offset, y + 40 + 2 * offset);
}