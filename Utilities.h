#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "stm32f30x.h"
#include <string.h>

bool HasFlag(uint32_t, uint32_t);
bool IsStrEqual(char*, const char*, int);
void SetLEDState(bool ON);
bool GetLEDState();
void LEDToggle();
void LEDInit();
#endif