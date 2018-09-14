#include "Utilities.h"

bool HasFlag(uint32_t mask, uint32_t flag)
{
	if((mask & flag) == flag)
		return true;
	return false;
}

void LEDInit()
{
	GPIO_InitTypeDef gpioa_init_struct = {GPIO_Pin_5, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL};
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &gpioa_init_struct);
}

void SetLEDState(bool ON)
{
	if(ON)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
}

void LEDToggle()
{
	LEDInit();
	if(GetLEDState())
	{
		SetLEDState(false);
		return;
	}
	SetLEDState(true);
}

bool GetLEDState()
{
	uint8_t led_bit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5);
	if(led_bit == (uint8_t)Bit_SET)
		return true;
	return false;
}

bool IsStrEqual(char* str1, const char* str2, int len)
{
	int i;
	for(i = 0; i < len; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}
	return true;
}
