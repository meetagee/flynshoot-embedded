#include "flynshoot_missile.h"
#include "activeobj.h"
#include "app.h"
#include "task_list.h"

static activeObj_t missile;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
	case(AC_MISSILE_ARMED): {
		uint8_t* tmp[] = get_common_msg(/* Fill in here */);
		task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_FIRE);
	}
		break;

	case(AC_MISSILE_FLYING): {

	}
		break;

	default:
		break;
	}
}
