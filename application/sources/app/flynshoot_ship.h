#ifndef __FLYNSHOOT_SHIP_H__
#define __FLYNSHOOT_SHIP_H__

//int* getShipCoordinates()
#include <stdint.h>

#define shipHeight 4
#define shipWidth 5

extern uint8_t ship[shipHeight][shipWidth];
extern uint8_t shipx, shipy;

extern void drawShip();
extern void checkDeath();
#endif // FLYNSHOOT_SHIP_H
