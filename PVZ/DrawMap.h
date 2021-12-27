#pragma once
#define ScreenWidth 600     
#define	ScreenHight 480
#define SquareWidth 60
#define SquareHight 80
#define SunFlowerColor RGB(255, 255, 0)
#define SunFlowerRadius 15
#define StoneColor RGB(190, 190, 190)
#define ShooterColor RGB(187, 255, 255)
#define HitColor RGB(255, 114, 86)
#define ZombieColor RGB(85, 107, 47)
#define FlyZombieColor RGB(0, 191, 255)
#define HighShooterColor RGB(160, 32, 240)
#define FFColor RGB(224, 102, 255)
#define SpkwdColor RGB(255, 250, 250)
#define ThornsColor RGB(139, 0, 0)
#include<graphics.h>

void DrawMap();
void DrawThorns(double x, double y);
void DrawDominator(double x, double y);
void DrawSpkwd(double x, double y, int height);