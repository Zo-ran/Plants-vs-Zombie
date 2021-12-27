#include"MouseEvent.h"
#include<math.h>
#include<graphics.h>
#include"MapPlants.h"
#include"AllPlants.h"

ExMessage msg;
bool pick = false;
Plants plants = vacant;
extern Plants MapPlants[5][10];

double dist(double x1, double y1, double x2, double y2)
{
	double result;
	result = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return result;
}

void MouseEvent() {
	
	if (MouseHit()) {
		msg = getmessage(EM_MOUSE);
		
		if (msg.message == WM_LBUTTONDOWN && sunlist.Clicked(msg.x, msg.y)) 
			return ;

		if (msg.message == WM_LBUTTONDOWN && !pick) {
			
			pick = true;
			
			if (msg.x >= 60 && msg.x <= 120 && msg.y >= 0 && msg.y <= 80) {
				plants = sunflower; 
			}
			
			else if (msg.x >= 120 && msg.x <= 180 && msg.y >= 0 && msg.y <= 80) {
				plants = shooter; 
			}
			
			else if (msg.x >= 180 && msg.x <= 240 && msg.y >= 0 && msg.y <= 80) {
				plants = stone; 
			}
			
			else if (msg.x >= 240 && msg.x <= 300 && msg.y >= 0 && msg.y <= 80) {
				plants = highshooter;
			}

			else if (msg.x >= 300 && msg.x <= 360 && msg.y >= 0 && msg.y <= 80) {
				plants = thorns;
			}

			else if (msg.x >= 360 && msg.x <= 420 && msg.y >= 0 && msg.y <= 80) {
				plants = dominator;
			}

			else if (msg.x >= 420 && msg.x <= 480 && msg.y >= 0 && msg.y <= 80) {
				plants = spikeweed;
			}

			else if (msg.x >= 540 && msg.x <= 600 && msg.y >= 0 && msg.y <= 80) {
				plants = spade;
			}

			else{
				pick = false;
			}
		}
		
		else if (msg.message == WM_LBUTTONDOWN && pick) {
			if (msg.x > 0 && msg.x < 480 && msg.y > 0 && msg.y < 80) {
				pick = false;
				return;
			}
			int TotalEnergy = sunlist.TotalEnergy;
			switch (plants) {
				case sunflower:{
					if (TotalEnergy >= 50 && sunflowerlist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 50;
					}
					break;
				}
				
				case stone: {
					if (TotalEnergy >= 100 && stonelist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 100;
					}
					break;
				}

				case shooter: {
					if (TotalEnergy >= 100 && shooterlist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 100;
					}
					break;
				}

				case highshooter: {
					if (TotalEnergy >= 150 && highshooterlist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 150; 
					}
					break;
				}

				case thorns: {
					if (TotalEnergy >= 300 && thornslist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 300;
					}
					break;
				}

				case dominator: {
					if (TotalEnergy >= 500 && dominatorlist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 500;
					}
					break;
				}

				case spikeweed: {
					if (TotalEnergy >= 200 && spkwdlist.Add(msg.x, msg.y)) {
						pick = false;
						sunlist.TotalEnergy -= 200;
					}
					break;
				}

				case spade: {
					pick = false;
					int col = msg.x / 60, row = msg.y / 80 - 1;
					if (col >= 0 && col <= 9 && row >= 0 && row <= 4) {
						switch (MapPlants[row][col]) {
						    case sunflower: {
								sunflowerlist.Hurt(row, col, 100000);
								break;
							} case shooter: {
								shooterlist.Hurt(row, col, 100000);
								break;
							} case stone: {
								stonelist.Hurt(row, col, 100000);
								break;
							} case dominator: {
								dominatorlist.Hurt(row, col, 100000);
								break;
							} case highshooter: {
								highshooterlist.Hurt(row, col, 100000);
								break;
							} case thorns: {
								thornslist.Hurt(row, col, 100000);
								break;
							} case spikeweed: {
								spkwdlist.Hurt(row, col, 100000);
								break;
							}
						}
					}
					break;
				}
			}
		}
	}
}