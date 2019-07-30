#include "flynshoot_ship.h"
#include "task_list.h"
#include "app.h"

#include "flynshoot_display.h"

int ship[shipHeight][shipWidth] = {{1,0,0,0,0},
								   {1,1,0,0,0},
								   {1,1,1,1,0,},
								   {1,1,1,1,1,},};

int shipx;
int shipy;
static void drawShip();
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

static void drawShip(){
	for(int j = 0; j < shipHeight; j++)
	{
		for(int i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
		}
	}
	screenObj.update();
}

static void updateShipUp()
{
	for(int j = 0; j < shipHeight; j++)
	{
		for(int i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,BLACK);
		}
	}
	shipy+=2;
	for(int j = 0; j < shipHeight; j++)
	{
		for(int i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
		}
	}
	screenObj.update();
}

static void updateShipDown()
{
	for(int j = 0; j < shipHeight; j++)
	{
		for(int i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,BLACK);
		}
	}
	shipy-=2;
	for(int j = 0; j < shipHeight; j++)
	{
		for(int i = 0; i < shipWidth; i++)
		{
			if(ship[j][i] == 1) screenObj.fillRect(shipx+2*i,shipy+2*j,2,2,WHITE);
		}
	}
	screenObj.update();
}

//int* getShipCoordinates() {
//	int ans[2];
//	ans[0] = shipx;
//	ans[1] = shipy;
//	return ans;
//}
