#include "Spikeweed.h"
#include "MapPlants.h"
#include "DrawMap.h"

extern Plants MapPlants[5][10];
SpkwdList spkwdlist;

Spikeweed::Spikeweed(int x, int y) : Plant(x, y, 20000) { }

SpkwdList::SpkwdList() {
	plants.resize(0);
}

bool SpkwdList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = spikeweed;
		Spikeweed* p = new Spikeweed(x, y);
		plants.push_back(p);
		return true;
	}
}

void SpkwdList::DrawBloodStrip(int base) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Spikeweed* p = (Spikeweed*)(*i);
		if (p->height >= 17) {
			p->dirct = -1;
		} else if (p->height <= 3) {
			p->dirct = 1;
		} 
		p->height += p->dirct * 0.04;
		DrawSpkwd(p->x / 60 * 60 + 10, p->y / 80 * 80 + 75, p->height);
	}
}

double SpkwdList::GetHeight(int row, int col) {
	for (auto i = plants.begin(); i != plants.end(); i++) {
		Spikeweed* p = (Spikeweed*)(*i);
		if (p->x / 60 == col && p->y / 80 - 1 == row)
			return p->height;
	}
}