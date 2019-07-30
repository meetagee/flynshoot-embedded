#ifndef FLYNSHOOT_DISPLAY_H
#define FLYNSHOOT_DISPLAY_H

#include "Adafruit_ssd1306syp.h"

#define tunnelHeight 5
#define tunnelWidth 80

extern Adafruit_ssd1306syp screenObj;
extern int topTunnel[tunnelWidth];
extern int botTunnel[tunnelWidth];

#endif // FLYNSHOOT_DISPLAY_H
