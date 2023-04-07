# Custom-RTOS
Developing a RTOS which schedules different tasks based on priority assigned. It can handle multiple tasks and schedules the most priority one when it is ready to run and can preampt the current running task and will continue its running after completing the most priority tasks. It also has delay function which do not utilize any cpu cycle and calls Idle task function where we can put device to sleep in that idle task as most of the time it spends it time in IDLE task. Switching between tasks is achieved using PendSV handler which is triggred by SysTick handler if we have any Task ready to run. Private Stack is used to save the contents of current running tasks before switching to next task.

Uploaded a trace using Logic analyzer which helps to analyze how tasks behave when all tasks are ready to run.

The tasks are scheduled when Systick interrupt triggers and it sets pending bit for PendSV if next scheduled task is available based on priority. Systick interval is set to 1ms in my project
