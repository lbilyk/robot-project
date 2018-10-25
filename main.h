#ifndef _MAIN_H_
#define _MAIN_H_


#include <string.h>
#include "stm32f30x.h"
#include "SysTick.h"
#include "DCmotors.h"
#include "LCD_display.h"
#include "pwmInit.h"
#include "stepper.h"
#include "limitSwitches.h"
#include "USARTSystem.h"
#include "ext_int.h"
#include "servo.h"

void sendstr(uint8_t* Buffer);
void delay(unsigned int time);
void commandselect(uint8_t* command);
int CompareC(uint8_t* baseword, uint8_t* command);
int argcheck (uint8_t*,const char*);

#endif