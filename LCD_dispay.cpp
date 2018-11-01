#include "LCD_display.h"
#include "SysTick.h"
#include <string.h>
#include "stm32f30x_gpio.h"

#define LCD_PORT GPIOB
#define LCD_RS 12
#define LCD_EN 13

#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

#define LCD1_MASK 0xF0FF00FF
#define LCD1_VALE 0x07007700

#define LCD2_MASK 0xCF0F



void LCD_PutNibble(uint8_t input)
{
	if ( input &0x8) //Put data bit to
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_7,Bit_SET);//send 1 to GPIOB pin 7
	else 
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_7,Bit_RESET);//send 0 to GPIOB pin 7
	
	if ( input &0x4) //plase da ta on 4 bit to pin
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_6,Bit_SET);//send 1 to GPIOB pin 6
	else 
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_6,Bit_RESET);//send 0 to GPIOB pin 7
	
	if ( input &0x2) //plase data on 4 bit to pin
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_5,Bit_SET);
	else 
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_5,Bit_RESET);
	if ( input &0x1) //plase data on 4 bit to pin
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_4,Bit_SET);
	else 
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_4,Bit_RESET);
}

void LCD_Pulse(void)
{
	Delay(4);
	//LCD_PORT ->ODR |= 1<<LCD_EN;//Set E high 
	GPIO_WriteBit(LCD_PORT,GPIO_Pin_12,Bit_SET);
	Delay(4);//delay
	GPIO_WriteBit(LCD_PORT,GPIO_Pin_12,Bit_RESET);
	Delay(4);//delay
}

void LCD_sendData(uint8_t input)
	
{
	LCD_PutNibble( input >> 4);//Sends upper four bits
	LCD_Pulse();
	
	LCD_PutNibble(input & 0xF);//Sends lower four bits
	LCD_Pulse();
}

void LCD_sendCommand(uint8_t input)
{
	//LCD_PORT->ODR &= ~(1<<LCD_RS);
	GPIO_WriteBit(LCD_PORT,GPIO_Pin_13,Bit_RESET);
	LCD_PutNibble( input >> 4);//Sends upper four bits
	LCD_Pulse();
	
	LCD_PutNibble(input & 0xF);//Sends lower four bits
	LCD_Pulse();
	
	//LCD_PORT->ODR |= (1<<LCD_RS);
	GPIO_WriteBit(LCD_PORT,GPIO_Pin_13,Bit_SET);
}

void LCD_init(void)
{	
	Delay(40);
	LCD_sendCommand(0x30);
	Delay(40);
	LCD_sendCommand(0x30);
	Delay(40);
	LCD_sendCommand(0x30);
	Delay(40);
	LCD_sendCommand(0x2);
	Delay(40);
	LCD_sendCommand(0x2C);
	Delay(40);
	LCD_sendCommand(0x01);
	Delay(40);
	LCD_sendCommand(0x06);
	Delay(40);
	LCD_sendCommand(0xC);
	Delay(40);
}

void LCD_gpio()
{
	uint16_t TimerPeriod = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	uint16_t Channel3Pulse = 0;

	TimerPeriod = (SystemCoreClock / 100 ) - 1;
	Channel3Pulse = (uint16_t) (((uint32_t) 10 * (TimerPeriod - 1)) / 100);
	

	GPIO_InitTypeDef LCD;
	LCD.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
	LCD.GPIO_Mode=GPIO_Mode_OUT;
	LCD.GPIO_OType=GPIO_OType_PP;
	//LCD.GPIO_Speed=GPIO_Speed_Level_3;
	LCD.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(LCD_PORT,&LCD);
	
	
}

void LCD_displaystr(char* input)
{

	int count;
	for(count=0; count < strlen(input); count++)
	{
		LCD_sendData(input[count]);
	}
}

void LCD_clearscreen(void)
{
LCD_sendCommand(0x1);
}