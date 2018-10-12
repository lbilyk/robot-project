
#include "stm32f30x.h"


void motorInit(){
	GPIO_InitTypeDef GPIO_InitStructure;

	//Configure Port A Pin 0 and 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Configure Port B Pin 0 and 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  return;

}

int motorControl(int speed,int dir){
	
	uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0, Channel2Pulse = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	int direction[5][2]= {{ //forward
													0x2,0x1,},
													//reverse
												{ 0x1,0x2},
													//right
												{ 0x2,0x0},
													//left
												{ 0x0,0x1},
												{0x0, 0x0}};
	

	//PWM DUTY CYCLE 
  TimerPeriod = (SystemCoreClock / 100 ) - 1;
  Channel1Pulse = (uint16_t) (((uint32_t) speed * (TimerPeriod - 1)) / 100);
  Channel2Pulse = (uint16_t) (((uint32_t) speed * (TimerPeriod - 1)) / 100);

	/* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	//Channel 1 & 2 continuous config in pwm mode
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

										
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;		
  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;		
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);												
										

	/* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);
	/* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	GPIOA->ODR = direction[dir][0];
	GPIOB->ODR = direction[dir][1];

	return 0;
}

	
	