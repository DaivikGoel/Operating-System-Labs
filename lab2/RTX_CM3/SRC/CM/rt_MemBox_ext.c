/*----------------------------------------------------------------------------
 *      ECE254 Lab Task Management
 *----------------------------------------------------------------------------
 *      Name:    RT_MEMBOX_ext.C
 *      Purpose: Interface functions for blocking 
 *               fixed memory block management system
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code is extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/
 
/*----------------------------------------------------------------------------
 *      Includes
 *---------------------------------------------------------------------------*/
 
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_MemBox.h"
#include "rt_HAL_CM.h"
#include "rt_Task.h"       /* added in ECE254 lab keil_proc */ 
#include "rt_MemBox_ext.h" /* added in ECE254 lab keil_proc */

#include "rt_List.h"

/* ECE254 Lab Comment: You may need to include more header files */

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/
 #define WAIT_MEM 10
 
struct OS_XCB blocked_list;

/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/*==========================================================================*/
/*  The following are added for ECE254 Lab Task Management Assignmet       */
/*==========================================================================*/

/**  
 * os_mem_alloc(mem_pool) calls this function.
 * @brief: Request a block of memory from the memory pool and block the calling
 * 			task if no memory is available in the memory pool
 */
void *rt_mem_alloc (void *mem_pool) {
	// Check if memory pool has enough space
	void *test;
	P_TCB task;
	
	test = rt_alloc_box(mem_pool);
	if ( test == NULL){
		task = os_active_TCB[rt_tsk_self() - 1];
		rt_put_prio(&blocked_list, task);
		rt_block(0xFFFF, WAIT_MEM);
		return NULL;
	}
	else{
		return test;
	}

}
		
/**
 * os_mem_free(mem_pool, box) calls this function.
 * free the memory pointed by box, it will unblock any task that might be 
 * 		waiting for memory.
 * @return: OS_R_OK on success and OS_R_NOK if box does not belong to mem_pool 
 */
OS_RESULT rt_mem_free (void *mem_pool, void *box) {
	
	//Check if box is in memory pool
  if(box == NULL)
		return OS_R_NOK;
	else{
		int test;
		P_TCB testBlock = rt_get_first(&blocked_list);
		//Check if there is a blocked task that can use newly free'd memory
		if(testBlock == NULL){ //If no, we can free the memory box
			test = rt_free_box(mem_pool, box);
			//Test if the memory block is in the pool
			if(test == 1){
				return OS_R_OK;
			}
			else
				return OS_R_NOK;
		}
		else{ //If yes we do not need to free memory block and just dispatch blocked task to use the memory block
			testBlock -> ret_val = (U32)box;
			rt_dispatch(testBlock);
		}
  }
	return (OS_R_OK);
}
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
