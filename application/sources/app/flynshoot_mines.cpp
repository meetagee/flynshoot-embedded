#include "flynshoot_mines.h"
#include "app.h"
#include "task_list.h"

// prototype
bool MISSILE_HIT_MINE(void);

int mine[mineHeight][mineWidth] = {{0,1,1,0},
								   {1,1,1,1},
								   {1,1,1,1,},
								   {0,1,1,0,},};

void task_control_mines(ak_msg_t* msg) {
	switch(msg->sig) {


	}
}

bool MISSILE_HIT_MINE(void) {
	// TODO: check if missile hits mine
	// return true if yes, otw false
}
