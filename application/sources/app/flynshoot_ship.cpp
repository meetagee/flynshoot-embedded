#include "task_list.h"
#include "app.h"
#include "app_dbg.h"

#include "flynshoot_mines.h"
#include "flynshoot_display.h"
#include "flynshoot_ship.h"

uint8_t ship[shipHeight][shipWidth] = {{1,0,0,0,0},
									   {1,1,0,0,0},
									   {1,1,1,1,0},
									   {1,1,1,1,1},
									  };

uint8_t shipx;
uint8_t shipy;
bool gameOver;

void drawShip();
static void updateShipUp();
static void updateShipDown();
static bool SHIP_HITS_MINE(void);

void task_control_ship(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_SHIP_PARKED): {
			gameOver = false;
			shipx = 10;
			shipy = 30;
			task_post_pure_msg(AC_SHIP_ID,AC_SHIP_ACTIVE);
		}
			break;
		case(AC_SHIP_ACTIVE): {
			drawShip();
			task_post_pure_msg(AC_SHIP_ID,AC_SHIP_FLYING);
		}
			break;
		case(AC_SHIP_FLYING): {

		}
			break;
		case(AC_SHIP_UP): {
			updateShipUp();
			task_post_pure_msg(AC_SHIP_ID,AC_SHIP_FLYING);
		}
			break;
		case(AC_SHIP_DOWN): {
			updateShipDown();
			task_post_pure_msg(AC_SHIP_ID,AC_SHIP_FLYING);
		}
			break;
	}
}
void checkDeath()
{
	screenObj.fillRect(85,25,50,10,BLACK);
	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1)
			{
				if(checkTunnelOverlap(shipx + 2*i, (shipy + 2*j)+2) || SHIP_HITS_MINE())
				{
					gameOver = true;
					task_post_pure_msg(AC_GAME_CONTROL_ID,AC_GAME_CONTROL_OVER);
				}
			}
		}
	}
}
void drawShip(){
	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
		}
	}
	screenObj.update();
}

static void updateShipUp()
{
	shipy+=2;
	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) {
				screenObj.fillRect(shipx+2*i,(shipy-2)+2*j,2,2,BLACK);
			}
		}
	}
}

static void updateShipDown()
{
	shipy-=2;

	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) {
				screenObj.fillRect(shipx+2*i,(shipy+2)+2*j,2,2,BLACK);
			}
		}
	}
}

static bool SHIP_HITS_MINE(void) {
	for(uint8_t i = 0; i < NUM_MINES; i++) {
		if(mines_coords[i].x > 0) {
			// head on collision
			if ((shipx + 2*shipWidth - 1>= mines_coords[i].x && shipx + 2*shipWidth - 1<= mines_coords[i].x + mineWidth - 1)
					&& (shipy + 2*shipHeight - 1 >= mines_coords[i].y && shipy + 2*shipHeight - 1 <= mines_coords[i].y + mineHeight - 1)) {
				//APP_DBG("HEAD ON: SHIP(%d, %d), MINE(%d, %d)\n", shipx, shipy, mines_coords[i].x, mines_coords[i].y);
				return true;
			}
			// upper collision
			if ((shipx  >= mines_coords[i].x && shipx <= mines_coords[i].x + mineWidth - 1)
					 && (shipy <= mines_coords[i].y + mineHeight - 1) && shipy >= mines_coords[i].y) {
				//APP_DBG("UPPER HIT: SHIP(%d, %d), MINE(%d, %d)\n", shipx, shipy, mines_coords[i].x, mines_coords[i].y);
				return true;
			}
			// lower collision
			if (	  ((shipx  >= mines_coords[i].x && shipx <= mines_coords[i].x + mineWidth - 1)
					|| (shipx + 2 >= mines_coords[i].x && shipx + 2 <= mines_coords[i].x + mineWidth - 1)
					|| (shipx + 4 >= mines_coords[i].x && shipx + 4 <= mines_coords[i].x + mineWidth - 1)
					|| (shipx + 6 >= mines_coords[i].x && shipx + 6 <= mines_coords[i].x + mineWidth - 1)
					|| (shipx + 8 >= mines_coords[i].x && shipx + 8 <= mines_coords[i].x + mineWidth - 1))
					&& (shipy + 2*shipHeight - 1 >= mines_coords[i].y && shipy + 2*shipHeight - 1<= mines_coords[i].y + mineHeight - 1)) {
				//APP_DBG("LOWER HIT: SHIP(%d, %d), MINE(%d, %d)\n", shipx, shipy, mines_coords[i].x, mines_coords[i].y);
				return true;
			}
		}
	}
	return false;
}
