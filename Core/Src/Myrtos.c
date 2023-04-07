/*
 * Myrtos.c
 *
 *  Created on: 01-Apr-2023
 *      Author: 007ma
 */

#include "Myrtos.h"


//uint8_t Thread_index; //Number of threads started so far
//uint8_t Current_index; //Current thread index

OS_Task * OS_threads[32]; //Pointers for TCB's of the task

OS_Task * CurrentThread; //Current thread which is running
OS_Task * NextThread; //Next thread which is to be scheduled

uint32_t ReadyToRun;
uint32_t IdleSet;

OS_Task Idle;
uint32_t red_task[40];

#define LOG2(x) (32 - __CLZ(x))

void OS_start(OS_Task * me,fun  threadHandler,uint8_t priority,void * StackStart,uint32_t SizeOfStack)
{
	uint32_t *sp = (uint32_t *)((((uint32_t)StackStart + SizeOfStack)/8) * 8);

	//Constructing the stack as per AAPCS without floating point unit
	*(--sp) = (1U << 24);  /* xPSR */
	*(--sp) = (uint32_t)threadHandler; /* PC */
	*(--sp) = 0x0000000EU; /* LR  */
	*(--sp) = 0x0000000CU; /* R12 */
	*(--sp) = 0x00000003U; /* R3  */
	*(--sp) = 0x00000002U; /* R2  */
	*(--sp) = 0x00000001U; /* R1  */
	*(--sp) = 0x00000000U; /* R0  */
	/* additionally, fake registers R4-R11 */
	*(--sp) = 0x0000000BU; /* R11 */
	*(--sp) = 0x0000000AU; /* R10 */
	*(--sp) = 0x00000009U; /* R9 */
	*(--sp) = 0x00000008U; /* R8 */
	*(--sp) = 0x00000007U; /* R7 */
	*(--sp) = 0x00000006U; /* R6 */
	*(--sp) = 0x00000005U; /* R5 */
	*(--sp) = 0x00000004U; /* R4 */

	me->sp = sp; // storing the value of Top of the stack

	//Assigning the pointer to schedule round robin fashion
	OS_threads[priority] = me;

	me->prio = priority;

	if(priority>0)
	{
	ReadyToRun |= (1<<(priority-1));
	}




}

__attribute__ ((naked, optimize("-fno-stack-protector")))
void PendSV_Handler(void) {
__asm volatile (



    /* __disable_irq(); */
    "  CPSID         I                 \n"

    /* if (CurrentThread != (OSThread *)0) { */
    "  LDR           r1,=CurrentThread       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  CBZ           r1,PendSV_restore \n"

    /*     push registers r4-r11 on the stack */
    "  PUSH          {r4-r11}          \n"

    /*     CurrentThread->sp = sp; */
    "  LDR           r1,=CurrentThread       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  STR           sp,[r1,#0x00]     \n"
    /* } */

    "PendSV_restore:                   \n"
    /* sp = NextThread->sp; */
    "  LDR           r1,=NextThread       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           sp,[r1,#0x00]     \n"

    /* CurrentThread = NextThread; */
    "  LDR           r1,=NextThread       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r2,=CurrentThread       \n"
    "  STR           r1,[r2,#0x00]     \n"

    /* pop registers r4-r11 */
    "  POP           {r4-r11}          \n"

    /* __enable_irq(); */
    "  CPSIE         I                 \n"

    /* return to the next thread */
    "  BX            lr                \n"
    );
}

void OS_schedule()
{
	OS_Task * next;

	if(ReadyToRun == 0)
	{
		next = OS_threads[0];
	}
	else
	{
		next = OS_threads[(LOG2(ReadyToRun))];

	}


	if(next != CurrentThread)
	{
		NextThread = next;
		//Triggering pendSV handler
		*(uint32_t volatile *)0xE000ED04 = (1U << 28);
	}
}

void OS_Init()
{
	OS_start(&Idle, &Idle_Task,0U, red_task, sizeof(red_task)); // Setting up idle task
	//Setting PendSV priority lowest so it does not preampt any other interrupts
	*((uint32_t volatile*)(0xE000ED20)) |= (0XFFU<<16);
}

void OS_Delay(uint8_t delay)
{
	__disable_irq();

	CurrentThread->delay = delay;
	ReadyToRun &= ~(1<<(CurrentThread->prio-1));
	IdleSet |= (1<<(CurrentThread->prio-1));
	OS_schedule();

	__enable_irq();
}

void Os_Tick(void)
{
	uint32_t temp = IdleSet;
	uint8_t index;
	while(temp != 0)
	{
		index = LOG2(temp);
		--OS_threads[(index)]->delay;
		if(OS_threads[(index)]->delay == 0)
		{
			ReadyToRun |= (1<<(index-1));
			IdleSet &= ~(1<<(index-1));
		}
		temp &= ~(1<<(index-1));
	}
}
