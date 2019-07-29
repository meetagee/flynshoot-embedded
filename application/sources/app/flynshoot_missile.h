#ifndef __FLYNSHOOT_MISSILE_H__
#define __FLYNSHOOT_MISSILE_H__

#define MAX_LIST_SIZE	5

#include "activeObj.h"
#include <list>

extern std::list<activeObj_t> missile(MAX_LIST_SIZE);

#endif // MISSILE_H
