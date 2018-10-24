
#include "stepper.h"


void stepperInit(){
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC , ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//Configure Port c Pin 6,7,8,9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void stepperControl(){

	int i,j;
	int counter = 0;
	
	unsigned char HalfStep[8] = {0x9, 0x8, 0xA, 0x2, 0x6, 0x4, 0x5, 0x1};
	unsigned int A, NOTA, B, NOTB;

	
	//Current Version is set up for half stepping
	//To change to full step, change array name to FullStep & set i parameters to 4 instead of 8
	//Future version may include infndef
	
	//Rotate Clockwise
		
					for(j = 0; j< 64; j++){
						for(i = 0; i<8; i++){
						Delay(10);
	
			A = (HalfStep[i] & 0x8) >> 3;
			NOTA = (HalfStep[i] & 0x4) >> 2;
			B = (HalfStep[i] & 0x2) >> 1;
			NOTB = HalfStep[i] & 0x1;
				

				// Used to clear the ports PC6,PC7,PC8,PC9
				GPIOC->ODR &= 0xFC3F;
				
				// Sets the GPIO to the corresponding array values 
				GPIOC->ODR |= (A << 6);
				GPIOC->ODR |= (NOTA << 7);
				GPIOC->ODR |= (B << 8);
				GPIOC->ODR |= (NOTB << 9);
							
						}
					}
					
					if(GPIOB->IDR == 0x4){
					
					GPIOC->ODR &= 0xFC3F;
						return;
					}
			
				
 return;

}
