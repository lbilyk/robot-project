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
	uint16_t Channel1Pulse = 0, Channel2Pulse = 0;
	int temo_ARR=SystemCoreClock/(20*10^-3+1);
	int TimerPeriod = (SystemCoreClock / temo_ARR )-1;
		
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Sets the Prescalar of the Timer 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//Sets counter mode to up counting mode 
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;//Sets the timer period 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;		
  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;		
	TIM_OC1Init(TIMER_SERVO, &TIM_OCInitStructure);
  TIM_OC2Init(TIMER_SERVO, &TIM_OCInitStructure);	

  TIM_TimeBaseInit(TIMER_SERVO, &TIM_TimeBaseStructure);//sends values to 

}
//End of function

//void Servo_SetAngle(int angle)
//Brandon Dyson
//Oct 12, 2018
//Changes the width of the Pulse that is being sent to the sevro motor
void Servo_SetAngle(int angle)
{
	//Will countainue to exist after the function is extucuted
	static TIM_OCInitTypeDef Timer_TimeBase;//Creates a TIM_TimeBaseInitTypeDef structucure to put new_CRRvalue in
	//
	int pulse_width;//Time that the width must be to get the right angle 
	float duty_cycle;//This is the duty cycle of the control signal( time on / period)
	int new_CRRvalue;//This the new CRR value that will set to ensure 
	int temo_ARR=SystemCoreClock/(20*10^-3+1); 
	
	//Error traping Stops angles greater then absoute value 0f 90 from being used to calculate pulse_width
	if((angle >= -90) && (angle <= 90))
	{
	//Pulse width Calculation 
	pulse_width=10*angle +1500;
	//duty cycle calculution 
	duty_cycle=pulse_width/20000;//Divide Pulse width(in uS) by period(in uS)20ms =20000uS
	
	//new_CRRvalue =int(duty_cycle*(ARR+1))The ARR is value the preset and I will call upon
	new_CRRvalue=int(duty_cycle*(temo_ARR+1));
	//Set the timer CRR value to new_CRRvalue
	Timer_TimeBase.TIM_Pulse=new_CRRvalue;
	TIM_OC1Init(TIM4,&Timer_TimeBase);
	}
	//End of Function 
}

//void Servo_GPIOsetup()
//Brandon Dyson
//Oct 23, 2018
//This Function sets up the sevros GPIO
void Servo_GPIOsetup()
{
	GPIO_InitTypeDef servo;
	servo.GPIO_Pin=GPIO_Pin_11;
	servo.GPIO_Mode=GPIO_Mode_OUT;
	servo.GPIO_OType=GPIO_OType_PP;
	servo.GPIO_Speed=GPIO_Speed_50MHz;
	servo.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(RCSERVO_PORT,&servo);
}