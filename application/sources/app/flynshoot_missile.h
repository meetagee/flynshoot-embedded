#ifndef __FLYNSHOOT_MISSILE_H__
#define __FLYNSHOOT_MISSILE_H__

#include <stdint.h>

#define MISSILE_SPEED_X	5
#define MISSILE_LENGTH	5
#define MISSILE_WIDTH	2

extern uint8_t missile_bmp[MISSILE_LENGTH];
extern uint8_t missileX, missileY, score;

#endif // MISSILE_H
