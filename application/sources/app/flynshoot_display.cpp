#include "flynshoot_display.h"
#include "Adafruit_ssd1306syp.h"
#include "app.h"
#include "task_list.h"

#define tunnelHeight 5
#define tunnelWidth 80


int topTunnel[tunnelWidth];
int botTunnel[tunnelWidth];
Adafruit_ssd1306syp screenObj;
void task_control_display(ak_msg_t* msg) {
	switch (msg->sig) {
		case AC_FLYNSHOOT_INIT:
		{
			for(int i = 0; i < tunnelWidth; i++)
			{
				topTunnel[i] = 0;
				botTunnel[i] = 0;
			}
			screenObj.initialize();
			screenObj.clear();
			screenObj.display_on();
			screenObj.print("test");
			screenObj.update();

		}
	}
}

void updateTunnel(){
	for(int i = 0; i < tunnelWidth-1; i++)
	{
		topTunnel[i] = topTunnel[i+1];
		botTunnel[i] = botTunnel[i+1];
	}
	int topOldBlocks = topTunnel[tunnelWidth-2];
	int botOldBlocks = botTunnel[tunnelWidth-2];
	int topNewBlocks = topOldBlocks + (rand()%1);
	int botNewBlocks = botOldBlocks + (rand()%1);

	if(topNewBlocks > tunnelHeight) topNewBlocks--;
	if(botNewBlocks > tunnelHeight) topNewBlocks--;

	topTunnel[tunnelWidth-1] = topNewBlocks;
	botTunnel[tunnelWidth-1] = topOldBlocks;
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
