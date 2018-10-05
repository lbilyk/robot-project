#include "LCD_display.h"
#include "SysTick.h"
#include "stm32f30x_gpio.h"

#define LCD_PORT GPIOB
#define LCD_RS 2
#define LCD_EN 3

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
		//LCD_PORT->ODR |= 1<<LCD_D7;
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_7,Bit_SET);//send 1 to GPIOB pin 7
	else 
		//LCD_PORT->ODR &= ~(1<<LCD_D7);
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_7,Bit_RESET);//send 0 to GPIOB pin 7
	
	if ( input &0x4) //plase data on 4 bit to pin
		//LCD_PORT->ODR |= 1<<LCD_D6;
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_6,Bit_SET);//send 1 to GPIOB pin 6
	else 
		//LCD_PORT->ODR &= ~(1<<LCD_D6);
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_6,Bit_RESET);//send 0 to GPIOB pin 7
	
	if ( input &0x2) //plase data on 4 bit to pin
		//LCD_PORT->ODR |= 1<<LCD_D5;
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_5,Bit_SET);
	else 
		LCD_PORT->ODR &= ~(1<<LCD_D5);
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_5,Bit_RESET);
	if ( input &0x1) //plase data on 4 bit to pin
		//LCD_PORT->ODR |= 1<<LCD_D4;
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_4,Bit_SET);
	else 
		//LCD_PORT->ODR &= ~(1<<LCD_D4);
		GPIO_WriteBit(LCD_PORT,GPIO_Pin_4,Bit_RESET);
}

void LCD_Pulse(void)
{
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
	Delay(300);
	LCD_sendCommand(0x30);
	Delay(40);
	LCD_sendCommand(0x30);
	Delay(40);
	LCD_sendCommand(0x30);
	Delay(40);
	
	LCD_sendCommand(0x2);
	Delay(40);
	LCD_sendCommand(0b001000);
	Delay(40);
	
	LCD_sendCommand(0x01);
	Delay(1500);
	LCD_sendCommand(0x06);
	Delay(40);
	LCD_sendCommand(0x0F);
	Delay(40);
}

void LCD_gpio()
{
	GPIO_InitTypeDef LCD;
	LCD.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13;
	LCD.GPIO_Mode=GPIO_Mode_OUT;
	LCD.GPIO_OType=GPIO_OType_PP;
	LCD.GPIO_Speed=GPIO_Speed_Level_1;
	LCD.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(LCD_PORT,&LCD);
	
	/*
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
  
  // Enable the clock to GPIO Port B,GPIO Port A,GPIO Port E
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN ;		
  
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)

	LCD_PORT->MODER &= LCD1_MASK;
	LCD_PORT->MODER |= LCD1_VALE;
		
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
			
	LCD_PORT->OSPEEDR &= LCD1_MASK;
	LCD_PORT->OSPEEDR |= LCD1_VALE;

	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	
	LCD_PORT->OTYPER &=LCD2_MASK;
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
		
	LCD_PORT->PUPDR &=LCD1_MASK;
	*/
}

void LCD_test(void)
{
	SysTickInit();
	uint8_t test_str[25]="Test";
	int count;
	LCD_init();
	
	for(count=0;test_str[count] != '\0';count++)
	{
		LCD_sendData(test_str[count]);
	}
	
}

void LCD_displaystr(uint8_t* input)
{
	int len=0;
	int count;
	
	for(count=0;input[count] != '\0';count++)
	{
			LCD_sendData(input[count]);
	}
}
