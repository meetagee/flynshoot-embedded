#include "flynshoot_ship.h"
#include "task_list.h"
#include "app.h"

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
	default:
		break;
	}
}

