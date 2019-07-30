#include "app.h"
#include "task_list.h"
#include "Adafruit_ssd1306syp.h"
#include "message.h"
#include "timer.h"
#include "app_dbg.h"

#include "flynshoot_ship.h"
#include "flynshoot_missile.h"
#include "flynshoot_mines.h"
#include "flynshoot_display.h"
#include "flynshoot_game_control.h"

// prototype
void spawnMissile(void);
void clearMissile(void);
void renderMissile(void);
bool MISSILE_HIT_TUNNEL(void);
bool MISSILE_HIT_MINE(void);

uint8_t missile_bmp[MISSILE_LENGTH];
uint8_t missileX, missileY;
uint8_t score;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_MISSILE_ARMED): {
			APP_DBG_SIG("AC_MISSILE_ARMED \n");
			spawnMissile();
		}
			break;

		case(AC_MISSILE_FLYING): {
			xprintf("missileX in FLYING: %d\n", missileX);
			xprintf("missileY in FLYING: %d\n", missileY);
			APP_DBG_SIG("AC_MISSILE_FLYING \n");
			if(missileX < tunnelWidth) {
				missileX += MISSILE_SPEED_X;
				renderMissile();
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_FLYING);
			}

			else if (MISSILE_HIT_MINE()) {
				score++;
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else if  (MISSILE_HIT_TUNNEL()) {
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else {
				screenObj.clear();
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			}
		}
			break;

		case(AC_MISSILE_EXPLODING) : {
			APP_DBG_SIG("AC_MISSILE_EXPLODING \n");
			task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			break;
		}

		default:
			break;
	}
}

void spawnMissile(void){
	missileX = 0;
	missileY = 30;
}


void renderMissile (void) {
	screenObj.fillRect(missileX, missileY, MISSILE_LENGTH, 2, WHITE);
	screenObj.update();
}

bool MISSILE_HIT_TUNNEL (void) {
	// TODO: check if missile hits tunnel
	// return true if yes, otw false
	return false;
}

bool MISSILE_HIT_MINE(void) {
	// TODO: check if missile hits mine
	// return true if yes, otw false
	return false;
}

