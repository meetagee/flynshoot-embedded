#include "flynshoot_mines.h"
#include "flynshoot_display.h"
#include "flynshoot_ship.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "timer.h"

coord_t	mines_coords[NUM_MINES];

// prototypes
void updateMines (void);
void renderMines (void);
void minesInit (void);
uint8_t minePassScr (void);

void task_control_mines(ak_msg_t* msg) {
	switch(msg->sig) {
	case AC_MINES_INIT: {
		minesInit();
		task_post_pure_msg(AC_MINES_ID, AC_MINES_ARMED);
	}
		break;

	case AC_MINES_ARMED: {
		updateMines();
		if(gameOver) {
			timer_remove_attr(AC_MINES_ID, AC_MINES_ARMED);
			task_post_pure_msg(AC_GAME_CONTROL_ID, AC_GAME_CONTROL_OVER);
		}
		task_post_pure_msg(AC_MINES_ID, AC_MINES_FLYING);
	}
		break;

	case AC_MINES_FLYING: {
		renderMines();
		timer_set(AC_MINES_ID, AC_MINES_ARMED, 50, TIMER_PERIODIC);
	}
		break;

	case AC_MINES_EXPLODING: {

	}
		break;

	default:
		break;
	}
}

uint8_t minePassScr (void) {
	for(uint8_t i = 0; i < NUM_MINES; i++) {
//		APP_DBG("Mine[%d] avai: %d, (%d, %d)\n", i, mines_coords[i].available, mines_coords[i].x, mines_coords[i].y);
		if(mines_coords[i].x + mineWidth < 0 || mines_coords[i].available == false) {
			return i;
		}
	}
//	APP_DBG("***********************************\n");
	return NUM_MINES;
}

void minesInit (void) {
	mines_coords[0].x = tunnelWidth + mineWidth - 2 /*((uint16_t)rand() % (tunnelWidth + 1))*/;
	mines_coords[0].y = (uint16_t)rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1) + TOP_TUNNEL_LOWEST;
	mines_coords[0].available = true;
	//APP_DBG("Mine[%d] avai: %d\n", 0, mines_coords[0].available);
	for(uint8_t i = 1; i < NUM_MINES; i++) {
		mines_coords[i].x = mines_coords[i-1].x + ((uint16_t)rand() % (tunnelWidth - MINE_MIN_DIST_X + 1)) + MINE_MIN_DIST_X;
		mines_coords[i].y = ((uint16_t)rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1)) + TOP_TUNNEL_LOWEST;
		mines_coords[i].available = true;
//		APP_DBG("Mine[%d] avai: %d\n", i, mines_coords[i].available);
	}
//	APP_DBG("DONE INIT \n");
//	APP_DBG("***********************************\n");
}

void renderMines (void) {
	for(uint8_t i = 0; i < NUM_MINES; i++) {
		mines_coords[i].x -= MINE_SPEED_X;
		if(mines_coords[i].available == true && mines_coords[i].x + mineWidth < tunnelWidth) {
			screenObj.drawSun(mines_coords[i].x + MINE_SPEED_X, mines_coords[i].y, mineWidth, BLACK);
			screenObj.drawSun(mines_coords[i].x, mines_coords[i].y, mineWidth, WHITE);
		}
		else {
			// Do nothing
		}
	}
}

void updateMines (void) {
	uint8_t mine_check = minePassScr();
//	APP_DBG("UPDATE MINES\n");
//	APP_DBG("mine_check = %d\n", mine_check);
//	APP_DBG("***********************************\n");
	if(mine_check < NUM_MINES) {
		mines_coords[mine_check].x = tunnelWidth + mineWidth - 2 + ((uint16_t)rand() % (tunnelWidth - MINE_MIN_DIST_X + 1)) + MINE_MIN_DIST_X;
		mines_coords[mine_check].y = ((uint16_t)rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1)) + TOP_TUNNEL_LOWEST;
		mines_coords[mine_check].available = true;
	}
}
