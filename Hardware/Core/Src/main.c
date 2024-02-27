/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
 1sasassaasas		  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t SR[7]; 
uint8_t single_on[] = { 0b01000000, 0b00100000, 0b00010000,
                         0b00001000, 0b00000100, 0b00000010 };
uint8_t high = 0b11111111;
uint8_t low = 0b00000000;
	  uint8_t level[6] = { 0b10111111, 0b11011111, 0b11101111,
                      0b11110111, 0b11111011,0b11111101 };											 
												 
												 
												 
	  uint8_t mode = 0;
  uint8_t type_mode0 = 0;
  uint8_t type_mode1 = 0;
		bool check_on = true;										
		  int soundThreshold = 3600;										 

  uint8_t buttonStatus_on = 0;
  uint8_t buttonStatus_mode = 0;
  uint8_t buttonStatus_next = 0;
   bool haveSignal = false;
												 
uint32_t sound_value;

char buffer[50];
bool chOn = false;											

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */


void	turn_on();

void turn_off();

void checkSignal();
bool checkSignalON();
void perform();
void mode0_next();
void mode1_next();


//effect



void sound_mode0();
void normal_mode0();
void random_yz();
void dynamicNoise(int duration);
void full(int t);
void random_on();
void random_off();
void single_random(int t);
void x();
void y();
void z();	
void x_snake();
void y_stretched();
void x_trail();
void sun();
void spiral();	
void rain();
void GrowingCube(int n);
void frame4x4();
void frame2x2();
void frame6x6();
void random2x2();
void random3x3();
void random4x4();	
void random5x5();
void flashLEDs();
void adjustBrightness();
void soundFrame();
void soundResponsiveEffect2();
void soundFloorJumping();
void soundResponsiveBlink();
void soundFrameCorner1();	
void soundFrameCorner5();
void soundFrameCorner2();
void soundFrameCorner6();
void soundFrameCorner3();
void soundFrameCorner7();
void soundFrameCorner4();
void soundFrameCorner8();


void displayChars(uint8_t letters[],int n);
void StringtoDisplay(char text_cp[]);
	

void shift_out();
void clear_out();
void delayMicroseconds(uint32_t us);
uint32_t  getValue();




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



char received_char;

int str_index = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)  
    {
        if (received_char != '@')
        {
            buffer[str_index++] = received_char;
        }
        else
        {
					
					
          buffer[str_index] = '\0'; 
          str_index = 0;
					
				
				
					  
					if(check_on == true){
						
							if (strcmp(buffer, "down") == 0) {
									soundThreshold = soundThreshold - 50;
									memset(buffer, 0, 50);
									HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1); 
									return;
							} else if (strcmp(buffer, "up") == 0)	 {
									soundThreshold = soundThreshold + 50;
									memset(buffer, 0, 50);
									HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1); 
									return;
							} else if (strcmp(buffer, "on") == 0)	 {
									memset(buffer, 0, 50);
									HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1); 
									return;
							}
							else{
									haveSignal = true;
									return;
							}									
					}else{
						if(strcmp(buffer, "on_off") == 0 ||  strcmp(buffer, "on") == 0){
								memset(buffer, 0, 50);
								chOn = true;
								haveSignal = true;
							return;
						}else{						
							memset(buffer, 0, 50);
							HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1); 
							return;
						}
					}		
					
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1);   
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	 

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1);   
	turn_on();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
		
