/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define sound_Pin GPIO_PIN_1
#define sound_GPIO_Port GPIOA
#define dataPin_Pin GPIO_PIN_5
#define dataPin_GPIO_Port GPIOA
#define latchPin_Pin GPIO_PIN_6
#define latchPin_GPIO_Port GPIOA
#define clockPin_Pin GPIO_PIN_7
#define clockPin_GPIO_Port GPIOA
#define btn_on_Pin GPIO_PIN_3
#define btn_on_GPIO_Port GPIOB
#define btn_mode_Pin GPIO_PIN_4
#define btn_mode_GPIO_Port GPIOB
#define btn_next_Pin GPIO_PIN_5
#define btn_next_GPIO_Port GPIOB
#define RED_PIN_Pin GPIO_PIN_7
#define RED_PIN_GPIO_Port GPIOB
#define GREEN_PIN_Pin GPIO_PIN_8
#define GREEN_PIN_GPIO_Port GPIOB
#define BLUE_PIN_Pin GPIO_PIN_9
#define BLUE_PIN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
