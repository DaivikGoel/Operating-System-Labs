/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: Ryan Michael Schmied and Daivik Goel
 * @date: 2018-11-22
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"

/* defines */
struct ll_node {
	int size; // size of memory
	int state; // if the linked list is free or not
	struct ll_node* previous; // points to previous node
	struct ll_node* next; // points to next node

}
/* global variables */
ll_node* best;
ll_node* worst
/* Functions */


/* memory initializer */
int best_fit_memory_init(size_t size)
{
	best = malloc(size); // allocate the memory space
	
	struct node* first = best;



	// To be completed by students
	// You call malloc once here to obtain the memory to be managed.
	
}

int worst_fit_memory_init(size_t size)
{
	worst = malloc(size);
	// To be completed by students
	// You call malloc once here to obtain the memory to be managed.
	return 0;

}

/* memory allocators */
void *best_fit_alloc(size_t size)
{
	// To be completed by students
	return NULL;
}


void *worst_fit_alloc(size_t size)
{
	// To be completed by students
	return NULL;
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

void worst_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}

int worst_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}
