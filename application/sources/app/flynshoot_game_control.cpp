#include "flynshoot_game_control.h"
#include "task_list.h"
#include "app.h"
#include "timer.h"

void task_control_game(ak_msg_t* msg) {
	switch(msg->sig) {
	case(AC_GAME_CONTROL_UPDATE): {
		timer_set(AC_SHIP_ID, AC_SHIP_ACTIVE, DEFAULT_TIME_TICK, TIMER_PERIODIC);
		timer_set(AC_MISSILE_ID, AC_MISSILE_ARMED, DEFAULT_TIME_TICK, TIMER_PERIODIC);
		//timer_set(/* Display goes here */);
	}
		break;
	}
}
