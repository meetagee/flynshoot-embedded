#include "flynshoot_missile.h"
#include "flynshoot_mines.h"
#include "app.h"
#include "task_list.h"
#include "Adafruit_ssd1306syp.h"
#include "message.h"
#include "timer.h"

activeObj_t* missile;
bool HIT_MINE(void);

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
	case(AC_MISSILE_ARMED): {
		missile = (activeObj_t*) get_data_common_msg(msg);
		task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_FLYING);
	}
		break;

	case(AC_MISSILE_FLYING): {
		if(missile->x + MISSILE_SPEED_X < SSD1306_WIDTH) {
			missile->x += MISSILE_SPEED_X;
			task_post_common_msg(/* Display ID */, /* Display sig */, (uint8_t*) missile, sizeof(activeObj_t));
		}

		else if (HIT_MINE(missile)) {
			timer_set(AC_MINES_ID, AC_MINES_EXPLODING, /* Time */, TIMER_ONE_SHOT);
		}

		else if (/* HIT_TUNNEL handle */) {
			timer_set(AC_MISSILE_ID, AC_MISSILE_EXPLODING, /* Time */, TIMER_ONE_SHOT);
		}

		else {

		}
	}
		break;

	case(AC_MISSILE_EXPLODING) : {

	}
		break;

	default:
		break;
	}
}


