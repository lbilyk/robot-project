#include "main.h"
static void TIM_Config(void);
extern void systemInit();

int main(void)
{
	int speed = 8;
	int direction = 0;
	
	motorInit();
	motorControl(speed,direction);
	
}