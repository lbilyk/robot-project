#include "pwmInit.h"
#define TIMER_SERVO TIM2
void pwmInit(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t Channel1Pulse = 0, Channel2Pulse = 0;
	int temo_ARR=SystemCoreClock/(20*10^-3+1);
	int TimerPeriod = (SystemCoreClock / temo_ARR )-1;
	
	
	// GPIOA Clocks enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);
	
	 
	//TIM1 clock enable 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN , ENABLE);

	/* GPIOA Configuration: Pins 8 and 9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

		//Servo PWM 
	GPIO_InitTypeDef servo;
	servo.GPIO_Pin=GPIO_Pin_11;
	servo.GPIO_Mode=GPIO_Mode_AF;
	servo.GPIO_OType=GPIO_OType_PP;
	servo.GPIO_Speed=GPIO_Speed_50MHz;
	servo.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&servo);

  /* GPIOB Configuration: Channel 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);


	//SERVO PWM INIT
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//Sets the Prescalar of the Timer 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//Sets counter mode to up counting mode 
  TIM_TimeBaseStructure.TIM_Period = SystemCoreClock/20000;//Sets the timer period 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//sends values to 

	
	
}