#include "flynshoot_ship.h"
#include "task_list.h"
#include "app.h"

#define shipHeight 4
#define shipWidth 5

int ship[shipHeight][shipWidth] = {{1,0,0,0,0},
								   {1,1,0,0,0},
								   {1,1,1,1,1,},
								   {1,1,1,1,1,},};

int shipx;
int shipy;

void task_control_ship(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_SHIP_ACTIVE): {

		}
			break;
	}
}

//int* getShipCoordinates() {
//	int ans[2];
//	ans[0] = shipx;
//	ans[1] = shipy;
//	return ans;
//}
