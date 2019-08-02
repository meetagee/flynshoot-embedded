#include "flynshoot_ship.h"
#include "task_list.h"
#include "app.h"

#include "flynshoot_display.h"

uint8_t ship[shipHeight][shipWidth] = {{1,0,0,0,0},
									   {1,1,0,0,0},
									   {1,1,1,1,0,},
									   {1,1,1,1,1,},
									  };

uint8_t shipx;
uint8_t shipy;

void drawShip();
static void updateShipUp();
static void updateShipDown();

void task_control_ship(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_SHIP_PARKED): {
			shipx = 10;
			shipy = 30;
			task_post_pure_msg(AC_SHIP_ID,AC_SHIP_ACTIVE);
		}
			break;
		case(AC_SHIP_ACTIVE): {
			screenObj.setCursor(85,15);
			screenObj.print("ship");
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
				if(checkTunnelOverlap(shipx + 2*i, (shipy + 2*j)+2))
				{
					screenObj.setCursor(85,25);
					screenObj.print("overlap");
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
//	for(uint8_t j = 0; j < shipHeight; j++)
//	{
//		for(uint8_t i = 0; i < shipWidth; i++)
//		{
//			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,BLACK);
//		}
//	}
	shipy+=2;
	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) {
				//screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
				screenObj.fillRect(shipx+2*i,(shipy-2)+2*j,2,2,BLACK);
			}
		}
	}
	//screenObj.update();
}

static void updateShipDown()
{
//	for(uint8_t j = 0; j < shipHeight; j++)
//	{
//		for(uint8_t i = 0; i < shipWidth; i++)
//		{
//			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,BLACK);
//		}
//	}
	shipy-=2;

	for(uint8_t j = 0; j < shipHeight; j++)
	{
		for(uint8_t i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) {
				//screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
				screenObj.fillRect(shipx+2*i,(shipy+2)+2*j,2,2,BLACK);
			}
		}
	}
	//screenObj.update();
}

//int* getShipCoordinates() {
//	int ans[2];
//	ans[0] = shipx;
//	ans[1] = shipy;
//	return ans;
//}
