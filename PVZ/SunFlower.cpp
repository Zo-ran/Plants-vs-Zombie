#include "SunFlower.h"
#include "MapPlants.h"
#include "DrawMap.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define rate 5000

static int seed = 0;
SunFlowerList sunflowerlist;
SunList sunlist;
extern Plants MapPlants[5][10];

static double dist(double x1, double y1, double x2, double y2) {
	double result;
	result = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return result;
}

Sun::Sun() {
	if (seed == 0) {
		srand((unsigned int)time(0));
		seed++;
	}
	int row = rand() % 5;
	int col = rand() % 10;
	x = col * 60 + 30;
	y = (row + 1) * 80 + 10;
	clicked = false;
}

Sun::Sun(int x, int y) {
	int row = y / 80 - 1, col = x / 60;
	this->x = col * 60 + 55;
	this->y = (row + 1) * 80 + 75;
	this->clicked = false;
}

SunList::SunList() {
	suns.resize(0);
	TotalEnergy = 200;
}

void SunList::Add(int x, int y) {
	suns.push_back(Sun(x, y));
}

void SunList::Add() {
	suns.push_back(Sun());
}

void SunList::Move() {
	for (auto i = suns.begin(); i != suns.end(); ) {
		if (i->clicked) {
			double angle = atan((i->y - 30) / (i->x - 30));
			i->x -= cos(angle);
			i->y -= sin(angle);
		}
		if (dist(i->x, i->y, 30, 30) < SunFlowerRadius + 5)
			i = suns.erase(i);
		else
			i++;
	}
}

bool SunList::Clicked(int x, int y) {
	for (auto i = suns.begin(); i != suns.end(); i++) {
		if (dist(x, y, i->x, i->y) < 30 && !i->clicked) {
			i->clicked = true;
			TotalEnergy += 25;
			return true;
		}
	}
}

void SunList::Draw() {
	for (auto i = suns.begin(); i != suns.end(); i++) {
		setfillcolor(SunFlowerColor);
		solidcircle(i->x, i->y, 10);
	}
}

SunFlower::SunFlower() {
	x = 0;
	y = 0;
	blood = 5000;
	gap = 0;
}

SunFlower::SunFlower(int x, int y): Plant(x, y, 5000), gap(0) { }

SunFlowerList::SunFlowerList() {
	plants.resize(0);
}

bool SunFlowerList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;
	
	if(MapPlants[row][col] != vacant)
		return false;
	
	else {
		MapPlants[row][col] = sunflower;
		SunFlower* p = new SunFlower(x, y);
		plants.push_back(p);

		return true;
	}
}

void SunFlowerList::Routine() {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		SunFlower* p = (SunFlower*)(*i);
		p->gap++;
	}
}

void SunFlowerList::GetEnergy() {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		SunFlower* p = (SunFlower*)(*i);
		if (p->gap >= rate) {
			sunlist.Add(p->x, p->y);
			p->gap = 0;
		}
	}
}

void SunFlowerList::Draw(Plant *plant, int x, int y) {
	SunFlower* var = (SunFlower*)plant;
	setfillcolor(SunFlowerColor);
	setlinecolor(SunFlowerColor);
	setlinestyle(PS_SOLID, 2);
	circle(x + 30, y + 40, 15);
	solidcircle(x + 30, y + 40, 15 * var->gap / rate);
}