#include "SysTick.h"

volatile uint32_t TimeDelayMS;
volatile uint32_t TimeDelayUS;
volatile bool StartDelay = false;

extern "C" 
{
	void SysTick_Handler()
	{
		if(StartDelay)
		{
			TimeDelayUS += 10;
			if(TimeDelayUS % 1000 == 0)
				TimeDelayMS++;
		}
	}
}

void Delay(uint32_t nTime)
{
	TimeDelayMS = TimeDelayUS = 0;
	StartDelay = true;
	while(TimeDelayMS < nTime);
	StartDelay = false;
}

void DelayMicro(uint32_t nTime)
{
	if(nTime < 10)
		nTime = 10; //Minimum tick count is 10us, lower will hang
	TimeDelayMS = TimeDelayUS = 0;
	StartDelay = true;
	while(TimeDelayUS < nTime);
	StartDelay = false;
}

void SysTickInit()
{
	uint32_t ticks = 4 * 16 * 1000000;
	ticks /= 100000;
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks -1 ;
	NVIC_SetPriority(SysTick_IRQn, 0);
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	StartDelay = false;
	TimeDelayMS = TimeDelayUS = 0;
}