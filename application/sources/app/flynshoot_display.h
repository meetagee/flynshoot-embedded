#ifndef FLYNSHOOT_DISPLAY_H
#define FLYNSHOOT_DISPLAY_H

#include "Adafruit_ssd1306syp.h"

#define tunnelHeight 5
#define tunnelWidth 80

extern Adafruit_ssd1306syp screenObj;

extern int topTunnel[tunnelWidth];
extern int botTunnel[tunnelWidth];

extern bool checkTunnelOverlap(uint8_t x, uint8_t y);
#endif // FLYNSHOOT_DISPLAY_H
