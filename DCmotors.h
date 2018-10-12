
#include "stm32f30x.h"
#include "pwmInit.h"
void motorInit();
int motorControl(int speed,int dir);

typedef struct Motors{
	int forward[2] = {0x2,0x1};
	int backward[2] ={0x1, 0x2};
	int right[2]= {0x1,0x1};
	int left[2] ={0x2,0x2};
	int stop[2] = {0x0,0x0};
} Direction;
	