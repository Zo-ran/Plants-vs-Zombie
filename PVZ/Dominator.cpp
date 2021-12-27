#include "Dominator.h"
#include"MapPlants.h"
#include<stdlib.h>
#include<time.h>
#include "AllPlants.h"
#include "DrawMap.h"

extern Plants MapPlants[5][10];
DominatorList dominatorlist; 
int DominatorList::seed = 0;

Dominator::Dominator(int x, int y): Plant(x, y, 1), gap(0) { }

DominatorList::DominatorList() {
	plants.resize(0);
}

bool DominatorList::Add(int x, int y) {
	int row = (y - 80) / 80;
	int col = x / 60;

	if (MapPlants[row][col] != vacant)
		return false;

	else {
		MapPlants[row][col] = dominator;
		Dominator* p = new Dominator(x, y);
		plants.push_back(p);

		return true;
	}
}

void DominatorList::Summon() {
	if (seed == 0) {
		srand((unsigned int)time(0));
		seed++;
	}

	for (auto i = plants.begin(); i != plants.end(); i++) {
		Dominator* p = (Dominator*)(*i);
		p->gap++;
		if (p->gap % 3000 == 0) {
			int row, col, cnt = 0, which;
			do {
				row = rand() % 5;
				col = rand() % 5;
			} while (MapPlants[row][col] != vacant && cnt++ < 200);

			which = rand() % 4;
			if (MapPlants[row][col] == vacant) {
				if (which == 0) {
					stonelist.Add(col * 60 + 2, (row + 1) * 80 + 2);
				} else if (which == 1) {
					shooterlist.Add(col * 60 + 2, (row + 1) * 80 + 2);
				} else if (which == 2) {
					highshooterlist.Add(col * 60 + 2, (row + 1) * 80 + 2);
				} else {
					thornslist.Add(col * 60 + 2, (row + 1) * 80 + 2);
				}
			}
		}
	}
}

void DominatorList::Draw(Plant* plant, int x, int y) {
	DrawDominator(x + 10, y + 15);
}