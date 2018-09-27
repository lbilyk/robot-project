
//#include "stm32f30x.h"

//#define MASK 0xFF33
//#define JSTICK_M 0xFFFFF300
//#define JSTICK_V 0x8AA

//void stepperControl(){
//	
//	int i,j,k,delay;
//	int counter = 0;
//	
//	unsigned char HalfStep[8] = {0x9, 0x8, 0xA, 0x2, 0x6, 0x4, 0x5, 0x1};
//	unsigned int A, NOTA, B, NOTB;
//	
//	GPIOB->MODER &= 0xFFFF0F0F;  
//	GPIOB->MODER |= 0x00005050;      //  Output(01)
//	

//	
//	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
//	GPIOB->OTYPER &= 0xFF33;     // Push-pull
//	
//	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
//	GPIOB->PUPDR   &= 0xFFFF0F0F;  

//	//Base speed	
//	delay = 50000;
//	
//	
//	//Current Version is set up for half stepping
//	//To change to full step, change array name to FullStep & set i parameters to 4 instead of 8
//	//Future version may include infndef
//	while(1){
//			
//	//Rotate Clockwise
//		
//					for(j = 0; j< 64; j++){
//						for(i = 0; i<8; i++){
//							for(k = 0; k< delay; k++);
//			
//			
//			A = (HalfStep[i] & 0x8) >> 3;
//			A = A << 2;
//			
//			NOTA = (HalfStep[i] & 0x4) >> 2;
//			NOTA = NOTA << 3;
//			B = (HalfStep[i] & 0x2) >> 1;
//			B = B << 6;
//			
//			NOTB = (HalfStep[i] & 0x1) >> 0;
//			NOTB = NOTB << 7;
//			
//			GPIOB->ODR &= 0xFF33;
//		 
//			GPIOB->ODR = A | NOTA | B | NOTB;
//							
//				
//						}
//					}
//				}
//  return;

//}
