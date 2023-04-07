/*
 * Myrtos.h
 *
 *  Created on: 01-Apr-2023
 *      Author: 007ma
 */

#ifndef INC_MYRTOS_H_
#define INC_MYRTOS_H_

#include "stdint.h"
#include "main.h"
#include "bsp.h"

typedef void (*fun)();

void OS_schedule();
void OS_Init();
void OS_Delay(uint8_t delay);
void Os_Tick(void);

//TCB for the task
typedef struct
{
	void *sp;
	uint8_t delay;
	uint8_t prio;
}OS_Task;


void OS_start(
		OS_Task * me,  			//Pointer to TCB of the task
		fun MyFun,   			//Pointer to Task
		uint8_t priority,
		void * StackStart,		//Pointer to Start of stack for the task
		uint32_t SizeOfStack);  //Size of stack


#endif /* INC_MYRTOS_H_ */
