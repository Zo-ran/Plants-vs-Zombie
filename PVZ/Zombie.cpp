#include "Zombie.h"
#include <stdlib.h>
#include <time.h>
#include "AllPlants.h"
#include "MapPlants.h"
#include "DrawMap.h"
#define zombie_mov_length 0.02

static int seed = 0;
ZombieList zombielist;
uint32_t TOTAL_SCORE = 0;
extern Plants MapPlants[5][10];

Zombie::Zombie() {
	blood = 10000;

	if (seed == 0) {
		srand((unsigned int)time(0));
		seed++;
	}
	y = rand() % 5;
	y = 120 + y * 80;
	x = ScreenWidth;
}

ZombieList::ZombieList() {
	zombies_list.resize(0);
}

void ZombieList::Add() {
	Zombie* p = new Zombie;
	zombies_list.push_back(p);
}

void ZombieList::Move() {
	for (auto i = zombies_list.begin(); i != zombies_list.end(); ) {
		Zombie* p = *i;
		int x = p->x, y = p->y;
		int row = (int)y / 80 - 1, col = (int)x / 60;
		bool go = true;
		if (MapPlants[row][col] != vacant) {
			switch (MapPlants[row][col]) {
				case sunflower: {
					if (x == col * 60 + 45) {
						sunflowerlist.Hurt(row, col);
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case shooter: {
					if (x == col * 60 + 45) {
						shooterlist.Hurt(row, col);
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case stone: {
					if (x == col * 60 + 45) {
						stonelist.Hurt(row, col);
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case highshooter: {
					if (x == col * 60 + 40) {
						highshooterlist.Hurt(row, col);
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case thorns: {
					if (x == col * 60 + 40) {
						thornslist.Hurt(row, col);
						p->blood -= 2;
						if (p->blood < 0) {
							TOTAL_SCORE += 10;
							i = zombies_list.erase(i);
							go = false;
						}
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case dominator: {
					if (x == col * 60 + 50) {
						dominatorlist.Hurt(row, col);
					} else {
						p->x -= zombie_mov_length;
					}
					break;
				} case spikeweed: {
					int height = spkwdlist.GetHeight(row, col);
					if (height >= 12)
						p->blood -= 5;
					if (p->blood < 0) {
						TOTAL_SCORE += 10;
						i = zombies_list.erase(i);
						go = false;
					}
					p->x -= zombie_mov_length;
					break;
				}
			}
		} else {
			p->x -= zombie_mov_length;
		}
		if (go)
			i++;
	}
}

bool ZombieList::BeHit(double x, double y) {      //判断是否有一个僵尸被子弹打中, 传入子弹的坐标, 返回一个bool
	for (auto i = zombies_list.begin(); i != zombies_list.end(); i++) {
		Zombie* p = *i;
		if ((p->x - x < 1 && p->x - x > -1 || (int)(p->x) == (int)x - 15) && (int)(p->y) / 80 == (int)(y) / 80) {
			p->blood -= 1000;
			if (p->blood < 0) {
				zombies_list.erase(i);
				TOTAL_SCORE += 10;
			}
			return true;
		}
	}
	return false;
}

void ZombieList::Draw() {
	setfillcolor(ZombieColor);
	setlinecolor(ZombieColor);
	for (auto i = zombies_list.begin(); i != zombies_list.end(); i++) {
		Zombie* p = *i;
		int x = p->x, y = p->y, offset = p->blood * 30 / 10000 ;
		solidrectangle(x, y + 20 - offset, x + 20, y + 20);
		rectangle(x, y - 10, x + 20, y + 20);
	}
}

bool ZombieList::Over() {
	for (auto i = zombies_list.begin(); i != zombies_list.end(); i++) {
		Zombie* p = *i;
		if (p->x <= 0)
			return true;
	}
	return false;
}