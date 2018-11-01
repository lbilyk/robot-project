#include "stm32f30x.h"
#include "Servo.h"

#define RCSEVROPIN GPIO_Pin_11
#define RCSERVO_PORT GPIOB
#define TIMER_SERVO TIM2
//void Servo_TimerInit()
//Brandon Dyson 
//Oct 22, 2018
//This function will put the starting values in the timer contol registior
void Servo_TimerInit()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Sets the Prescalar of the Timer 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//Sets counter mode to up counting mode 
  TIM_TimeBaseStructure.TIM_Period = SystemCoreClock/50;//Sets the timer period 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//sends values to 
		
	

}
//End of function

//void Servo_SetAngle(int angle)
//Brandon Dyson
//Oct 12, 2018
//Changes the width of the Pulse that is being sent to the sevro motor
void Servo_SetAngle(int angle)
{
	//Will countainue to exist after the function is extucuted
	static TIM_OCInitTypeDef Timer_OCTimeBase;//Creates a TIM_TimeBaseInitTypeDef structucure to put new_CRRvalue in
	//Error traping Stops angles greater then absoute value 0f 90 from being used to calculate pulse_width
	int servo = 600; //default
	if((angle >= 0) && (angle <= 180))
	{
		servo = SystemCoreClock/(angle*(20/9) + 420); // calculates servo movement based on angle

		
	Timer_OCTimeBase.TIM_Pulse=servo;
	Timer_OCTimeBase.TIM_OCMode = TIM_OCMode_PWM2;
  Timer_OCTimeBase.TIM_OutputState = TIM_OutputState_Enable;
  Timer_OCTimeBase.TIM_OutputNState = TIM_OutputNState_Enable;
	Timer_OCTimeBase.TIM_OCPolarity = TIM_OCPolarity_Low;
  Timer_OCTimeBase.TIM_OCNPolarity = TIM_OCNPolarity_High;
  Timer_OCTimeBase.TIM_OCIdleState = TIM_OCIdleState_Set;
  Timer_OCTimeBase.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC4Init(TIM2, &Timer_OCTimeBase);	
	
	TIM_Cmd(TIM2, ENABLE);
	/* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM2, ENABLE);
	
	}
	//End of Function 
}

//void Servo_GPIOsetup()
//Brandon Dyson
//Oct 23, 2018
//This Function sets up the sevros GPIO
void Servo_GPIOsetup()
{

}