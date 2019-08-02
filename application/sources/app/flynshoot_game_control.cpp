#include "flynshoot_game_control.h"
#include "task_list.h"
#include "app.h"
#include "timer.h"
#include "flynshoot_display.h"


void task_control_game(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_GAME_CONTROL_UPDATE): {
	//		timer_set(AC_SHIP_ID, AC_SHIP_ACTIVE, DEFAULT_TIME_TICK, TIMER_PERIODIC);
			//task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
//			task_post_pure_msg(AC_MINES_ID, AC_MINES_INIT);
			timer_set(AC_DISPLAY_ID,AC_FLYNSHOOT_UPDATE_TUNNEL,50,TIMER_PERIODIC);
		}
		break;
		case(AC_GAME_CONTROL_OVER): {
	//		timer_set(AC_SHIP_ID, AC_SHIP_ACTIVE, DEFAULT_TIME_TICK, TIMER_PERIODIC);
			//task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
	//			task_post_pure_msg(AC_MINES_ID, AC_MINES_INIT);
			timer_remove_attr(AC_DISPLAY_ID,AC_FLYNSHOOT_UPDATE_TUNNEL);
			screenObj.clear();
			screenObj.setCursor(30,20);
			screenObj.print("Game Over");
			screenObj.setCursor(25,35);
			screenObj.print("Score: ");
			screenObj.print(score);
			screenObj.update();
		}
		break;
	}
}
