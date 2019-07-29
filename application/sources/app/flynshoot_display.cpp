#include "flynshoot_display.h"
#include "Adafruit_ssd1306syp.h"
#include "app.h"
#include "task_list.h"

Adafruit_ssd1306syp screenObj;
void task_control_display(ak_msg_t* msg) {
	switch (msg->sig) {
		case AC_FLYNSHOOT_INIT:
		{
			screenObj.initialize();
			screenObj.clear();
			screenObj.print("test");
		}
	}
}
