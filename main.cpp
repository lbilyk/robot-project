#include "main.h"
//static void TIM_Config(void);


int main(void)
{

	Direction motor_direction;
	int speed =100; //at least 7
	int direction =0; //forward:0 || reverse:1 || right:2 || left:3 || stop:4
	
	//INITIALIZE SYSTEMS
	SysTickInit();
	pwmInit();
	motorInit();
	
	//stepperInit();
	
	LCD_gpio();
	LCD_init();
	
	while(1){

		//motorControl(speed,direction);
	
		LCD_test();
		Delay(2000);
		motorControl(50,0);
		Delay(2000);
		//	stepperControl();
		

	

	}
		
	

	
}
