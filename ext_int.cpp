
#include "ext_int.h"

EXTI_InitTypeDef   EXTI_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;


static void EXTI9_5_Config(void);
static void EXTI15_10_Config(void);


int extInit(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
     */

  /* Initialize LEDs mounted on STM32303C-EVAL board */

  /* Configure PE6 and PD5 in interrupt mode */
  EXTI9_5_Config();
  
  /* Configure PC13 in interrupt mode */
  EXTI15_10_Config();
  
  /* Generate software interrupt: simulate a rising edge applied on EXTI5 line */
  EXTI_GenerateSWInterrupt(EXTI_Line5);
return 0;
}


static void EXTI9_5_Config(void)
{
  /* Enable the BUTTON Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD|RCC_AHBPeriph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
//  /* Connect EXTI5 Line to PD5 pin */
//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);
//  
//  /* Connect EXTI6 Line to PE6 pin */
//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
  
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure); 
}


static void EXTI15_10_Config(void)
{
  /* Enable GPIOC clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PC13 pin in input pull-down mode */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* Connect EXTI13 Line to PC13 pin */
//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13); 
  
  /* Configure EXTI13 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI15_10 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

