#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f30x.h"

extern "C" { void SysTick_Handler(); }
void Delay(uint32_t);
void DelayMicro(uint32_t);
void SysTickInit();

#endif