#include "flynshoot_missile.h"
#include "app.h"
#include "task_list.h"

void missileInit (void);

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
	case(AC_MISSILE_ARMED): {
		uint8_t* tmpCoords[] = get_common_msg(/* Fill in here */);
		missileInit(tmpCoords);
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

void missileInit (uint8_t* coords[]) {
	activeObj_t tmp;
	tmp.x = *coords[0];
	tmp.y = *coords[1];
	missile.push_front(tmp);
}
