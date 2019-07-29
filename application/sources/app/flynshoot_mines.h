#ifndef __FLYNSHOOT_MINES_H__
#define __FLYNSHOOT_MINES_H__

#include "activeObj.h"

#define NUM_MINES 10

extern activeObj_t (*mines) [NUM_MINES];
extern bool HIT_MINE (activeObj_t* obj);

#endif // FLYNSHOOT_MINES_H
