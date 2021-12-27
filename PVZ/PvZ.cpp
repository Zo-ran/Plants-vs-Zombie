#include "DrawMap.h"
#include "MouseEvent.h"
#include "GameEvent.h"
#include "GameOver.h"
#include <graphics.h>
#include "GameInit.h"

int main() {
	initgraph(ScreenWidth, ScreenHight);

	while (1) {
		switch (GameInit()) {
			case GAME_START: {
				while (!GameOver()) {
					DrawMap();
					MouseEvent();
					GameEvent();
				}
				FILE_EVENT();
				while(OVER_UI());
				return 0;
			} case SHOW_SCOREBOARD: {
				while(ScoreBoard());
			}
		}
	}

}