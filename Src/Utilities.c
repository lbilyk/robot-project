//
// Created by Nik Kershaw on 2018-09-19.
//

#include "Utilities.h"

bool HasFlag(uint32_t mask, uint32_t flag)
{
    if((mask & flag) == flag)
        return true;
    return false;
}
/*
void LEDInit()
{
    GPIO_InitTypeDef gpioa_init_struct = {GPIO_PIN_5, GPIO_Mode_OUT, GPIO_SPEED_FREQ_HIGH, GPIO_OTYPE_, GPIO_PuPd_NOPULL};
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN, ENABLE);
    GPIO_Init(GPIOA, &gpioa_init_struct);
}

void SetLEDState(bool ON)
{
    if(ON)
    {
        GPIO_SetBits(GPIOA, GPIO_PIN_5);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_PIN_5);
    }
}

bool GetLEDState()
{
    uint8_t led_bit = GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_5);
    if(led_bit == (uint8_t)GPIO_PIN_SET)
        return true;
    return false;
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
}*/
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