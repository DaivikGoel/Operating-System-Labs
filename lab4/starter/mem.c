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
	int state; // if the node is free or not 0 means free 1 means occupied
	void* startingAddy;
	struct ll_node* previous; // points to previous node
	struct ll_node* next; // points to next node

};

/* global variables */
//Data Structure
void* listBest;
void* listWorst;

/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	//Check if size is too small
	if((int)size < sizeof(struct ll_node))
		return -1;
	listBest = malloc(size); // allocate the memory space

	if((int)listBest == -1)
		return -1;
	
	struct ll_node* first = listBest;
	first -> previous = NULL;
	first -> next = NULL;
	first -> size = (int)size - sizeof(struct ll_node);
	first -> startingAddy = listBest + sizeof(struct ll_node);
	first -> state = 0;

	return 0;
}

int worst_fit_memory_init(size_t size)
{
	//Check if size is too small
	if((int)size < sizeof(struct ll_node))
		return -1;
	listWorst = malloc(sizeof((int)size));
	if ((int)listWorst == -1)
		return -1;
	
	struct ll_node *first = listWorst;
	first -> size = (int)size - sizeof(struct ll_node); // whatever the remaining size of the memory space is will be the remaining space
	first -> previous = NULL;
	first -> next = NULL;
	first -> state = 0;
	first->startingAddy = listWorst + sizeof(struct ll_node);

	return 0;
}

/* memory allocators */
void *best_fit_alloc(size_t size_requested)
{
	// To be completed by students
	int size = makeDivisibleByFour((int)size_requested);
	//Handle inavlid cases
	if(size <= 0)
		return NULL;

	struct ll_node* best = NULL;
	struct ll_node* move = listBest;
	int diff;

	while (move != NULL)
	{
		//Check if current block is free and big enough for requested allocation
		if ((move -> size) >= size  && move -> state == 0)
		{
			//If block hasnt been allocated or is smaller than last smallest block, then allocate space 
			if(best == NULL || (move -> size < best -> size)){
				best = move;
			}	
		}
		move = move->next;
	} //Find smallest memory block

	//Check if noadequate memory block was found
	if( best == NULL){
		return NULL;
	}
	best -> state = 1;
	diff = (best->size) - size - sizeof(struct ll_node);

	//Check if there is free space leftover
	if (diff < 0)
	{
		best -> size = size;
		return best->startingAddy;
	}
	else if(diff >= 0)//Create node to control free space
	{
		//Enough free space is avaialbe to create free space node
		struct ll_node* freeSpace = best->startingAddy + size;
		freeSpace -> size = diff;
		freeSpace -> state = 0;
		freeSpace -> startingAddy = freeSpace + 1;
		freeSpace -> next == NULL;
		freeSpace -> previous == NULL;

		best -> size = size;
		insert_node(best, freeSpace);
	}
	return best -> startingAddy;
}

