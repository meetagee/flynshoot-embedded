#include "flynshoot_mines.h"
#include "activeObj.h"
#include "app.h"
#include "task_list.h"

activeObj_t (*mines) [NUM_MINES];

void task_control_mines(ak_msg_t* msg) {

}

bool HIT_MINE(activeObj_t* obj) {
	for(int i = 0; i < NUM_MINES; i++) {
		if(obj->x == mines[i]->x && obj->y == mines[i]->y) {
			return true;
		}
	}
	return false;
}
