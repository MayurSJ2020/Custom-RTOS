
#include "main.h"
#include "bsp.h"
#include "Myrtos.h"


void System_Initialize(void);

//Stack for different tasks

uint32_t orange_task[40];
uint32_t green_task[40];
uint32_t blue_task[40];


OS_Task Task1;
OS_Task Task2;
OS_Task Task3;


int main(void)
{

	OS_Init();

	OS_start(&Task1, &Toggle_blue_led,22U, blue_task, sizeof(blue_task));
	OS_start(&Task2, &Toggle_green_led,10U, green_task, sizeof(green_task));
	OS_start(&Task3, &Toggle_orange_led,5U, orange_task, sizeof(orange_task));


	System_Initialize();

	while(1);


}



void System_Initialize(void)
{


	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
}





void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

