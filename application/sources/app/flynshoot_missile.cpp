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
void renderMissile(void);
void clearMissile(void);
bool MISSILE_HIT_TUNNEL(void);
bool MISSILE_HIT_MINE(void);

uint8_t missile_bmp[MISSILE_LENGTH];
uint8_t missileX, missileY;
uint8_t score;
static bool draw = false;
static bool endOfLine = false;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_MISSILE_ARMED): {
			APP_DBG_SIG("AC_MISSILE_ARMED \n");
			spawnMissile();
		}
			break;

		case(AC_MISSILE_FLYING): {
			APP_DBG_SIG("AC_MISSILE_FLYING \n");
			if(missileX + MISSILE_SPEED_X < tunnelWidth && !MISSILE_HIT_MINE() /*&& !MISSILE_HIT_TUNNEL()*/) {
				missileX += MISSILE_SPEED_X;
				renderMissile();
				draw = true;
				timer_set(AC_MISSILE_ID, AC_MISSILE_FLYING, 50, TIMER_PERIODIC);
			}

			else if (missileX + MISSILE_SPEED_X < tunnelWidth && MISSILE_HIT_MINE()) {
				APP_DBG_SIG("HIT MINE!\n");
				score++;
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

//			else if (missileX + MISSILE_SPEED_X < tunnelWidth && MISSILE_HIT_TUNNEL()) {
//				APP_DBG_SIG("HIT TUNNEl!\n");
//				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
//			}

			else {
				clearMissile();
				timer_remove_attr(AC_MISSILE_ID, AC_MISSILE_FLYING);
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			}
		}
			break;

		case(AC_MISSILE_EXPLODING) : {
			APP_DBG_SIG("AC_MISSILE_EXPLODING \n");
			clearMissile();
			timer_remove_attr(AC_MISSILE_ID, AC_MISSILE_FLYING);
			task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			break;
		}

		default:
			break;
	}
}

void spawnMissile(void){
	missileX = shipx + shipWidth;
	missileY = shipy + shipHeight - 1;
}


void renderMissile (void) {
	if(!draw) {
		screenObj.fillRect(missileX, missileY, MISSILE_LENGTH, MISSILE_WIDTH, WHITE);
	}
	else if (endOfLine) {
		screenObj.fillRect(missileX, missileY, MISSILE_LENGTH, MISSILE_WIDTH, BLACK);
	}
	else {
		screenObj.fillRect(missileX - MISSILE_SPEED_X, missileY, MISSILE_LENGTH, MISSILE_WIDTH, BLACK);
		screenObj.fillRect(missileX, missileY, MISSILE_LENGTH, MISSILE_WIDTH, WHITE);
	}
}

void clearMissile (void) {
	endOfLine = true;
	renderMissile();
	endOfLine= false;
}

bool MISSILE_HIT_TUNNEL (void) {
	// TODO: check if missile hits tunnel
	// return true if yes, otw false
	if(missileY <= topTunnel[missileX + MISSILE_LENGTH] || missileY + MISSILE_WIDTH - 1 >= botTunnel[missileX + MISSILE_LENGTH]) {
		return true;
	}
	return false;
}

bool MISSILE_HIT_MINE(void) {
	// TODO: check if missile hits mine
	// return true if yes, otw false
	for(uint8_t i = 0; i < NUM_MINES; i++) {
		if((missileX + MISSILE_LENGTH >= mines_coords[i].x - mineWidth +1) && ((missileY > mines_coords[i].y - mineHeight + 1 && missileY < mines_coords[i].y + mineHeight - 1)
				 || (missileY + MISSILE_WIDTH - 1 > mines_coords[i].y - mineHeight + 1 && missileY + MISSILE_WIDTH - 1 < mines_coords[i].y + mineHeight - 1))) {
			mines_coords[i].available = false;
			return true;
		}
	}
	return false;
}

