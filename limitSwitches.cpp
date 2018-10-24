#include "limitSwitches.h"

void switchInit(){
	
GPIO_InitTypeDef GPIO_InitStructure;

	//Configure Port B Pin 2 and 10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
}


