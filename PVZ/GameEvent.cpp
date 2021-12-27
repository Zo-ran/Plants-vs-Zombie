#include"GameEvent.h"
#include"MapPlants.h"
#include"Bullet.h"
#include"AllPlants.h"
#include"AllZombie.h"

#define BulletGap 1500
#define rate 5000

static int times = 0;
static int frequency = 16000;
static int base = 0;
static int ff_frequency = 30000;
static int fly_frequency = 40000;
static int fire_frequency = 50000;

extern BulletList bulletlist;
extern Plants MapPlants[5][10];

void InspectAlive() {
	for (int row = 0; row < 5; row++)
		for (int col = 0; col < 10; col++) {
			switch (MapPlants[row][col]) {
				case sunflower: {
					if (!sunflowerlist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}

				case stone: {
					if (!stonelist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}

				case shooter: {
					if(!shooterlist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}

				case highshooter: {
					if (!highshooterlist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}

				case thorns: {
					if (!thornslist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}
				
				case dominator: {
					if (!dominatorlist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}

				case spikeweed: {
					if (!spkwdlist.InspectAlive(row, col))
						MapPlants[row][col] = vacant;
					break;
				}
			}
		}
}

void AddZombie() {
	times++;
	if(frequency > 5000)
		frequency -= 1;
	if (times % frequency == 0) 
		zombielist.Add();
	
	if (fly_frequency > 10000)
		fly_frequency -= 1;
	if (times % fly_frequency == 0)
		flyzombielist.Add();
	
	if (fire_frequency > 14000)
		fire_frequency -= 1;
	if (times % fire_frequency == 0) {
		firezombielist.Add();
	}
	
	if (ff_frequency > 12000)
		ff_frequency -= 1;
	if (times % ff_frequency == 0)
		ffzombielist.Add();
}

void FireBullet() {
	shooterlist.Fire();
	highshooterlist.Fire();

	shooterlist.Routine();
	
	bulletlist.Clean();
	
	bulletlist.Move(); 
	highshooterlist.MoveBullet();
}

void AddEnergy() {
	base++;

	sunflowerlist.Routine();
	sunflowerlist.GetEnergy();
	
	if (base % rate == 0)
		sunlist.Add();
}

void GameEvent() {
	AddZombie();
	
	InspectAlive();
	//僵尸的一些活动
	zombielist.Move();
	flyzombielist.Move();
	firezombielist.Move();
	firezombielist.Fire();
	firezombielist.MoveBullets();
	ffzombielist.Move();
	ffzombielist.Fire();
	
	//植物的一些活动
	dominatorlist.Summon();
	FireBullet();
	AddEnergy();
	sunlist.Move();
}