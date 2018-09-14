#include "main.h"


int main()
{
	SystemInit();
	SysTickInit();

	while(true)
	{
		LEDToggle();
		Delay(150);
	}
	
	return 0;
}