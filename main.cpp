#include "main.h"
static void TIM_Config(void);
extern void systemInit();

int main(void)
{
	
	int speed = 9; //at least 7
	int direction =1; //forward:0 || reverse:1 || right:2 || left:3 || stop:4 
	
	motorInit();
 
		motorControl(speed, direction);
	

	
}
