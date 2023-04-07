# Custom-RTOS
Developing a Custom RTOS which schedules the Task based on given priority and can be changed at any point of time. It also has blocking delay function which will not waste any CPU cycle which calls Idle task where we can put device to sleep to save power. We can add N number of task if we need in future and can set priority based on Hard and Soft events which has to meet with deadline of execution.

Uploaded a trace using Logic analyzer which helps to analyze how tasks behave when all tasks are ready to run.

The tasks are scheduled when Systick interrupt triggers and it sets pending bit for PendSV if next scheduled task is available based on priority. Systick interval is set to 1ms in my project
