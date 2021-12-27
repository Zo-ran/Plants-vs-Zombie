#pragma once
#include "DrawMap.h"
typedef enum {
	GAME_START,
	SHOW_SCOREBOARD,
	NONE
} EVENT;

EVENT GameInit();

bool ScoreBoard();

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);