#include"DrawMap.h"
#include"MapPlants.h"
#include"Bullet.h"
#include"AllZombie.h"
#include"AllPlants.h"

extern Plants MapPlants[5][10];
extern bool pick;
extern ExMessage msg;
extern Plants plants;
extern BulletList bulletlist;

void DrawThorns(double x, double y) {
	setfillcolor(ThornsColor);
	for (int i = 0; i < 5; i++) {
		POINT ptr[3] = { {x , y + i * 9}, {x, y + (i + 1) * 9}, {x + 20, y + i * 9 + 4.5} };
		solidpolygon(ptr, 3);
	}
}

void DrawSpkwd(double x, double y, int height) {
	setfillcolor(SpkwdColor);
	for (int i = 0; i < 5; i++) {
		POINT ptr[3] = { {x + i * 8, y}, {x + (i + 1) * 8, y}, {x + i * 8 + 4, y - height} };
		solidpolygon(ptr, 3);
	}
}

void DrawSpade(double x, double y) {
	setfillcolor(RGB(255, 127, 36));
	solidcircle(x, y, 7);
	setfillcolor(RGB(130, 100, 20));
	setfillcolor(RGB(255, 127, 36));
	solidrectangle(x - 2, y + 7, x + 2, y + 37);
	setfillcolor(RGB(156, 156, 156));
	solidpie(x - 15, y + 23, x + 15, y + 53, 3.14, 0);
}

void DrawDominator(double x, double y) {
	setfillcolor(RGB(255, 255, 0));
	solidrectangle(x, y, x + 40, y + 50);
	setlinecolor(RGB(155, 48, 255));
	setfillcolor(RGB(155, 48, 255));
	solidcircle(x + 20, y + 25, 17);
	setfillcolor(RGB(0, 0, 0));	
	fillcircle(x + 20, y + 25, 15);
}

void DrawMousePlants() {
	if (pick) {
		double x = msg.x;
		double y = msg.y;
		switch (plants) {
			case sunflower: {
				setfillcolor(SunFlowerColor);
				solidcircle(x, y, SunFlowerRadius);
				break;
			}

			case stone: {
				setfillcolor(StoneColor);
				solidellipse(x - 15, y - 22.5, x + 15, y + 22.5);
				break;
			}

			case shooter: {
				setfillcolor(ShooterColor);
				solidrectangle(x - 15, y - 15, x + 15, y + 15);
				break;
			}

			case highshooter: {
				setfillcolor(HighShooterColor);
				solidrectangle(x - 10, y - 20, x + 10, y + 20);
				break;
			}

			case thorns: {
				DrawThorns(x, y);
				break;
			}

			case dominator: {
				DrawDominator(x - 20, y - 25);
				break;
			}

			case spikeweed: {
				DrawSpkwd(x - 20, y, 10);
				break;
			}

			case spade: {
				DrawSpade(x, y - 30);
				break;
			}
		}
	}
}

void ChangeEnergy() {
	char text[5] = "\0";
	settextstyle(17, 0, L"宋体");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfillcolor(SunFlowerColor);
	solidcircle(30, 30, SunFlowerRadius + 5);
	RECT rect = { 12, 55, 52, 75 };
	TCHAR s[5];
	swprintf(s, _T("%d"), sunlist.TotalEnergy);
	drawtext(s, &rect, DT_WORDBREAK);
}

