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
	//int state; // if the linked list is free or not 0 means free 1 means occupied
	void *startingAddy;
	struct ll_node* previous; // points to previous node
	struct ll_node* next; // points to next node

};

/* global variables */
//Data Structure
struct ll_node* stackBest;
struct ll_node* stackworst;
int totalMemoryBest;
int totalMemoryWorst;
/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	totalMemoryBest = (int)size;
	stackBest = malloc(sizeof((int)size)); // allocate the memory space

	if(stackBest == -1)
		return -1;
	
	struct ll_node* first = stackBest;
	//first -> size = size - sizeof(struct ll_node); // whatever the remaining size of the memory space is will be the remaining space
	//first -> state = 0;
	first -> previous = NULL;
	first -> next = NULL;
	first -> startingAddy = sizeOfMemAlloc(stackBest) + sizeof(stackBest);

	return 0;
}

int worst_fit_memory_init(size_t size)
{
	totalMemoryWorst = (int)size;
	stackworst = malloc(sizeof((int)size));

	struct ll_node *first = stackworst;
	//first -> size = size - sizeof(struct ll_node); // whatever the remaining size of the memory space is will be the remaining space
	//first -> state = 0;
	first -> previous = NULL;
	first -> next = NULL;
	first -> startingAddy = sizeOfMemAlloc(stackworst) + sizeof(stackworst);
	return 0;

}

/* memory allocators */
void *best_fit_alloc(size_t size)
{
	// To be completed by students

	//Handle inavlid cases
	if((int)size <= 0)
		return NULL;
	else if((int)size > totalMemoryBest + sizeof(stackBest))
		return NULL;
	else if((int)size > (totalMemoryBest - sizeOfMemAlloc(stackBest)))
		return NULL;

	// struct ll_node* best = NULL;
	// struct ll_node* move = best;
	// int diff = 0;

	// while( move != NULL){
	// if(move -> size >= size && move -> state = 0 && ( best == NULL || (move -> size < best -> size ))){

	// 	best = move;
	// }
	// else 
	// 	move = move -> next;
	// } // Find biggest memory block

	// best -> state = 1;
	
	// diff = (best -> size ) - size;
	
	// if(diff == 0){

	// return best -> mem;

	// }
	// else {
	// diff = diff - sizeof(struct ll_node);

	// if(diff < 0 ){
	// 	best -> size = size + (best -> size);
	// }

	// return NULL;
	// }
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

//Return size of memory currently allocated in stack
int sizeOfMemAlloc(struct ll_node* stack)
{
	int i;
	int numMemory = 0;
	struct ll_node* traverse = stack;
	//Traverse through linked lis and count hoe many bytes are allocated
	while(traverse != NULL){
		numMemory += traverse->size;
		traverse = traverse->next;
	}
	return numMemory;
}
