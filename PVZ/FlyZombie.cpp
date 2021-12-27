#include "FlyZombie.h"
#include <stdlib.h>
#include <time.h>
#include "DrawMap.h"
#include "MapPlants.h"
#include "Thorns.h"
#include "Zombie.h"

static int seed = 0;
FlyZombieList flyzombielist;
extern Plants MapPlants[5][10];
extern ThornsList thornslist;
extern uint32_t TOTAL_SCORE;

FlyZombie::FlyZombie() {
	blood = 10000;
	fly = true;
	if (seed == 0) {
		srand((unsigned int)time(0));
		seed++;
	}
	
	y = rand() % 5;
	y = (y + 1) * SquareHight;
	x = ScreenWidth;
}

FlyZombieList::FlyZombieList() {
	l.resize(0);
}

void FlyZombieList::Add() {
	FlyZombie *p = new FlyZombie;
	l.push_back(p);
}

void FlyZombieList::Move() {
	for (auto i = l.begin(); i != l.end(); ) {
		int x = (*i)->x, y = (*i)->y;
		bool go = true;
		int row = (y - 80) / 80, col = x / 60;
		if (MapPlants[row][col] == thorns) {
			if (x == col * 60 + 40) {
				thornslist.Hurt(row, col);
				(*i)->blood -= 2;
				if ((*i)->blood < 0) {
					i = l.erase(i);
					TOTAL_SCORE += 30;
					go = false;
				}
			} else {
				(*i)->x -= 0.02;
			}
		} else {
			(*i)->x -= 0.02;
		}
		if (go)
			i++;
	}
}

bool FlyZombieList::BeHit(double x, double y) {
	for (auto i = l.begin(); i != l.end(); i++) {
		if (((*i)->x - x < 1 && (*i)->x - x > -1 || (int)((*i)->x) == (int)x - 15) && (int)((*i)->y) / 80 == (int)(y) / 80) {
			(*i)->blood -= 1000;
			if ((*i)->blood < 0) {
				TOTAL_SCORE += 30;
				l.erase(i);
			}
			return true;
		}
	}
	return false;
}

void FlyZombieList::setcolor() {
	setfillcolor(FlyZombieColor);
	setlinecolor(FlyZombieColor);
}

void FlyZombieList::Draw() {
	setcolor();
	for (auto i = l.begin(); i != l.end(); i++) {
		d(*i);
		double x = (*i)->x;
		double y = (*i)->y;
		int offset = (*i)->blood * 10 / 10000;
		solidrectangle(x, y + 20 - offset, x + 40, y + 20);
		rectangle(x, y + 10, x + 40, y + 20);
	}
}

bool FlyZombieList::RowJudge(int row) {       //判断该行有无飞行僵尸 ps: 用于判断高射手是否需要改变发射子弹的状态, 发射飞行子弹
	for (auto i = l.begin(); i != l.end(); i++) {
		if (((*i)->y - 80) / 80 == row)
			return true;
	}
	return false;
}

bool FlyZombieList::Over() {
	for (auto i = l.begin(); i != l.end(); i++)
		if ((*i)->x <= 0)
			return true;
	return false;
}