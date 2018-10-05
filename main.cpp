#include "main.h"
//static void TIM_Config(void);


int main(void)
{

	int speed =2; //at least 7
	int direction =4; //forward:0 || reverse:1 || right:2 || left:3 || stop:4 
		SysTickInit();
		motorInit();
	
	
	LCD_gpio();
		LCD_init();
	while(1){

		//motorControl(10,0);
		LCD_test();
		Delay(5000);
	
	
	}

 
		
	

	
}
