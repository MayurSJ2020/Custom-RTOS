/*
 * bsp.h
 *
 *  Created on: 01-Apr-2023
 *      Author: 007ma
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "main.h"

//Led pins to be used as tasks
#define GREEN_LED_PIN GPIO_PIN_12
#define ORANGE_LED_PIN GPIO_PIN_13
#define RED_LED_PIN GPIO_PIN_14
#define BLUE_LED_PIN GPIO_PIN_15

//Led port
#define LED_PORT GPIOD

void Toggle_green_led(void);
void Toggle_orange_led(void);
void Idle_Task(void);
void Toggle_blue_led(void);

void SystemClock_Config(void);
void MX_GPIO_Init(void);



#endif /* INC_BSP_H_ */