//		HAL_UART_Receive(&huart1, (uint8_t*)&buffer, 6,50);
//		if(strcmp(buffer, "mode0@") == 0 ){	
//			HAL_GPIO_WritePin(GPIOB, GREEN_PIN_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB, BLUE_PIN_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin, GPIO_PIN_RESET);
//		}			
}		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  
  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, dataPin_Pin|latchPin_Pin|clockPin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin|GREEN_PIN_Pin|BLUE_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : dataPin_Pin latchPin_Pin clockPin_Pin */
  GPIO_InitStruct.Pin = dataPin_Pin|latchPin_Pin|clockPin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : btn_on_Pin btn_mode_Pin btn_next_Pin */
  GPIO_InitStruct.Pin = btn_on_Pin|btn_mode_Pin|btn_next_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_PIN_Pin GREEN_PIN_Pin BLUE_PIN_Pin */
  GPIO_InitStruct.Pin = RED_PIN_Pin|GREEN_PIN_Pin|BLUE_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   if(hadc->Instance ==  hadc1.Instance){
	
	  sound_value = HAL_ADC_GetValue(&hadc1);
		HAL_Delay(100);
	
 }
}





 void shift_out() {
    HAL_GPIO_WritePin(GPIOA, latchPin_Pin, GPIO_PIN_RESET); 

    for (int i = 0; i < 7; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            HAL_GPIO_WritePin(GPIOA, dataPin_Pin, ((SR[i] >> bit) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
            
            HAL_GPIO_WritePin(GPIOA, clockPin_Pin, GPIO_PIN_SET);
           
            HAL_GPIO_WritePin(GPIOA, clockPin_Pin, GPIO_PIN_RESET);
        }
    }
    HAL_GPIO_WritePin(GPIOA, latchPin_Pin, GPIO_PIN_SET);
}





void clear_out() {
    for (int i = 0; i < 6; i++) {
        SR[i] = 0x00;
    }
    SR[6] = 0xFF;
    shift_out();
}


void mode0_next(){
	mode = 0;
	HAL_GPIO_WritePin(GPIOB, GREEN_PIN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BLUE_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin, GPIO_PIN_RESET);
  clear_out();
  if (type_mode0 == 0) {
    while (type_mode0 == 0) {
      normal_mode0();
      if (haveSignal) {
        break;
      }
    }
    perform();

  } else if (type_mode0 == 1) {
    while (type_mode0 == 1) {
      single_random(50);
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 2) {
    while (type_mode0 == 2) {
      GrowingCube(10);

      if (haveSignal) {
        break;
      }
    }

    perform();
  } else if (type_mode0 == 3) {
    while (type_mode0 == 3) {
      rain();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 4) {
    while (type_mode0 == 4) {
      x_snake();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 5) {
    while (type_mode0 == 5) {
      y_stretched();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 6) {
    while (type_mode0 == 6) {

      x_trail();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 7) {
    while (type_mode0 == 7) {
      spiral();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 8) {
    while (type_mode0 == 8) {

      random_on();
      if (haveSignal) {
        break;
      }
      random_off();

      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 9) {
    while (type_mode0 == 9) {
      random2x2();
      if (haveSignal) {
        break;
      }
      random3x3();
      if (haveSignal) {
        break;
      }
      random4x4();
      if (haveSignal) {
        break;
      }
      random5x5();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 10) {
    while (type_mode0 == 10) {

      x();
      if (haveSignal) {
        break;
      }
      y();
      if (haveSignal) {
        break;
      }
      z();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 11) {
    while (type_mode0 == 11) {
      sun();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 12) {
    while (type_mode0 == 12) {
      dynamicNoise(500);
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 13) {
    while (type_mode0 == 13) {
      random_yz();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 14) {
    while (type_mode0 == 14) {

      frame2x2();
      if (haveSignal) {
        break;
      }
      frame4x4();
      if (haveSignal) {
        break;
      }
      frame6x6();
      if (haveSignal) {
        break;
      }
      frame6x6();
      if (haveSignal) {
        break;
      }
      frame4x4();
      if (haveSignal) {
        break;
      }
      frame2x2();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 == 15) {
    while (type_mode0 == 15) {
      full(100);
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode0 > 15) {
    type_mode0 =0;
		 mode0_next();
    
  }
}

void mode1_next(){
	mode = 1;
  HAL_GPIO_WritePin(GPIOB, GREEN_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BLUE_PIN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin, GPIO_PIN_RESET);
  clear_out();
  if (type_mode1 == 0) {
    while (type_mode1 == 0) {
      sound_mode0();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 1) {
    while (type_mode1 == 1) {
      flashLEDs();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 2) {
    while (type_mode1 == 2) {
      adjustBrightness();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 3) {
    while (type_mode1 == 3) {
      soundResponsiveBlink();

      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 4) {
    while (type_mode1 == 4) {
      soundFrame();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 5) {
    while (type_mode1 == 5) {
      soundResponsiveEffect2();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 6) {
    while (type_mode1 == 6) {
      soundFloorJumping();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    perform();
  } else if (type_mode1 == 7) {
    while (type_mode1 == 7) {

      uint32_t  currentMillis =	HAL_GetTick();
      uint32_t  previousMillis = HAL_GetTick();
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner1();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner2();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner3();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner4();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner5();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner6();
        checkSignal();
        if (haveSignal) {
          break;
        }
       currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner7();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }

      if (haveSignal) {
        break;
      }
      previousMillis = currentMillis;
      while (currentMillis - previousMillis <= 15000) {
        soundFrameCorner8();
        checkSignal();
        if (haveSignal) {
          break;
        }
        currentMillis = HAL_GetTick();
      }
      if (haveSignal) {
        break;
      }
    }
    perform();

  } else if (type_mode1 > 7) {
    type_mode1 = 0;
    mode1_next();
  }
	
}

void checkSignal(){
	buttonStatus_on = HAL_GPIO_ReadPin(GPIOB,btn_on_Pin);
  buttonStatus_mode = HAL_GPIO_ReadPin(GPIOB,btn_mode_Pin);
  buttonStatus_next = HAL_GPIO_ReadPin(GPIOB,btn_next_Pin);
	
	
	//HAL_UART_Receive(&huart1, (uint8_t*)buffer, 50, 10);
	
//	if (mode == 1) {
//    if (strcmp(buffer, "t") == 0) {
//      soundThreshold = soundThreshold - 100;
//     memset(buffer, 0, 50);
//    } else if (strcmp(buffer, "t") == 0)	 {
//      soundThreshold = soundThreshold + 100;
//        memset(buffer, 0, 50);
//    }
//  }
	
//	 if (buttonStatus_on == 1 || buttonStatus_mode == 1 || buttonStatus_next == 1  ||  strcmp(buffer, "") != 0) {
//    haveSignal = true;
//  }
	 
	if (buttonStatus_on == 1 || buttonStatus_mode == 1 || buttonStatus_next == 1) {
    haveSignal = true;
  }
	

	
}



void perform(){
	 
		if(strcmp(buffer, "") != 0){
			
			HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1);
			char firstChar = buffer[0];
			if(firstChar != '#'){
					haveSignal = false;
      if (check_on == true) {
        if ( strcmp(buffer, "on_off") == 0 ||  strcmp(buffer, "off") == 0) {
					memset(buffer, 0, 50);
          HAL_Delay(200);
          check_on = false;

          turn_off();
        } else if ( strcmp(buffer, "mode0") == 0) {
          mode = 0;
       	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode1") == 0) {
          mode = 1;
          	memset(buffer, 0, 50);
          mode1_next();
        } else if (strcmp(buffer, "mode0_0") == 0) {
         	memset(buffer, 0, 50);
         
          type_mode0 = 0;

          mode0_next();
        } else if (strcmp(buffer, "mode0_1") == 0) {
          type_mode0 = 1;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_2") == 0) {
          type_mode0 = 2;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_3") == 0) {
          type_mode0 = 3;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_4") == 0) {
          type_mode0 = 4;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_5") == 0) {
          type_mode0 = 5;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_6") == 0) {
          type_mode0 = 6;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_7") == 0) {
          type_mode0 = 7;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_8") == 0) {
          type_mode0 = 8;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_9") == 0) {
          type_mode0 = 9;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_10") == 0) {
          type_mode0 = 10;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_11") == 0) {
          type_mode0 = 11;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_12") == 0) {
          type_mode0 = 12;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_13") == 0) {
          type_mode0 = 13;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_14") == 0) {
          type_mode0 = 14;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode0_15") == 0) {
          type_mode0 = 15;
          	memset(buffer, 0, 50);
          mode0_next();
        } else if (strcmp(buffer, "mode1_0") == 0) {
          type_mode1 = 0;
          	memset(buffer, 0, 50);
          mode1_next();
        } else if (strcmp(buffer, "mode1_1") == 0) {
          type_mode1 = 1;
          	memset(buffer, 0, 50);
          mode1_next();
        } else if (strcmp(buffer, "mode1_2") == 0) {
          type_mode1 = 2;
          	memset(buffer, 0, 50);
          mode1_next();
        } else if (strcmp(buffer, "mode1_3") == 0) {
          type_mode1 = 3;
          	memset(buffer, 0, 50);
          mode1_next();
        } else if (strcmp(buffer, "mode1_4") == 0) {
          type_mode1 = 4;
          	memset(buffer, 0, 50);
					 mode1_next();
        } else if (strcmp(buffer, "mode1_5") == 0) {
          type_mode1 = 5;
          	memset(buffer, 0, 50);
          mode1_next();

        } else if (strcmp(buffer, "mode1_6") == 0) {
          type_mode1 = 6;
          	memset(buffer, 0, 50);
          mode1_next();

        } else if (strcmp(buffer, "mode1_7") == 0) {
          type_mode1 = 7;
          	memset(buffer, 0, 50);
          mode1_next();

        }
				
				else	{
           NVIC_SystemReset();
        }
      } else {
        if (strcmp(buffer, "on_off") == 0 || strcmp(buffer, "on") == 0) {
					
					memset(buffer, 0, 50);
					HAL_Delay(200);
          check_on = true;
          turn_on();
					
					
        }
      }
					
				} 
			else {
			 char newBuffer[strlen(buffer)];
				
				 for (int i = 1; i < strlen(buffer); i++) {
						newBuffer[i - 1] = buffer[i];
				}
				  newBuffer[strlen(buffer) - 1] = '\0';
		
						haveSignal = false;
						memset(buffer, 0, 50);
						StringtoDisplay(newBuffer);
    
						perform();
			}
			
			
		}	
	
	 if (buttonStatus_on == 1) {
    buttonStatus_on = 0;
    haveSignal = false;
   
    clear_out();
    HAL_Delay(500);

    if (check_on == true) {
      check_on = false;
      turn_off();

    } else {

      check_on = true;
      turn_on();
    }
  } else if (buttonStatus_mode == 1 && check_on == true) {
    buttonStatus_mode = 0;
    haveSignal = false;
 
    clear_out();
    HAL_Delay(500);
    if (mode == 0) {
      mode = 1;
      mode1_next();
    } else {
      mode = 0;
      mode0_next();
    }

  } else if (buttonStatus_next == 1 && check_on == true) {
    buttonStatus_next = 0;
    haveSignal = false;
 
    HAL_Delay(500);
    clear_out();
    if (mode == 0) {
      type_mode0++;
      mode0_next();
    } else {
      type_mode1++;
      mode1_next();
    }
  }
}

void StringtoDisplay(char text_cp[]) {
 
  int k = 0;
  uint8_t arrayText[100];

  for (int i = 0; i < strlen(text_cp); i++) {
   
     char x = text_cp[i];

    int a;
    if (x == 'a') {
      arrayText[k++] = 0;
    } else if (x == 'b') {
      arrayText[k++] = 1;
    } else if (x == 'c') {
      arrayText[k++] = 2;
    } else if (x == 'd') {
      arrayText[k++] = 3;
    } else if (x == 'e') {
      arrayText[k++] = 4;
    } else if (x == 'f') {
      arrayText[k++] = 5;
    } else if (x == 'g') {
      arrayText[k++] = 6;
    } else if (x == 'h') {
      arrayText[k++] = 7;
    } else if (x == 'i') {
      arrayText[k++] = 8;
    } else if (x == 'j') {
      arrayText[k++] = 9;
    } else if (x == 'k') {
      arrayText[k++] = 10;
    } else if (x == 'l') {
      arrayText[k++] = 11;
    } else if (x == 'm') {
      arrayText[k++] = 12;
    } else if (x == 'n') {
      arrayText[k++] = 13;
    } else if (x == 'o') {
      arrayText[k++] = 14;
    } else if (x == 'p') {
      arrayText[k++] = 15;
    } else if (x == 'q') {
      arrayText[k++] = 16;
    } else if (x == 'r') {
      arrayText[k++] = 17;
    } else if (x == 's') {
      arrayText[k++] = 18;
    } else if (x == 't') {
      arrayText[k++] = 19;
    } else if (x == 'u') {
      arrayText[k++] = 20;
    } else if (x == 'v') {
      arrayText[k++] = 21;
    } else if (x == 'w') {
      arrayText[k++] = 22;
    } else if (x == 'x') {
      arrayText[k++] = 23;
    } else if (x == 'y') {
      arrayText[k++] = 24;
    } else if (x == 'z') {
      arrayText[k++] = 25;
    } else if (x == ' ') {
      arrayText[k++] = 26;
    } else if (x == '0') {
      arrayText[k++] = 27;
    } else if (x == '1') {
      arrayText[k++] = 28;
    } else if (x == '2') {
      arrayText[k++] = 29;
    } else if (x == '3') {
      arrayText[k++] = 30;
    } else if (x == '4') {
      arrayText[k++] = 31;
    } else if (x == '5') {
      arrayText[k++] = 32;
    } else if (x == '6') {
      arrayText[k++] = 33;
    } else if (x == '7') {
      arrayText[k++] = 34;
    } else if (x == '8') {
      arrayText[k++] = 35;
    } else if (x == '9') {
      arrayText[k++] = 36;
    } else if (x == '!') {
      arrayText[k++] = 37;
    } else if (x == ':') {
      arrayText[k++] = 38;
    } else if (x == ',') {
      arrayText[k++] = 39;
    } else if (x == '?') {
      arrayText[k++] = 40;
    } else if (x == '/') {
      arrayText[k++] = 41;
    } else if (x == ';') {
      arrayText[k++] = 42;
    }else if (x == '+') {
      arrayText[k++] = 43;
    }else if (x == '-') {
      arrayText[k++] = 44;
    }else if (x == '=') {
      arrayText[k++] = 45;
    }else if (x == ')') {
      arrayText[k++] = 46;
    }else if (x == '(') {
      arrayText[k++] = 47;
    }else if (x == '<') {
      arrayText[k++] = 48;
    }else if (x == '>') {
      arrayText[k++] = 49;
    }else if (x == '.') {
      arrayText[k++] = 50;
    }
  }
  arrayText[k++] = 26;
  arrayText[k++] = 26;
  while (true) {
    displayChars(arrayText, k);
    if (haveSignal) {
      break;
    }
  }
  return;
}


void displayChars(uint8_t letters[],int n){
	
	uint8_t alphabet[][6] = {
    { 0b00011000, 0b00100100, 0b00100100, 0b00111100, 0b00100100, 0b00100100 },  //a 0
    { 0b00111000, 0b00100100, 0b00100100, 0b00111000, 0b00100100, 0b00111000 },  //0b 1
    { 0b00011000, 0b00100100, 0b00100000, 0b00100000, 0b00100100, 0b00011000 },  //c 2
    { 0b00111000, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00111000 },  //d 3
    { 0b00111100, 0b00100000, 0b00111000, 0b00100000, 0b00100000, 0b00111100 },  //e 4
    { 0b00111100, 0b00100000, 0b00111000, 0b00100000, 0b00100000, 0b00100000 },  //f 5
    { 0b00011000, 0b00100100, 0b00100000, 0b00101100, 0b00100100, 0b00011000 },  //g 6
    { 0b00100100, 0b00100100, 0b00100100, 0b00111100, 0b00100100, 0b00100100 },  //h 7
    { 0b00111000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00111000 },  //i 8
    { 0b00111110, 0b00001000, 0b00001000, 0b01001000, 0b01001000, 0b00110000 },  //j 9
    { 0b00100100, 0b00101000, 0b00110000, 0b00101000, 0b00100100, 0b00100100 },  //k 10
    { 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00111100 },  //l 11
    { 0b01000100, 0b01101100, 0b01010100, 0b01000100, 0b01000100, 0b01000100 },  //m 12
    { 0b01000010, 0b01100010, 0b01010010, 0b01001010, 0b01000110, 0b01000010 },  //n 13
    { 0b00011000, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00011000 },  //o 14
    { 0b00111000, 0b00100100, 0b00100100, 0b00111000, 0b00100000, 0b00100000 },  //p 15
    { 0b00111000, 0b01000100, 0b01000100, 0b01010100, 0b01001000, 0b00110100 },  //q 16
    { 0b00111000, 0b00100100, 0b00100100, 0b00111000, 0b00101000, 0b00100100 },  //r 17
    { 0b00011100, 0b00100000, 0b00010000, 0b00001000, 0b00100100, 0b00011000 },  //s 18
    { 0b01111100, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000 },  //t 19
    { 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00011000 },  //u 20
    { 0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b00101000, 0b00010000 },  //v 21
    { 0b01000100, 0b01000100, 0b01000100, 0b01010100, 0b01101100, 0b01000100 },  //w 22
    { 0b00000000, 0b01000100, 0b00101000, 0b00010000, 0b00101000, 0b01000100 },  //x 23
    { 0b01000100, 0b00101000, 0b00010000, 0b00010000, 0b00010000, 0b00010000 },  //y 24
    { 0b01111100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b01111100 },  //z 25
    { 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 },  //space 26
    { 0b00011000, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00011000 },  //0 27
    { 0b00001000, 0b00011000, 0b00001000, 0b00001000, 0b00001000, 0b00011100 },  //1 28
    { 0b00011000, 0b00100100, 0b00001000, 0b00010000, 0b00100000, 0b00111100 },  //2 29
    { 0b00011000, 0b00100100, 0b00001000, 0b00000100, 0b00100100, 0b00011000 },  //3 30
    { 0b00100100, 0b00100100, 0b00111100, 0b00000100, 0b00000100, 0b00000100 },  //4 31
    { 0b00111100, 0b00100000, 0b00111000, 0b00000100, 0b00100100, 0b00011000 },  //5 32
    { 0b00011100, 0b00100000, 0b00111000, 0b00100100, 0b00100100, 0b00011000 },  //6 33
    { 0b00111100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100 },  //7 34
    { 0b00011000, 0b00100100, 0b00011000, 0b00100100, 0b00100100, 0b00011000 },  //8 35
    { 0b00011000, 0b00100100, 0b00100100, 0b00011100, 0b00000100, 0b00011000 },  //9 36
    { 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00000000, 0b00001000 },  // ! 37
    { 0b00000000, 0b00011000, 0b00011000, 0b00000000, 0b00011000, 0b00011000 },  // : 38};
    { 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00010000 },  // , 39
    { 0b00011000, 0b00100100, 0b00001000, 0b00010000, 0b00000000, 0b00010000 },  // ? 40
    { 0b00000000, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b00000000 },  // / 41
    { 0b00000000, 0b00011000, 0b00011000, 0b00000000, 0b00001000, 0b00010000 },  // ; 42
    { 0b00000000, 0b00011000, 0b00111100, 0b00111100, 0b00011000, 0b00000000 },  // + 43
    { 0b00000000, 0b00000000, 0b00111100, 0b00111100, 0b00000000, 0b00000000 },  // - 44
    { 0b00000000, 0b00111100, 0b00111100, 0b00000000, 0b00111100, 0b00111100 },  // = 45
    { 0b00010000, 0b00001000, 0b00000100, 0b00000100, 0b00001000, 0b00010000 },  // ) 46
    { 0b00001000, 0b00010000, 0b00100000, 0b00100000, 0b00010000, 0b00001000 },  // ( 47
    { 0b00000000, 0b00001000, 0b00010000, 0b00100000, 0b00010000, 0b00001000 },  // < 48
    { 0b00000000, 0b00010000, 0b00001000, 0b00000100, 0b00001000, 0b00010000 },  // > 49
    { 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00011000 },  // . 50
  };




  for (int letter = 0; letter < n; letter++) {
    for (int row = 0; row < 6; row++) {
      for (int reps = 0; reps < 8; reps++) {
        for (int lvl = 0; lvl < 6; lvl++) {
          SR[6] = level[lvl];
          SR[5 - row] = alphabet[letters[letter]][5 - lvl];
          shift_out();

          HAL_Delay(1);
          clear_out();
          
        }
       
      }
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
   
  }
	
	
}
bool checkSignalON() {
	
  //uint8_t a = HAL_GPIO_ReadPin(GPIOB,btn_on_Pin);

	buttonStatus_on = HAL_GPIO_ReadPin(GPIOB,btn_on_Pin);
	
	//HAL_UART_Receive(&huart1, (uint8_t*)buffer, 50, 10);
	
	if (buttonStatus_on == 1 ||   strcmp(buffer, "on_off") == 0 ||  strcmp(buffer, "on") == 0){
		return true;
	}

	memset(buffer, 0, 50);
  return false;
}


void turn_on(){
	HAL_GPIO_WritePin(GPIOB, GREEN_PIN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BLUE_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin, GPIO_PIN_RESET);
	
	if(mode == 0){
		mode0_next();
	}else {
		mode1_next();
	}

}

void turn_off() {
  
  HAL_GPIO_WritePin(GPIOB, GREEN_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BLUE_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED_PIN_Pin, GPIO_PIN_SET);
	 clear_out();
  while (true) {	
			buttonStatus_on = HAL_GPIO_ReadPin(GPIOB,btn_on_Pin);
		
			if (buttonStatus_on == 1){		
					break;
			}
				if(chOn == true){
					chOn =  false;
					buttonStatus_on = 1;
					HAL_UART_Receive_IT(&huart1, (uint8_t*)&received_char, 1);
					break;
				}
  }

   perform();
	
}

////function effect

void normal_mode0(){
 full(5000);
  if (haveSignal) {
    return;
  }
  single_random(50);
  if (haveSignal) {
    return;
  }
  GrowingCube(10);

  if (haveSignal) {
    return;
  }
  rain();

  if (haveSignal) {
    return;
  }
  x_snake();
  if (haveSignal) {
    return;
  }
  y_stretched();
  if (haveSignal) {
    return;
  }
  x_trail();
  if (haveSignal) {
    return;
  }
  for (int j = 0; j < 5; j++) {
    spiral();
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }
  for (int j = 0; j < 10; j++) {
    random_on();
    if (haveSignal) {
      break;
    }
    random_off();
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }

  for (int j = 0; j < 7; j++) {
    random2x2();
    if (haveSignal) {
      break;
    }
    random3x3();
    if (haveSignal) {
      break;
    }
    random4x4();
    if (haveSignal) {
      break;
    }
    random5x5();
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }
  for (int k = 0; k < 10; k++) {
    x();
    if (haveSignal) {
      break;
    }
    y();
    if (haveSignal) {
      break;
    }
    z();
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }
  sun();
  if (haveSignal) {
    return;
  }
  dynamicNoise(500);
  if (haveSignal) {
    return;
  }
  random_yz();
  for (int k = 0; k < 10; k++) {
    frame2x2();
    if (haveSignal) {
      break;
    }
    frame4x4();
    if (haveSignal) {
      break;
    }
    frame6x6();
    if (haveSignal) {
      break;
    }
    frame6x6();
    if (haveSignal) {
      break;
    }
    frame4x4();
    if (haveSignal) {
      break;
    }
    frame2x2();
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }
  full(10000);
  if (haveSignal) {
    return;
  }



};
void random_yz(){
for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 6; j++) {
       SR[6] = (uint8_t)(rand() % 128 + 129);

     SR[j] = (uint8_t)(rand() % 256);
    }
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }

    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }



};
void dynamicNoise(int duration){
 for (int i = 0; i < duration; i++) {
    for (int j = 0; j < 6; j++) {
			SR[6] = 0b10000001;
       SR[j] = (uint8_t)(rand() % 256);
    }
    shift_out();
    HAL_Delay(80);

    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
};
void full(int t){
	
	
	
	for (int i = 0; i < 6; i++) {
    SR[i] = 0b11111111;
  }
  SR[6] = 0b00000000;
  shift_out();
  for (int j = 0; j < t / 50; j++) {
	
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
  }
};



	

void random_on(){
	int leds[216];
	uint8_t cube[36] = {0};

  
    for (int i = 0; i < 216; i++) {
        leds[i] = i;
    }

    int count = 216;
    for (int i = 0; i < count; i++) {
        int n = rand() % count; 
        int temp = leds[i];
        leds[i] = leds[n];
        leds[n] = temp;
    }

    for (int j = 0; j < 216; j++) {
        int ledIndex = leds[j];
        int b = ledIndex / 6;
        cube[b] |= (1 << (ledIndex - b * 6)); 

        for (int reps = 0; reps < 2; reps++) {
            for (int k = 0; k < 6; k++) {
                 SR[6] = level[k];
									int base = k * 6;
								SR[0] = cube[base];
								SR[1] = cube[base + 1];
								SR[2] = cube[base + 2];
								SR[3] = cube[base + 3];
								SR[4] = cube[base + 4];
								SR[5] = cube[base + 5];
								shift_out();
								delayMicroseconds(1);
								clear_out();
            }
        }

        checkSignal();
        if (haveSignal) {
            break;
        }
    }
};
void random_off(){
		  uint8_t cube[36];
  for (int i = 0; i < 36; i++) {
    cube[i] = 0b11111111;  
  }

  int leds[216];
  for (int i = 0; i < 216; i++) {
    leds[i] = i;  
  }

  int count = 216;
  for (int i = 0; i < count; i++) {
   int n = rand() % (count - i) + i; 
    int temp = leds[i];
    leds[i] = leds[n];
    leds[n] = temp;
  }

  for (int j = 0; j < 216; j++) {
    int ledIndex = leds[j];
    int b = ledIndex / 6;
    if (low) {
    cube[b] |= (1 << (ledIndex - b * 6 + 1)); 
		} else {
    cube[b] &= ~(1 << (ledIndex - b * 6 + 1)); 
		}
    for (int reps = 0; reps < 2; reps++) {
      for (int k = 0; k < 6; k++) {
        SR[6] = level[k];
        int base = k * 6;
        SR[0] = cube[base];
        SR[1] = cube[base + 1];
        SR[2] = cube[base + 2];
        SR[3] = cube[base + 3];
        SR[4] = cube[base + 4];
        SR[5] = cube[base + 5];
        shift_out();
        delayMicroseconds(1);
        clear_out();
      }
    }
    checkSignal();
    if (haveSignal) {
      return;
    }
  }
};
void single_random(int t){
	for (int i = 0; i < t ; i++) {

    SR[6] = level[rand() % 6];
    SR[rand() % 6] = single_on[rand() % 6];
    shift_out();
    //delayMicroseconds(100);
		 HAL_Delay(200);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }

};
void x(){
	SR[6] = low;
  for (int i = 0; i < 6; i++) {
    SR[0] = SR[1] = SR[2] = SR[3] = SR[4] = SR[5] = single_on[i];
    shift_out();

    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
  }
  for (int j = 0; j < 6; j++) {
    SR[0] = SR[1] = SR[2] = SR[3] = SR[4] = SR[5] = single_on[5 - j];
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
  }



};

void y(){
  for (int i = 0; i < 6; i++) {
    SR[i] = high;
  }
  for (int j = 0; j < 6; j++) {
    SR[6] = level[j];
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
  }
  for (int k = 0; k < 6; k++) {
    SR[6] = level[5 - k];
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
  }
};
void z(){
	clear_out();
  for (int i = 0; i < 6; i++) {
    SR[6] = low;
    SR[i] = high;
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
  for (int i = 0; i < 6; i++) {
    SR[6] = low;
    SR[5 - i] = high;
    shift_out();
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }

};	
void x_snake(){
	 for (int k = 1; k <= 10; k++) {

    SR[6] = low;
      uint8_t one = 0b00000000;
    uint8_t two = 0b00000000;
    int row = 0;

    for (int b = 0; b < 42; b++) {
      if (row < floor(b / 6)) {
        row = floor(b / 6);
        two = one;
        one = 0b00000000;
      }
      if (row % 2 == 0) {
        one |= (1 << (b - row * 6 + 1));
            two &= ~(1 << (6 - (b - row * 6)));
      } else {
       
				one |= (1 << (6 - (b - row * 6)));
          two &= ~(1 << (b - row * 6 + 1));
      }
      if (row < 6) {
        SR[row] = one;
      }
      if (row > 0) {
        SR[row - 1] = two;
      }
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
  }
};
void y_stretched(){
 for (int t = 0; t <= 10; t++) {
    uint8_t hi = 0b11111111;

    for (int i = 0; i < 6; i++) {
      SR[i] = hi;
    }
    for (int j = 1; j < 7; j++) {
       hi &= ~(1 << j);
      SR[6] = hi;
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
    for (int j = 1; j < 7; j++) {
      hi |= (1 << j);
      SR[6] = hi;
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
    for (int k = 1; k < 7; k++) {
      hi &= ~(1 << (7 - k));
      SR[6] = hi;
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
    for (int k = 1; k < 7; k++) {
      hi |= (1 << (7 - k));
      SR[6] = hi;
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
    clear_out();
  }
};
void x_trail(){
	int trail[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };
  const int count = sizeof trail / sizeof trail[0];

  for (int k = 1; k <= 10; k++) {


    for (int i = 0; i < count; i++) {
     int n = rand() % count;
      int temp = trail[n];
      trail[n] = trail[i];
      trail[i] = temp;
    }
    int n = 0;
    int m = 0;
    int show_end_longer = 10;
    for (int h = 0; h < 6; h++) {
      n = h * 3;
      m = h * 36;
      trail[n] += m;
      trail[n + 1] += m;
      trail[n + 2] += m;
      if (h == 5) {
        show_end_longer = 120;
      }
      for (int reps = 0; reps < show_end_longer; reps++) {
        for (int j = 0; j < 6; j++) {
          SR[6] = level[j];
          SR[0] = SR[1] = SR[2] = SR[3] = SR[4] = SR[5] = single_on[h];
          for (int k = 0; k < n; k++) {
            int a = floor(trail[k] / 36);
            int b = trail[k] - a * 36;
            int c = floor(b / 6);
            if ((b - c * 6) == j) {
              SR[c] = 0b00000000;
             SR[c] |= (1 << (6 - a));
            }
          }
          shift_out();
          delayMicroseconds(1);

          checkSignal();
          if (haveSignal) {
            return;
          }
          clear_out();
        }
      }
    }
  }
	
};
void sun(){
clear_out();
  for (int i = 0; i < 9999; i++) {
    int a = floor(i / 80);
    SR[6] = 0b11011011;
    SR[2] = SR[3] = 0b00011000;
    if (a % 4 > 0) {
      SR[1] = SR[4] =0b00100100;
    }
    shift_out();
    delayMicroseconds(1);
    clear_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
    if (a % 4 == 2) {
      SR[6] = 0b10111101;
      SR[0] = SR[5] = 0b01000010;
      shift_out();
      delayMicroseconds(1);
      clear_out();
    }
    SR[6] =0b11100111;
    SR[2] = SR[3] = 0b00111100;
    SR[1] = SR[4] =0b00011000;
    shift_out();
    delayMicroseconds(1);

    clear_out();

    checkSignal();
    if (haveSignal) {
      return;
    }
  }

};
void spiral(){
	for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 20; j++) {
      SR[6] = level[i];
      if (j < 6) {
        SR[0] = single_on[j];
      } else if (9 < j && j < 16) {
        SR[5] = single_on[6 - (j - 9)];
      } else {
        if (j < 10) {
          SR[j - 5] = single_on[5];
        } else {  //16-19
          SR[6 - (j - 14)] = single_on[0];
        }
      }
      shift_out();
      HAL_Delay(50);


      clear_out();
      checkSignal();
      if (haveSignal) {
        break;
      }
    }
    if (haveSignal) {
      break;
    }
  }

  if (haveSignal) {
    return;
  }

};	
void rain(){
	 int raindrops_x[6]; 
    int raindrops_z[6]; 
	 
	for (int i = 0; i < 6; i++) {
        raindrops_x[i] = rand() % 6; 
        raindrops_z[i] = rand() % 6; 
    }
	
	
  for (int i = 0; i < 350; i++) {
    for (int j = 0; j < 36; j++) {
      int k = j % 6;
      SR[6] = level[k];
      SR[raindrops_z[k]] = single_on[raindrops_x[k]];
      shift_out();
      HAL_Delay(1);
      clear_out();
			 checkSignal();
      if (haveSignal) {
        break;
      }
    }
		
		 checkSignal();
      if (haveSignal) {
        break;
      }

    raindrops_x[5] = raindrops_x[4];
    raindrops_x[4] = raindrops_x[3];
    raindrops_x[3] = raindrops_x[2];
    raindrops_x[2] = raindrops_x[1];
    raindrops_x[1] = raindrops_x[0];
    raindrops_x[0] = rand() % 6;
    raindrops_z[5] = raindrops_z[4];
    raindrops_z[4] = raindrops_z[3];
    raindrops_z[3] = raindrops_z[2];
    raindrops_z[2] = raindrops_z[1];
    raindrops_z[1] = raindrops_z[0];
    raindrops_z[0] = rand() % 6;
  }
};


void GrowingCube(int n){
	bool previous[] = {};
  for (int a = 0; a < n; a++) {
    uint8_t lvl = 0b11111111;
    uint8_t row = 0b00000000;
     bool corner[3]; 
   
    for (int i = 0; i < 3; i++) {
        corner[i] = rand() % 2; 
    }
    for (int i = 0; i < 7; i++) {
      int L = 0;
      if (corner[0] == 0) {
        L = 7 - i;
      } else {
        L = i;
      }
     lvl &= ~(1 << L);
      int r = 0;
      if (corner[1] == 0) {
        r = 7 - i;
      } else {
        r = i;
      }
      row |= (1 << r);
      int d = 0;
      if (corner[2] == 0) {
        d = 5 - i;
        for (int v = 5; v > d; v--) {
          SR[v] = row;
        }
      } else {
        d = i;
        for (int w = 0; w < d; w++) {
          SR[w] = row;
        }
      }


      SR[6] = lvl;
      shift_out();

      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }

      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }

      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }

      clear_out();
    }
    if (haveSignal) {
      return;
    }
    corner[0] = rand() % 2;
    corner[1] = rand() % 2;
    corner[2] = rand() % 2;
    for (int i = 6; i >= 0; i--) {
      int L = 0;
      if (corner[0] == 0) {
        L = 7 - i;
      } else {
        L = i;
      }
     lvl |= (1 << L);
      int r = 0;
      if (corner[1] == 0) {
        r = 7 - i;
      } else {
        r = i;
      }
      row &= ~(1 << r);
      int d = 0;
      if (corner[2] == 0) {
        d = 5 - i;
        for (int v = 5; v > d; v--) {
          SR[v + 1] = row;
        }
      } else {
        d = i;
        for (int w = 0; w < d; w++) {
          SR[w - 1] = row;
        }
        haveSignal = false;
      }
      SR[6] = lvl;
      shift_out();
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }
      HAL_Delay(50);
      checkSignal();
      if (haveSignal) {
        break;
      }
      clear_out();
    }
    if (haveSignal) {
      break;
    }
  }
  if (haveSignal) {
    return;
  }

};
void frame4x4(){
	 for (int k = 0; k < 200; k++) {
    SR[6] = 0b11011011;
    SR[1] = SR[4] = 0b00111100;
    SR[2] = SR[3] = 0b00100100;
    shift_out();
    delayMicroseconds(3);
   clear_out();
    if (haveSignal) {
      return;
    }
   

    SR[6] = 0b11100111;
    SR[1] = SR[4] = 0b00100100;
    shift_out();
   
    clear_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
    delayMicroseconds(3);
  }
};
void frame2x2(){
int k;
  for (k = 0; k < 200; k++) {
    SR[6] = 0b1100111;
    // SR[3] = SR[4] = 0b00011000;
    SR[2] = SR[3] = 0b00011000;
    shift_out();
    delayMicroseconds(3);
  
    checkSignal();
    if (haveSignal) {
      return;
    }
  


 
    
    checkSignal();
    if (haveSignal) {
      return;
    }
    delayMicroseconds(3);
  }

};


void frame6x6() {
  int k;
  for (k = 0; k < 200; k++) {
    SR[6] = 0b10111101;
    SR[0] = SR[5] = high;
    SR[1] = SR[2] = SR[3] = SR[4] = 0b01000010;

    shift_out();
    delayMicroseconds(3);
    clear_out();
    checkSignal();
    if (haveSignal) {
      return;
    }

    SR[6] = 0b11000011;
    SR[0] = SR[5] = 0b01000010;
    shift_out();
    delayMicroseconds(3);
    clear_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
  }
}






void random2x2() {
  int LEVEL2[5] = { 0b10011111, 0b11001111, 0b11100111, 0b11110011,0b11111001 };

  int ROW2[5] = { 0b01100000, 0b00110000, 0b00011000, 0b00001100, 0b00000110 };
  for (int k = 0; k < 30; k++) {
    int SRrandom = rand() % 5;

    SR[6] = LEVEL2[rand() % 5];
    SR[SRrandom] = SR[SRrandom + 1] = ROW2[rand() % 5];
    shift_out();

    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }


    clear_out();
  }
}

void random3x3() {

  int LEVEL3[4] = { 0b10001111, 0b11000111, 0b11100011, 0b11110001 };
  int ROW3[4] = { 0b01110000, 0b00111000, 0b00011100, 0b00001110 };
  int SRrandom;
  for (int k = 0; k < 30; k++) {
    SRrandom = rand() % 4;

    SR[6] = LEVEL3[rand() % 4];
    SR[SRrandom] = SR[SRrandom + 1] = SR[SRrandom + 2] = ROW3[rand() % 4];
    shift_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
}

void random4x4() {
  int LEVEL4[3] = { 0b10000111, 0b11000011, 0b11100001 };

  int ROW4[3] = { 0b01111000, 0b00111100, 0b00011110 };
  for (int k = 0; k < 30; k++) {
    int SRrandom = rand() % 3;

    SR[6] = LEVEL4[rand() % 3];
    SR[SRrandom] = SR[SRrandom + 1] = SR[SRrandom + 2] = SR[SRrandom + 3] = ROW4[rand() % 3];
    shift_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
}

void random5x5() {
  int LEVEL5[2] = { 0b10000011, 0b11000001 };

  int ROW5[2] = { 0b01111100, 0b00111110 };
  for (int k = 0; k < 30; k++) {
    int SRrandom = rand() % 2;

    SR[6] = LEVEL5[rand() % 2];
    SR[SRrandom] = SR[SRrandom + 1] = SR[SRrandom + 2] = SR[SRrandom + 3] = SR[SRrandom + 4] = ROW5[rand() % 2];
    shift_out();
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(50);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
}






/// sound
void sound_mode0(){
  uint32_t  currentMillis =	HAL_GetTick();
      uint32_t  previousMillis = HAL_GetTick();
  while (currentMillis - previousMillis <= 30000) {
    flashLEDs();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 30000) {

    adjustBrightness();
    checkSignal();
    if (haveSignal) {
      return;
    }
   currentMillis = HAL_GetTick();
  }

  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 30000) {
    soundResponsiveBlink();
    checkSignal();
    if (haveSignal) {
      return;
    }
    currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 30000) {
    soundFrame();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 30000) {
    soundResponsiveEffect2();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 30000) {
    soundFloorJumping();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner1();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;

  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner2();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner3();
    checkSignal();
    if (haveSignal) {
      return;
    }
    currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner4();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner5();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner6();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner7();
    checkSignal();
    if (haveSignal) {
      return;
    }
    currentMillis = HAL_GetTick();
  }
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= 15000) {
    soundFrameCorner8();
    checkSignal();
    if (haveSignal) {
      return;
    }
     currentMillis = HAL_GetTick();
  }

};
void flashLEDs(){
	sound_value = getValue();
  if (sound_value > soundThreshold) {

    for (int i = 0; i < 6; i++) {
      SR[i] =0b11111111;
    }
    SR[6] = 0b00000000;
    shift_out();
    HAL_Delay(50);

   
  }else{
		clear_out();
		}
	 
};
void adjustBrightness(){
		
  SR[0] = 0b11111111;
  SR[1] = 0b11111111;
  SR[2] = 0b11111111;
  SR[3] = 0b11111111;
  SR[4] = 0b11111111;
  SR[5] = 0b11111111;
	sound_value = getValue();
  if (sound_value >= soundThreshold) {
    for (int i = 0; i < 6; i++) {
      SR[i] = 0b11111111;
      SR[6] = level[i];
    
      shift_out();
      HAL_Delay(50);
    }
  } else {
    clear_out();
  }
};
void soundFrame(){
		
  sound_value = getValue();
  if (sound_value >= soundThreshold && sound_value < soundThreshold + 35) {
    SR[6] = 0b1100111;

    SR[2] = SR[3] = 0b00011000;
    shift_out();


    HAL_Delay(50);

  } else if (sound_value >= soundThreshold + 35 && sound_value < soundThreshold + 70) {
    SR[6] = 0b11000011;
    SR[1] = SR[4] = 0b00111100;
    SR[2] = SR[3] = 0b00111100;
    shift_out();
    HAL_Delay(50);

  } else if (sound_value >= soundThreshold + 105) {
    for (int i = 0; i < 6; i++) {
      SR[i] = 0b11111111;
    }
    SR[6] = 0b00000000;
    shift_out();
    HAL_Delay(50);


  } else {
    clear_out();
  }
};
void soundResponsiveEffect2(){

	 
 sound_value = getValue();
  if (sound_value >= soundThreshold) {
    for (int i = 0; i < 6; i++) {
      SR[6] = 0b10000000 >> i;
      int numLEDsToLight = ((sound_value - soundThreshold ) * 36) /100;
      for (int j = 0; j < numLEDsToLight; j++) {
				int randomLED = rand() % 36;
         SR[randomLED / 6] |= (1 << (randomLED % 6 + 1));
      }
      shift_out();
      HAL_Delay(50);
      clear_out();
      checkSignal();
      if (haveSignal) {
        return;
      }
    }
  }else {
		
		clear_out();
	}
  if (haveSignal) {
    return;
  }


};
void soundFloorJumping(){
	
  
  SR[0] = 0b01111110;
  SR[1] = 0b01111110;
  SR[2] = 0b01111110;
  SR[3] = 0b01111110;
  SR[4] = 0b01111110;
  SR[5] = 0b01111110;
sound_value = getValue();
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 10) {
      SR[6] = 0b10111111;
    } else if (sound_value <= soundThreshold + 40) {
      SR[6] = 0b10011111;
    } else if (sound_value <= soundThreshold + 70) {
      SR[6] = 0b10001111;
    } else if (sound_value <= soundThreshold + 100) {
      SR[6] = 0b10000111;
    } else if (sound_value <= soundThreshold + 130) {
      SR[6] = 0b10000011;
    } else {
      SR[6] = 0b10000001;
    }
  } else {
    SR[6] = 0b11111111;
  }
  shift_out();
  HAL_Delay(50);

};
void soundResponsiveBlink(){
	sound_value = getValue();
  if (sound_value > soundThreshold) {  

    for (int i = 0; i < 6; i++) {
      SR[i] =rand() % 256; 
    }
    SR[6] = 0b00000000;
    shift_out();

    HAL_Delay(90);
    checkSignal();
    if (haveSignal) {
      return;
    }
    HAL_Delay(90);
    checkSignal();
    if (haveSignal) {
      return;
    }
    clear_out();
  }
  checkSignal();
  if (haveSignal) {
    return;
  }
};
void soundFrameCorner1(){
	sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b10011111;
      SR[0] = 0b01100000;
      SR[1] = 0b01100000;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b10001111;
      SR[0] = 0b01110000;
      SR[1] = 0b01110000;
      SR[2] = 0b01110000;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b10000111;
      SR[0] = 0b01111000;
      SR[1] = 0b01111000;
      SR[2] = 0b01111000;
      SR[3] = 0b01111000;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b10000011;
      SR[0] = 0b01111100;
      SR[1] = 0b01111100;
      SR[2] = 0b01111100;
      SR[3] = 0b01111100;
      SR[4] = 0b01111100;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
 
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};	
void soundFrameCorner5(){
	sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b11111001;
      SR[0] = 0b01100000;
      SR[1] = 0b01100000;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b11110001;
      SR[0] = 0b01110000;
      SR[1] = 0b01110000;
      SR[2] = 0b01110000;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b11100001;
      SR[0] = 0b01111000;
      SR[1] = 0b01111000;
      SR[2] = 0b01111000;
      SR[3] = 0b01111000;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b11000001;
      SR[0] = 0b01111100;
      SR[1] = 0b01111100;
      SR[2] = 0b01111100;
      SR[3] = 0b01111100;
      SR[4] = 0b01111100;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};
void soundFrameCorner2(){
	sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b10011111;
      SR[0] = 0b00000110;
      SR[1] = 0b00000110;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b10001111;
      SR[0] = 0b00001110;
      SR[1] = 0b00001110;
      SR[2] = 0b00001110;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b10000111;
      SR[0] = 0b00011110;
      SR[1] = 0b00011110;
      SR[2] = 0b00011110;
      SR[3] = 0b00011110;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b10000011;
      SR[0] = 0b00111110;
      SR[1] = 0b00111110;
      SR[2] = 0b00111110;
      SR[3] = 0b00111110;
      SR[4] = 0b00111110;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);

};
void soundFrameCorner6(){
sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b11111001;
      SR[0] = 0b00000110;
      SR[1] = 0b00000110;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b11110001;
      SR[0] = 0b00001110;
      SR[1] = 0b00001110;
      SR[2] = 0b00001110;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b11100001;
      SR[0] = 0b00011110;
      SR[1] = 0b00011110;
      SR[2] = 0b00011110;
      SR[3] = 0b00011110;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b11000001;
      SR[0] = 0b00111110;
      SR[1] = 0b00111110;
      SR[2] = 0b00111110;
      SR[3] = 0b00111110;
      SR[4] = 0b00111110;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};
void soundFrameCorner3(){
	sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b10011111;
      SR[5] = 0b00000110;
      SR[4] = 0b00000110;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b10001111;
      SR[5] = 0b00001110;
      SR[4] = 0b00001110;
      SR[3] = 0b00001110;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b10000111;
      SR[5] = 0b00011110;
      SR[4] = 0b00011110;
      SR[3] = 0b00011110;
      SR[2] = 0b00011110;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b10000011;
      SR[5] = 0b00111110;
      SR[4] = 0b00111110;
      SR[3] = 0b00111110;
      SR[2] = 0b00111110;
      SR[1] = 0b00111110;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};
void soundFrameCorner7(){
	sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b11111001;
      SR[5] = 0b00000110;
      SR[4] = 0b00000110;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b11110001;
      SR[5] = 0b00001110;
      SR[4] = 0b00001110;
      SR[3] = 0b00001110;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b11100001;
      SR[5] = 0b00011110;
      SR[4] = 0b00011110;
      SR[3] = 0b00011110;
      SR[2] = 0b00011110;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b11000001;
      SR[5] = 0b00111110;
      SR[4] = 0b00111110;
      SR[3] = 0b00111110;
      SR[2] = 0b00111110;
      SR[1] = 0b00111110;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};
void soundFrameCorner4(){
sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b10011111;
      SR[5] = 0b01100000;
      SR[4] = 0b01100000;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b10001111;
      SR[5] = 0b01110000;
      SR[4] = 0b01110000;
      SR[3] = 0b01110000;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b10000111;
      SR[5] = 0b01111000;
      SR[4] = 0b01111000;
      SR[3] = 0b01111000;
      SR[2] = 0b01111000;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b10000011;
      SR[5] = 0b01111100;
      SR[4] = 0b01111100;
      SR[3] = 0b01111100;
      SR[2] = 0b01111100;
      SR[1] = 0b01111100;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
    // shift_out();
    // HAL_Delay(50);
    // checkSignal();
    // if (haveSignal) {
    //   return;
    // }
  } else {

    SR[6] = 0b11111111;
    // clear_out();
  }
  shift_out();
  HAL_Delay(50);
};
void soundFrameCorner8(){
sound_value = getValue();
  SR[0] = 0b00000000;
  SR[1] = 0b00000000;
  SR[2] = 0b00000000;
  SR[3] = 0b00000000;
  SR[4] = 0b00000000;
  SR[5] = 0b00000000;
  if (sound_value >= soundThreshold) {
    if (sound_value <= soundThreshold + 30) {
      SR[6] = 0b11111001;
      SR[5] = 0b01100000;
      SR[4] = 0b01100000;
    } else if (sound_value <= soundThreshold + 60) {
      SR[6] = 0b11110001;
      SR[5] = 0b01110000;
      SR[4] = 0b01110000;
      SR[3] = 0b01110000;
    } else if (sound_value <= soundThreshold + 90) {
      SR[6] = 0b11100001;
      SR[5] = 0b01111000;
      SR[4] = 0b01111000;
      SR[3] = 0b01111000;
      SR[2] = 0b01111000;
    } else if (sound_value <= soundThreshold + 120) {
      SR[6] = 0b11000001;
      SR[5] = 0b01111100;
      SR[4] = 0b01111100;
      SR[3] = 0b01111100;
      SR[2] = 0b01111100;
      SR[1] = 0b01111100;
    } else {
      SR[6] = 0b10000001;
      SR[0] = 0b01111110;
      SR[1] = 0b01111110;
      SR[2] = 0b01111110;
      SR[3] = 0b01111110;
      SR[4] = 0b01111110;
      SR[5] = 0b01111110;
    }
  
  } else {

    SR[6] = 0b11111111;
    
  }
  shift_out();
  HAL_Delay(50);
};


void delayMicroseconds(uint32_t us) {
    uint32_t ms = us / 1000;
    HAL_Delay(ms);
    us = us % 1000;
    if (us > 0) {
        uint32_t startTick = HAL_GetTick();
        while ((HAL_GetTick() - startTick) < us) {
        }
    }
}
	
uint32_t  getValue(){
	HAL_ADC_Start(&hadc1); 
	uint32_t var = HAL_ADC_GetValue(&hadc1);
	
	return var;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
