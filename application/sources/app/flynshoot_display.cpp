#include "flynshoot_display.h"
#include "Adafruit_ssd1306syp.h"
#include "app.h"
#include "task_list.h"

#define tunnelHeight 5
#define tunnelWidth 80

#define screenSize 80

int topTunnel[tunnelWidth] = {0};
int botTunnel[tunnelWidth] = {0};
Adafruit_ssd1306syp screenObj;
void task_control_display(ak_msg_t* msg) {
	switch (msg->sig) {
		case AC_FLYNSHOOT_INIT:
		{
			topTunnel[tunnelWidth] = {0};
			botTunnel[tunnelWidth] = {0};
			screenObj.initialize();
			screenObj.clear();
			screenObj.print("test");
		}
	}
}

void updateTunnel(){
	for(int j = 0; j < tunnelWidth-1; j++)
	{
		topTunnel[i] = topTunnel[i+1];
		botTunnel[i] = botTunnel[i+1];
	}
	int topOldBlocks = topTunnel[tunnelWidth-1];
	int botOldBlocks = botTunnel[tunnelWidth-1];
	int topNewBlocks = topOldBlocks + (rand()%1);
	int botNewBlocks = botOldBlocks + (rand()%1);

	if(topNewBlocks > tunnelHeight) topNewBlocks--;
	if(botNewBlocks > tunnelHeight) topNewBlocks--;

	topTunnel[tunnelWidth] = topNewBlocks;
	botTunnel[tunnelWidth] = topOldBlocks;
}

bool checkTunnelOverlap(int x, int y)
{
	if(y<=5)
	{
		int sizeTunnel = topTunnel[x];
		if(sizeTunnel >= y) return true;
	}


	if(y>=55)
	{
		int sizeTunnel = botTunnel[x];
		if(sizeTunnel >= 60-y) return true;
	}
	return false;
}
