#ifndef _USARTSYSTEM_H_
#define _USARTSYSTEM_H_

#include "stm32f30x_usart.h"
#include "Utilities.h"
#include <stdlib.h>

void USARTInit();
void USARTSend(char);
unsigned char USART_R (USART_TypeDef* USARTx);

#endif