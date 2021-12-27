#include "FireZombie.h"
#include "Zombie.h"
#include "DrawMap.h"
#include "AllPlants.h"
#include "MapPlants.h"
#define zombie_mov_length 0.04

extern Plants MapPlants[5][10];
FireZombieList firezombielist;

FireZombie::FireZombie(): Zombie(), gap(0) { }

FireZombieList::FireZombieList() {
	zombies_list.resize(0);
	bullets_list.resize(0);
}

ZombieBullet::ZombieBullet(double x, double y) {
	this->x = x - 20;
	this->y = y;
}

void FireZombieList::Draw() {
	setfillcolor(ShooterColor);
	setlinecolor(ShooterColor);
	for (auto i = zombies_list.begin(); i != zombies_list.end(); i++) {
		FireZombie* p = (FireZombie*)(*i);
		double offset = 2 * 3.14 - (p->blood * 2 * 3.14 / 10000);
		solidpie(p->x, p->y - 15, p->x + 30, p->y + 15, (3.14 + offset) / 2, (3.14 - offset) / 2);
		circle(p->x + 15, p->y, 15);
	}

	for (auto i = bullets_list.begin(); i != bullets_list.end(); i++) {
		solidcircle(i->x + 10, i->y, 10);
	}
}

void FireZombieList::Fire() {
	for (auto i = zombies_list.begin(); i != zombies_list.end(); i++) {
		FireZombie* p = (FireZombie*)(*i);
		if (p->gap % 3000 == 0) {
			ZombieBullet b(p->x, p->y);
			bullets_list.push_back(b);
		}
		p->gap++;
	}
}

void FireZombieList::MoveBullets() {
	for (auto i = bullets_list.begin(); i != bullets_list.end(); ) {
		int x = i->x, y = i->y;
		int row = (int)y / 80 - 1, col = (int)x / 60;
		if (x <= 0) {
			i = bullets_list.erase(i);
			continue;
		}
			
		bool go = true;
		if (MapPlants[row][col] != vacant) {
			switch (MapPlants[row][col]) {
				case sunflower: {
					if ((x - (col * 60 + 45)) > -45 && (x - (col * 60 + 45)) < 2) {
						sunflowerlist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case shooter: {
					if ((x - (col * 60 + 45)) > -45 && (x - (col * 60 + 45)) < 2) {
						shooterlist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case stone: {
					if ((x - (col * 60 + 45)) > -45 && (x - (col * 60 + 45)) < 2) {
						stonelist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case highshooter: {
					if ((x - (col * 60 + 40)) > -45 && (x - (col * 60 + 40)) < 2) {
						highshooterlist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case thorns: {
					if ((x - (col * 60 + 40)) > -45 && (x - (col * 60 + 40)) < 2) {
						thornslist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case dominator: {
					if ((x - (col * 60 + 50)) > -45 && (x - (col * 60 + 50)) < 2) {
						dominatorlist.Hurt(row, col, 500);
						i = bullets_list.erase(i);
						go = false;
					} else {
						i->x -= zombie_mov_length;
					}
					break;
				} case spikeweed: {
					i->x -= zombie_mov_length;
					break;
				}
			}
		} else {
			i->x -= zombie_mov_length;
		}
		if (go)
			i++;
	}
}