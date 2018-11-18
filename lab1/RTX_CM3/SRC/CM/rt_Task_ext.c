/**
* @file: rt_Task_ext.c
*/
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"
/*----------------------- rt_tsk_count_get --------------------------*/
/* added for ECE254 lab */

int rt_tsk_count_get (void) {
	int i;
	int count = 0;
	for(i = 0; i < os_maxtaskrun; i++ ){
		if(os_active_TCB[i] != NULL){
			count++;
		}	
  }
if( os_idle_TCB.state != INACTIVE){
	count++;
}
return count;
}
/*----------------------- rt_tsk_get --------------------------------*/
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	U16 default_stack_size;
	U16 stack_usage;
	P_TCB output;
	if(task_id > os_maxtaskrun || task_id < 0)
		return OS_R_NOK;
	else{
		 output = os_active_TCB[task_id - 1]; 
		p_task_info -> state = output -> state;
		p_task_info -> prio = output -> prio;
		p_task_info -> task_id = task_id;
		p_task_info -> ptask = output -> ptask;
		
		//Calculate Stack Usage
		
		default_stack_size = (U16)os_stackinfo + (U16)output->stack;
	
		if(output->state!=RUNNING)
			stack_usage = default_stack_size - (U16)output->tsk_stack;
		else
			stack_usage = default_stack_size - (U16)rt_get_PSP();
		
		p_task_info -> stack_usage = (100*stack_usage)/ (U16)os_stackinfo;
  }
	
	return OS_R_OK;
}
/* end of file */
