#include "flynshoot_missile.h"
#include "flynshoot_mines.h"
#include "app.h"
#include "task_list.h"
#include "Adafruit_ssd1306syp.h"
#include "message.h"
#include "timer.h"
#include "flynshoot_ship.h"

// prototype
void spawnMissile(uint8_t shipX, uint8_t shipY);

uint8_t missile_bmp[MISSILE_LENGTH] = {1 ,1 ,1 ,1 ,1};
uint8_t missileX, missileY;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_MISSILE_ARMED): {

		}
			break;

		case(AC_MISSILE_FLYING): {

			}

			break;

		case(AC_MISSILE_EXPLODING) : {

		}
			break;
	}
}


void spawnMissile(uint8_t shipX, uint8_t shipY){
	missileX = shipX;
	missileY = shipY;
}
