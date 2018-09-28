/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ADC_1_Pin GPIO_PIN_0
#define ADC_1_GPIO_Port GPIOC
#define ADC_2_Pin GPIO_PIN_1
#define ADC_2_GPIO_Port GPIOC
#define ADC_3_Pin GPIO_PIN_2
#define ADC_3_GPIO_Port GPIOC
#define MOTOR_DIR1_Pin GPIO_PIN_0
#define MOTOR_DIR1_GPIO_Port GPIOA
#define MOTOR_DIR2_Pin GPIO_PIN_1
#define MOTOR_DIR2_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define ENCODER_1_Pin GPIO_PIN_6
#define ENCODER_1_GPIO_Port GPIOA
#define ENCODER_2_Pin GPIO_PIN_7
#define ENCODER_2_GPIO_Port GPIOA
#define RS232_TX_Pin GPIO_PIN_4
#define RS232_TX_GPIO_Port GPIOC
#define RS232_RX_Pin GPIO_PIN_5
#define RS232_RX_GPIO_Port GPIOC
#define MOTOR2_DIR1_Pin GPIO_PIN_0
#define MOTOR2_DIR1_GPIO_Port GPIOB
#define MOTOR2_DIR2_Pin GPIO_PIN_1
#define MOTOR2_DIR2_GPIO_Port GPIOB
#define LIMIT_LEFT_Pin GPIO_PIN_2
#define LIMIT_LEFT_GPIO_Port GPIOB
#define LIMIT_RIGHT_Pin GPIO_PIN_10
#define LIMIT_RIGHT_GPIO_Port GPIOB
#define RC_SERVO_Pin GPIO_PIN_11
#define RC_SERVO_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_12
#define LCD_E_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOB
#define STEP_A_Pin GPIO_PIN_6
#define STEP_A_GPIO_Port GPIOC
#define STEP_NOT_A_Pin GPIO_PIN_7
#define STEP_NOT_A_GPIO_Port GPIOC
#define STEP_B_Pin GPIO_PIN_8
#define STEP_B_GPIO_Port GPIOC
#define STEP_NOT_B_Pin GPIO_PIN_9
#define STEP_NOT_B_GPIO_Port GPIOC
#define DC_MOTOR_PWM1_Pin GPIO_PIN_8
#define DC_MOTOR_PWM1_GPIO_Port GPIOA
#define DC_MOTOR_PWM2_Pin GPIO_PIN_9
#define DC_MOTOR_PWM2_GPIO_Port GPIOA
#define LCD_BKLT_Pin GPIO_PIN_10
#define LCD_BKLT_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SPI_CS2_Pin GPIO_PIN_15
#define SPI_CS2_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