void *worst_fit_alloc(size_t size_requested)
{
	// To be completed by students
	int size = makeDivisibleByFour((int)size_requested);
	//Handle inavlid cases
	if (size <= 0)
		return NULL;
	
	struct ll_node *worst = NULL; 
	struct ll_node *move = listWorst;
	int diff;

	while (move != NULL)
	{
		//Check if current block is free and big enough for requested allocation
		if ((move -> size) >= size && move -> state == 0)
		{
			//If block hasnt been allocated or is smaller than last smallest block, then allocate space
			if (worst == NULL || (move -> size > worst -> size))
			{
				worst = move;
			}
		}
		move = move->next;
	} // Find smallest memory block

	//Check if no adequate memory block was found
	if( worst == NULL){
		return NULL;
	}
	worst->state = 1;
	diff = (worst->size) - size - sizeof(struct ll_node);

	//Check if there is free space leftover
	if (diff < 0)
	{
		worst -> size = size;
		return worst -> startingAddy;
	}
	else if (diff >= 0) //Create node to control free space
	{
		//Enough free space is avaialbe to create free space node
		struct ll_node *freeSpace = worst -> startingAddy + size;
		freeSpace -> size = diff;
		freeSpace -> state = 0;
		freeSpace -> startingAddy = freeSpace + 1;
		freeSpace -> next == NULL;
		freeSpace -> previous == NULL;

		worst->size = size;
		insert_node(worst, freeSpace);
	}
	return worst->startingAddy;
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{
	// To be completed by students
	if(ptr == NULL){
		printf("Pointer passed in was NULL \n");
		return;
	}
		
	struct ll_node* traverse = listBest;
	//Find node to de-alloc
	while(traverse != NULL){
		if(traverse -> startingAddy == ptr){
			break;												
		}
		traverse = traverse -> next;
	}
	if(traverse == NULL){
		printf("Did not find ptr in list\n");
		return;
	}
	
	//Check if there is free space to me merged together
	//Check if there is a free node 'next'
	if( traverse -> next != NULL && traverse -> next -> state == 0){
		traverse -> state = 0;
		traverse -> size += traverse -> next -> size + sizeof(struct ll_node);
		removeNode(traverse -> next);					
	}
	//Check if there is a free node 'previous'
	else if(traverse -> previous != NULL && traverse -> previous -> state == 0){
		traverse -> previous -> size += traverse -> size + sizeof(struct ll_node);
		removeNode(traverse);
	}	
	else
		traverse -> state = 0;
	return;
}

void worst_fit_dealloc(void *ptr) 
{
	// To be completed by students
	if(ptr == NULL){
		printf("Pointer passed in was NULL \n");
		return;
	}
		
	struct ll_node* traverse = listWorst;
	//Find node to de-alloc
	while(traverse != NULL){
		if(traverse -> startingAddy == ptr){
			break;												
		}
		traverse = traverse -> next;
	}
	if(traverse == NULL){
		printf("Did not find ptr in list\n");
		return;
	}
	
	//Check if there is free space to be merged together
	//Check if there is a free node 'next'
	if( traverse -> next != NULL && traverse -> next -> state == 0){
		traverse -> state = 0;
		traverse -> size += traverse -> next -> size + sizeof(struct ll_node);
		removeNode(traverse -> next);		
	}
	//Check if there is a free node 'previous'
	else if(traverse -> previous != NULL && traverse -> previous -> state == 0){
		traverse -> previous -> size += traverse -> size + sizeof(struct ll_node);
		removeNode(traverse);
	}	
	else{ //No free nodes nearby to merge
		traverse -> state = 0;
	}
		
	return;
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	// To be completed by students
	int count = 0;
	struct ll_node* traverse = listBest;
	while(traverse != NULL){
		if(traverse -> size < (int)size && traverse -> state == 0)
			count++;
		traverse= traverse -> next;
	}
	return count;
}

int worst_fit_count_extfrag(size_t size)
{
	// To be completed by students
	int count = 0;
	struct ll_node* traverse = listWorst;
	while(traverse != NULL){
		if(traverse -> size < (int)size && traverse -> state == 0)
			count++;
		traverse= traverse -> next;
	}
	return count;
}

//Return size of memory currently allocated in stack
int sizeOfMemAlloc(void* stack)
{
	int i;
	int numMemory = 0;
	struct ll_node* traverse = stack;
	//Traverse through linked lis and count hoe many bytes are allocated
	while(traverse != NULL){
		numMemory += (traverse->size) + sizeof(struct ll_node);
		traverse = traverse->next;
	}
	return numMemory;
}

int makeDivisibleByFour (int input){
	if(input % 4 == 0)
		return input;
	else	
		return input + (4 - input%4);
}

void printCurrentAllocs(int bestOrWorst){
	struct ll_node* traverse;
	if(bestOrWorst == 0)
		traverse = listWorst;
	else if(bestOrWorst == 1)
		traverse = listBest;
	
	while(traverse != NULL){
		printf("Memory Address: %lu, Size: %d, State: %d\n", (long unsigned int)traverse, traverse->size, traverse->state);
		traverse = traverse->next;
	}
}

// inserts node to linked list
void insert_node(struct ll_node* previousnode , struct ll_node* insertnode){
	insertnode -> next = previousnode -> next;
	previousnode -> next = insertnode;
	insertnode -> previous  = previousnode;
}

//Remove a node from the linked list
void removeNode(struct ll_node* pop){
	if(pop->next!=NULL){
		pop->next->previous = pop->previous;
	}
	else if (pop->previous != NULL)
	{
		pop->previous->next = pop->next;
	}
}