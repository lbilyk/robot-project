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

void stepperControl(int dir){

	int i,j;
	unsigned char halfStep[2][8] = {{0x9, 0x8, 0xA, 0x2, 0x6, 0x4, 0x5, 0x1},
																	{0x1, 0x5, 0x4, 0x6, 0x2, 0xA, 0x8, 0x9}};												
	unsigned int A, NOTA, B, NOTB;

		for(i = 0; i<8; i++){
			Delay(3);
			
			A = (halfStep[dir][i] & 0x8) >> 3;
			NOTA = (halfStep[dir][i] & 0x4) >> 2;
			B = (halfStep[dir][i] & 0x2) >> 1;
			NOTB = halfStep[dir][i] & 0x1;
				

			// Used to clear the ports PC6,PC7,PC8,PC9
			GPIOC->ODR &= 0xFC3F;
				
			// Sets the GPIO to the corresponding array values 
			GPIOC->ODR |= (A << 6);
			GPIOC->ODR |= (NOTA << 7);
			GPIOC->ODR |= (B << 8);
			GPIOC->ODR |= (NOTB << 9);					
		}
		if(GPIOB->IDR & 0x400){
			
			stepperControl(1);
		}
		if(GPIOB->IDR == 0x004){
		
			stepperControl(0);
		}
		GPIOC->ODR &= 0xFC3F; // clear bits to not draw excess power
 return;
}

int stepperCalibrate(){
	unsigned char halfStep[2][8] = {{0x9, 0x8, 0xA, 0x2, 0x6, 0x4, 0x5, 0x1}, //CCW
																	{0x1, 0x5, 0x4, 0x6, 0x2, 0xA, 0x8, 0x9}}; //CW
	unsigned int A, NOTA, B, NOTB, counter;
	int  i,j,dir;
	dir = 0; //CCW
	while(1){
		for(i = 0; i<8; i++){
			Delay(3);						//2 or 3 ms works best										
			A = (halfStep[dir][i] & 0x8) >> 3;
			NOTA = (halfStep[dir][i] & 0x4) >> 2;
			B = (halfStep[dir][i] & 0x2) >> 1;
			NOTB = halfStep[dir][i] & 0x1;

			GPIOC->ODR &= 0xFC3F; //clear bits
				
			// Sets the GPIO to the corresponding array values 
			GPIOC->ODR |= (A << 6);
			GPIOC->ODR |= (NOTA << 7);
			GPIOC->ODR |= (B << 8);
			GPIOC->ODR |= (NOTB << 9);					 
		}
		if(GPIOB->IDR & 0x400){ //if right limit switch is activated
			counter = 0;	//set the counter
			break;
		}
	}
	dir = 1; //change direction to CW
	while(1){
		for(i = 0; i<8; i++){
			Delay(3);																	
			A = (halfStep[dir][i] & 0x8) >> 3;
			NOTA = (halfStep[dir][i] & 0x4) >> 2;
			B = (halfStep[dir][i] & 0x2) >> 1;
			NOTB = halfStep[dir][i] & 0x1;

			GPIOC->ODR &= 0xFC3F; //clear bits
				
			// Sets the GPIO to the corresponding array values 
			GPIOC->ODR |= (A << 6);
			GPIOC->ODR |= (NOTA << 7);
			GPIOC->ODR |= (B << 8);
			GPIOC->ODR |= (NOTB << 9);				
			 
		}
		counter++;	//count until the other switch is activated
		if(GPIOB->IDR & 0x004){ //if left limit switch is activated
			break;
		}
			
	}
	counter = counter / 2; //find the middle
	dir = 0;
	for(i = 0; i < counter; i++){ //step until the middle is reached
		for(j=0; j < 8; j++){
			Delay(3);																	
			A = (halfStep[dir][j] & 0x8) >> 3;
			NOTA = (halfStep[dir][j] & 0x4) >> 2;
			B = (halfStep[dir][j] & 0x2) >> 1;
			NOTB = halfStep[dir][j] & 0x1;

			GPIOC->ODR &= 0xFC3F; //clear bits
				
			// Sets the GPIO to the corresponding array values 
			GPIOC->ODR |= (A << 6);
			GPIOC->ODR |= (NOTA << 7);
			GPIOC->ODR |= (B << 8);
			GPIOC->ODR |= (NOTB << 9);				
			 
		}
	}
	GPIOC->ODR &= 0xFC3F; // clear bits to not draw excess power
			
	return counter;
}

