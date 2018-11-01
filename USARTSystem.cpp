#include "USARTSystem.h"

volatile void (*USARTInvoker)(const char*) = 0;
volatile bool IsUSARTReady = false;
char* bufferText[10];
int strIndex = 0;
int strInternalIndex = 0;


void USARTInit()
{
	//Literally change the pins/uart number and it'll work
	//USART1 PA2 and PA3 do not work, they are not physically connected

	USART_InitTypeDef usartStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef gpioStruct;
	gpioStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &gpioStruct);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_7);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	usartStruct.USART_BaudRate = 115200;   
	usartStruct.USART_WordLength = USART_WordLength_8b;  
	usartStruct.USART_StopBits = USART_StopBits_1;   
	usartStruct.USART_Parity = USART_Parity_No ;
	usartStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usartStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &usartStruct);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
}

void USARTSend(char ch)
{
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, ch);
	for(int i = 0; i <10; i++);
}


unsigned char USART_R (USART_TypeDef* USARTx)
{
  while (!(USARTx->ISR & USART_ISR_RXNE));

  return((uint8_t) (USARTx->RDR & 0xFF));
}
