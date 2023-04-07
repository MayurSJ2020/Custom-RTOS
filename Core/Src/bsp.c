/*
 * bsp.c
 *
 *  Created on: 01-Apr-2023
 *      Author: 007ma
 */
#include "bsp.h"
#include "main.h"
#include "Myrtos.h"
//Tasks for RTOS
void Toggle_green_led(void)
{
	while(1)
	{
	for(int i=0;i<100;i++)
	{
	HAL_GPIO_WritePin(LED_PORT, GREEN_LED_PIN, GPIO_PIN_SET);
	//OS_Delay(25);
	HAL_GPIO_WritePin(LED_PORT, GREEN_LED_PIN, GPIO_PIN_RESET);
	//OS_Delay(60);
	}
	OS_Delay(50);
	}
}

void Toggle_orange_led(void)
{
	while(1)
	{
	for(int i=0;i<600;i++)
	{
	HAL_GPIO_WritePin(LED_PORT, ORANGE_LED_PIN, GPIO_PIN_SET);
	//OS_Delay(25);
	HAL_GPIO_WritePin(LED_PORT, ORANGE_LED_PIN, GPIO_PIN_RESET);

	}
	OS_Delay(5);
	}
}

void Idle_Task(void)
{
	while(1)
	{

	HAL_GPIO_WritePin(LED_PORT, RED_LED_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);

	}

}

void Toggle_blue_led(void)
{

	while(1)
	{
	for(int i=0;i<300;i++)
	{

	HAL_GPIO_WritePin(LED_PORT, BLUE_LED_PIN, GPIO_PIN_SET);
	//OS_Delay(25);
	HAL_GPIO_WritePin(LED_PORT, BLUE_LED_PIN, GPIO_PIN_RESET);
	//OS_Delay(200);
	}
	OS_Delay(100);
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


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
}

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void SysTick_Handler(void)
{

  HAL_IncTick();
  Os_Tick();
  __disable_irq();
  OS_schedule();
  __enable_irq();

}


