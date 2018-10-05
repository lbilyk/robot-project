
#include "stm32f30x.h"

void LCD_gpio();
void LCD_init(void);
void LCD_PutNibble(uint8_t input);
void LCD_sendData(uint8_t input);
void LCD_sendCommand(uint8_t input);
void LCD_Pulse(void);
void LCD_test(void);
void LCD_displaystr(uint8_t* input);