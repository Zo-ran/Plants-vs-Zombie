#include "FFZombie.h"
#include "DrawMap.h"
#include "AllPlants.h"
#include "MapPlants.h"

FFZombieList ffzombielist;
extern Plants MapPlants[5][10];

void FFZombieList::setcolor() {
	setfillcolor(FFColor);
	setlinecolor(FFColor);
}

FFZombie::FFZombie(): FlyZombie(), gap(0) { }

FFZombieList::FFZombieList() {
	blts.resize(0);
}

void FFZombieList::Add() {
	FFZombie* p = new FFZombie;
	l.push_back(p);
}

void FFZombieList::Fire() {
	for (auto i = l.begin(); i != l.end(); i++) {
		FFZombie* p = (FFZombie*)(*i);
		if (p->gap >= 2000) {
			p->gap = 0;
			int row = p->y / 80 - 1, col = p->x / 60;
			bool find = false;
			int i = col, j = col;
			for (; i >= 0; i--) 
				if (MapPlants[row][i] != vacant && MapPlants[row][i] != spikeweed) {
					find = true;
					break;
				}
			for (; j <= 9; j++)
				if (MapPlants[row][j] != vacant && MapPlants[row][j] != spikeweed) {
					find = true; 
					break;
				}
			if (find) {
				if (i < 0 || (j - col < col - i && j <= 9))
					i = j;
				switch (MapPlants[row][i]) {
					case sunflower: {
						sunflowerlist.Hurt(row, i, 500);
						break;
					} case shooter: {
						shooterlist.Hurt(row, i, 500);
						break;
					} case stone: {
						stonelist.Hurt(row, i, 500);
						break;
					} case highshooter: {
						highshooterlist.Hurt(row, i, 500);
						break;
					} case thorns: {
						thornslist.Hurt(row, i, 500);
						break;
					} case dominator: {
						dominatorlist.Hurt(row, i, 500);
						break;
					} case spikeweed: {
						break;
					}
				}
				FFBlt b(p->x - 8, p->y + 15, i * 60 + 30, (row + 1) * 80 + 40);
				blts.push_back(b);
			}
		}
		p->gap++;
	}
}

void FFZombieList::DrawBlt() {
	for (auto i = blts.begin(); i != blts.end(); ) {
		setlinecolor(FFColor);
		setlinestyle(PS_SOLID, i->thickns);
		line(i->begin_x, i->begin_y, i->end_x, i->end_y);
		if (i->thickns <= 0)
			i = blts.erase(i);
		else {
			i->thickns -= 0.03;
			i++;
		}
	}
	setlinestyle(PS_SOLID, 2);
}

void FFZombieList::d(FlyZombie *t) {
	setfillcolor(FFColor);
	FFZombie* p = (FFZombie*)t;
	solidcircle(p->x - 8, p->y + 15, 5 * p->gap / 2000);
}