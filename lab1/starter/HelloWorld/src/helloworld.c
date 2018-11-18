/**
* @file: helloworld.c
* @brief: Two simple tasks running pseduo-parallelly
*/
#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"
#include "../../../RTX_CM3/INC/RTL_ext.h"


__task void task0()
{
int num;

// ...
num = rt_tsk_count_get();
printf("number of tasks: %d.\n", num);
// ...

}
__task void task1()
{

while(1){
int j;
RL_TASK_INFO print1;
	rt_tsk_get(-1, &print1);
for( j = 0; j <= rt_tsk_count_get(); j++){
	OS_RESULT output = rt_tsk_get(j, &print1);
	if(output == OS_R_NOK){
		printf("ERROR");
	}
	else{
		printf("task_id: %d\n", print1.task_id );
		printf("state: %d\n", print1.state );
		printf("prio: %d\n", print1.prio );
		printf("ptask: %d\n", print1.ptask );
		printf("Stack usage: %d\n", print1.stack_usage );
	}
}
os_dly_wait(60);
}

}
__task void task2()
{
unsigned int i = 0;
for(;; i++)
{
printf("Task2: %d\n", i);
os_dly_wait(100);
}
}
__task void task3()
{
while(1)
{

printf("Task3: HelloWorld!\n");
os_dly_wait(300);
}
}
__task void task4()
{
while(1)
{

printf("Task4: This is another Task for testing\n");
os_dly_wait(300);
}
}
__task void init(void)
{
os_tsk_create(task0, 1); // task0 at priority 1
os_tsk_create(task1, 1); // task1 at priority 1
os_tsk_create(task2, 1); // task2 at priority 1
os_tsk_create(task3, 1); // task3 at priority 1
os_tsk_create(task4, 1); // task4 at priority 1
os_tsk_delete_self(); // must delete itself before exiting
}
int main ()

{
SystemInit();
uart0_init();
os_sys_init(init);
}
