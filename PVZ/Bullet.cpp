#include "Bullet.h"
#include"Zombie.h"
#include"DrawMap.h"
#include"FlyZombie.h"
#include"FireZombie.h"

#define length 0.1
#define BulletHarm 10

bool flag = false;
BulletList bulletlist;
extern ZombieList zombielist;
extern FlyZombieList flyzombielist;
extern FireZombieList firezombielist;

Bullet::Bullet(int row, int col) {
	x = (double)col * 60 + 45;
	y = (double)row * 80 + 112.5;
}

Bullet::Bullet() {
	x = 0;
	y = 0;
}

Bullet::Bullet(const Bullet& p) {
	x = p.x;
	y = p.y;
}

BulletList::BulletList() {
	l.resize(0);
}

void BulletList::Add(int row, int col) {
	Bullet p(row, col);
	l.push_back(p);
}

void BulletList::Move() {
	for (auto i = l.begin(); i != l.end(); i++) {
		(*i).x += length;
	}
}

void BulletList::Clean() {
	for (auto i = l.begin(); i != l.end(); ) {
		Bullet p = *i;
		if (p.x > ScreenWidth) {
			i = l.erase(i);
		} else {
			if (zombielist.BeHit(p.x + 15, p.y)) {
				i = l.erase(i);
			} else if (firezombielist.BeHit(p.x + 15, p.y)) {
				i = l.erase(i);
			} else {
				i++;
			}
		}
	}
}

void BulletList::Draw() {
	HRGN rgn = CreateRectRgn(0, 0, ScreenWidth, ScreenHight);
	setcliprgn(rgn);
	DeleteObject(rgn);
	setfillcolor(ShooterColor);
	for (auto i = l.begin(); i != l.end(); i++) {
		Bullet temp = *i;
		double x = temp.x;
		double y = temp.y;
		solidrectangle(x, y, x + 15, y + 15);
	}
}