void DrawMap() {
	BeginBatchDraw();
	
	HRGN rgn = CreateRectRgn(0, SquareHight, ScreenWidth, ScreenHight);  
	setcliprgn(rgn);
	DeleteObject(rgn);

	setfillcolor(RGB(0, 205, 0)); //最深的绿色
	for (int i = 0; i < 3; i++)	//1, 3, 5行，1，3, 5，7列				
		for (int j = 0; j < 6; j++) {
			solidrectangle(j * (2 * SquareWidth), SquareHight + i * (2 * SquareHight), 
				j * (2 * SquareWidth) + SquareWidth, SquareHight * 2 + i * (2 * SquareHight));
		}
	
	setfillcolor(RGB(0, 238, 0));
	for (int i = 0; i < 3; i++)	
		for (int j = 0; j < 6; j++) {
			solidrectangle(SquareWidth + j * (2 * SquareWidth), SquareHight + i * (2 * SquareHight), 
				j * (2 * SquareWidth) + 2 * SquareWidth, SquareHight * 2 + i * (2 * SquareHight));
		}

	setfillcolor(RGB(0, 255, 0));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6; j++) {
			solidrectangle(j * (2 * SquareWidth), SquareHight * 2 + i * (2 * SquareHight),
				j * (2 * SquareWidth) + SquareWidth, 3 * SquareHight + i * (2 * SquareHight));
		}
	
	setfillcolor(RGB(0, 205, 0));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6; j++) {
			solidrectangle(SquareWidth + j * (2 * SquareWidth), SquareHight * 2 + i * (2 * SquareHight),
				j * (2 * SquareWidth) + 2 * SquareWidth, 3 * SquareHight + i * (2 * SquareHight));
		}
	
	rgn = CreateRectRgn(0, 0, ScreenWidth, SquareHight);
	setfillcolor(RGB(205, 133, 0));
	setcliprgn(rgn);
	DeleteObject(rgn);
	for (int i = 0; i < 6; i++) {
		solidrectangle(i * SquareWidth * 2, 0, SquareWidth + i * SquareWidth * 2, SquareHight);
	}
	setfillcolor(RGB(130, 100, 20));
	for (int i = 0; i < 6; i++) {
		solidrectangle(SquareWidth + i * SquareWidth * 2, 0, 2 * SquareWidth + i * SquareWidth * 2, SquareHight);
	}
	
	setfillcolor(SunFlowerColor);    //绘制向日葵
	solidcircle(90, 30, 15);
	settextstyle(12, 0, L"宋体");
	outtextxy(71, 55, _T("向日葵"));
	outtextxy(85, 68, _T("50"));

	setfillcolor(ShooterColor);
	solidrectangle(135, 15, 165, 45);
	outtextxy(138, 55, L"射手"); 
	outtextxy(140, 68, _T("100"));

	setfillcolor(StoneColor);
	solidellipse(195, 8, 225, 53);
	outtextxy(198, 55, L"石块");
	outtextxy(200, 68, _T("100"));

	setfillcolor(HighShooterColor);
	solidrectangle(260, 10, 280, 50);
	outtextxy(253, 55, _T("高射手"));
	outtextxy(260, 68, _T("150"));

	DrawThorns(320, 10);
	outtextxy(305, 55, _T("nju铁丝网"));
	outtextxy(320, 68, _T("300"));

	DrawDominator(370, 5);
	outtextxy(365, 57, _T("dominator"));
	outtextxy(382, 68, _T("500"));

	DrawSpkwd(430, 50, 10);
	outtextxy(438, 55, _T("地刺"));
	outtextxy(442, 68, _T("200"));

	DrawSpade(570, 15);

	rgn = CreateRectRgn(0, 0, ScreenWidth, ScreenHight);
	setcliprgn(rgn);
	DeleteObject(rgn);
	
	//画地图
	DrawMousePlants();
	ChangeEnergy();
	sunlist.Draw();
	
	//画子弹
	bulletlist.Draw();
	highshooterlist.DrawBullet();
	ffzombielist.DrawBlt();

	//画僵尸
	flyzombielist.Draw();                        
	zombielist.Draw();
	firezombielist.Draw();
	ffzombielist.Draw();
	
	//画血条
	sunflowerlist.DrawBloodStrip(5000);            
	stonelist.DrawBloodStrip(30000);
	shooterlist.DrawBloodStrip(5000);
	highshooterlist.DrawBloodStrip(5000);
	thornslist.DrawBloodStrip(20000);
	dominatorlist.DrawBloodStrip(1);
	spkwdlist.DrawBloodStrip(100);

	EndBatchDraw();
}
