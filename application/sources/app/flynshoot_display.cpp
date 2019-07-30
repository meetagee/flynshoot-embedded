#include "flynshoot_display.h"
#include "app.h"
#include "task_list.h"
#include "app_dbg.h"

int topTunnel[tunnelWidth];
int botTunnel[tunnelWidth];

Adafruit_ssd1306syp screenObj;

static void drawTunnel();
static void updateTunnel();

bool MISSILE_HIT_TUNNEL (void);

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
			screenObj.update();
			task_post_pure_msg(AC_DISPLAY_ID,AC_FLYNSHOOT_DRAW_TUNNEL);
		}
		break;
		case AC_FLYNSHOOT_DRAW_TUNNEL:
		{
			screenObj.setCursor(85,5);
			screenObj.print("display");
			drawTunnel();
		}
		break;

		case AC_FLYNSHOOT_UPDATE_TUNNEL:
		{
			APP_DBG("UPDATE TUNNEL \n");
			updateTunnel();
			task_post_pure_msg(AC_DISPLAY_ID,AC_FLYNSHOOT_DRAW_TUNNEL);
		}
		break;
	}
}

static void updateTunnel(){
	for(int i = 0; i < tunnelWidth-1; i++)
	{
		topTunnel[i] = topTunnel[i+1];
		botTunnel[i] = botTunnel[i+1];
	}
	int topOldBlocks = topTunnel[tunnelWidth-2];
	int botOldBlocks = botTunnel[tunnelWidth-2];
	int topNewBlocks = topOldBlocks + ((rand()%3)-1);
	int botNewBlocks = botOldBlocks + ((rand()%3)-1);

	if(topNewBlocks > tunnelHeight) topNewBlocks--;
	if(botNewBlocks > tunnelHeight) botNewBlocks--;
	if(topNewBlocks < 0) topNewBlocks=0;
	if(botNewBlocks < 0) botNewBlocks=0;
	topTunnel[tunnelWidth-1] = topNewBlocks;
	botTunnel[tunnelWidth-1] = botNewBlocks;
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

static void drawTunnel(){

	for(int i = 0; i < tunnelWidth; i++)
	{
		screenObj.fillRect(i,-1,1,10,BLACK);
		screenObj.fillRect(i,-1,1,2*topTunnel[i],WHITE);
	}
	for(int i = 0; i < tunnelWidth; i++)
	{
		screenObj.fillRect(i,60,1,-10,BLACK);
		screenObj.fillRect(i,60,1,2*-botTunnel[i],WHITE);
	}
	screenObj.update();
}
