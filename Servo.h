#include "LCD_display.h"
#include "SysTick.h"
#include <string.h>
#include "stm32f30x_gpio.h"
#include "stm32f30x_tim.h"

void Servo_SetAngle(int angle);//Changes the width of the Pulse that is being sent to the sevro motor
void Servo_TimerInit();//This function will put the starting values in the timer contol registior
void Servo_GPIOsetup();
