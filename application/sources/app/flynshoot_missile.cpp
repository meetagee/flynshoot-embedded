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

uint8_t missileX, missileY;
static bool draw = false;
static bool endOfLine = false;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {

		case(AC_MISSILE_ARMED): {
			//APP_DBG_SIG("Nothing happenning \n");
		}
			break;

		case(AC_MISSILE_FLYING): {
			if(draw == false) spawnMissile();
			//APP_DBG_SIG("AC_MISSILE_FLYING \n");
			if(missileX + MISSILE_SPEED_X < tunnelWidth && !MISSILE_HIT_MINE() && !MISSILE_HIT_TUNNEL()) {
				renderMissile();
				draw = true;
				timer_set(AC_MISSILE_ID, AC_MISSILE_FLYING, 50, TIMER_PERIODIC);
			}

			else if (missileX + MISSILE_SPEED_X < tunnelWidth && MISSILE_HIT_MINE()) {
				//APP_DBG_SIG("HIT MINE!\n");
<<<<<<< HEAD
				clearMissile();
=======
				score++;
>>>>>>> 1d25cb54f34393628adee34fe1a1b152987fec54
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else if (missileX + MISSILE_SPEED_X < tunnelWidth && MISSILE_HIT_TUNNEL()) {
				//APP_DBG_SIG("HIT TUNNEl!\n");
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else {
				clearMissile();
				timer_remove_attr(AC_MISSILE_ID, AC_MISSILE_FLYING);
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			}
		}
			break;

		case(AC_MISSILE_EXPLODING) : {
			//APP_DBG_SIG("AC_MISSILE_EXPLODING \n");
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
	missileY = shipy + shipHeight + 2;
}


void renderMissile (void) {
	missileX += MISSILE_SPEED_X;
	if(!draw && !endOfLine) {
		screenObj.fillRect(missileX, missileY, MISSILE_LENGTH, MISSILE_WIDTH, WHITE);
	}
	else if (endOfLine) {
		screenObj.fillRect(missileX- MISSILE_SPEED_X, missileY, MISSILE_LENGTH, MISSILE_WIDTH, BLACK);
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
	draw = false;
}

bool MISSILE_HIT_TUNNEL (void) {
	// TODO: check if missile hits tunnel
	// return true if yes, otw false
	if(checkTunnelOverlap(missileX + MISSILE_LENGTH, missileY) || checkTunnelOverlap(missileX + MISSILE_LENGTH, missileY + MISSILE_WIDTH - 1)) {
		//APP_DBG("MISSILE HITS TUNNEL\n");
		return true;
	}
	return false;
}

bool MISSILE_HIT_MINE(void) {
	// TODO: check if missile hits mine
	// return true if yes, otw false
	for(int i = 0; i < NUM_MINES; i++) {
		if(		(missileX + MISSILE_LENGTH >= mines_coords[i].x && missileX + MISSILE_LENGTH <= mines_coords[i].x + mineWidth)
				&& ((missileY >= mines_coords[i].y && missileY <= mines_coords[i].y + mineHeight - 1)|| (missileY + MISSILE_WIDTH - 1 >= mines_coords[i].y && missileY + MISSILE_WIDTH - 1 <= mines_coords[i].y + mineHeight - 1))
				&& (mines_coords[i].available == true)) {
			//APP_DBG_SIG("MINE HIT: %d, MINE COORD: (%d, %d) - MISSILE COORD: (%d, %d)\n", i, mines_coords[i].x, mines_coords[i].y, missileX, missileY);
			//APP_DBG("***********************************\n");
			screenObj.drawSun(mines_coords[i].x, mines_coords[i].y, mineWidth, BLACK);
			mines_coords[i].x = INT8_MAX;
			mines_coords[i].y = INT8_MAX;
			mines_coords[i].available = false;
			return true;
		}
	}
	return false;
}

