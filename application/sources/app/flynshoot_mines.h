#ifndef __FLYNSHOOT_MINES_H__
#define __FLYNSHOOT_MINES_H__

#include <stdint.h>

#define NUM_MINES 3
#define mineHeight 8
#define mineWidth 8
#define MINE_SPEED_X 2
#define MINE_MIN_DIST_X 5

typedef struct {
	int8_t x, y;
	bool available;
} coord_t;

extern coord_t mines_coords[NUM_MINES];

#endif // FLYNSHOOT_MINES_H
