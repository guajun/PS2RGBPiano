/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>

#include <stdlib.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define LED_DATA0_Pin GPIO_PIN_0
#define LED_DATA0_GPIO_Port GPIOB
#define LED_DATA1_Pin GPIO_PIN_1
#define LED_DATA1_GPIO_Port GPIOB
#define LED_DATA2_Pin GPIO_PIN_2
#define LED_DATA2_GPIO_Port GPIOB
#define PS2_DATA_Pin GPIO_PIN_10
#define PS2_DATA_GPIO_Port GPIOA
#define LED_DATA3_Pin GPIO_PIN_3
#define LED_DATA3_GPIO_Port GPIOB
#define LED_DATA4_Pin GPIO_PIN_4
#define LED_DATA4_GPIO_Port GPIOB
#define LED_DATA5_Pin GPIO_PIN_5
#define LED_DATA5_GPIO_Port GPIOB
#define LED_DATA6_Pin GPIO_PIN_6
#define LED_DATA6_GPIO_Port GPIOB
#define LED_DATA7_Pin GPIO_PIN_7
#define LED_DATA7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
