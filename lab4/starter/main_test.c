/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"
// TODO: void printCurrentAllocs(){}

// tests completely filling the mem space and deallocates two blocks and then allocates one into the larger free block
void worst_fit1()
{
	printf("Worst Fit Test 1\n");
	worst_fit_memory_init(600);

	void *a = worst_fit_alloc(105);
	void *b = worst_fit_alloc(95);
	void *c = worst_fit_alloc(110);
	void *d = worst_fit_alloc(60);

	printf("Full\n");
	printCurrentAllocs(0);
	printf("---\n");

	worst_fit_dealloc(a);
	worst_fit_dealloc(c);

	printf("Freed 1st and 3rd blocks so new alloc should go to 3rd block \n");
	printCurrentAllocs(0);
	printf("---\n");

	worst_fit_alloc(70);
	printf("New alloc should go to 3rd block \n");
	printCurrentAllocs(0);
	printf("---\n");

	return;
}

void best_fit1()
{
	printf("Best Fit Test 1 \n");
	best_fit_memory_init(600);

	void *a = best_fit_alloc(105);
	void *b = best_fit_alloc(95);
	void *c = best_fit_alloc(110);
	void *d = best_fit_alloc(60);

	printf("Full\n");
	printCurrentAllocs(1);
	printf("---\n");

	best_fit_dealloc(a);
	best_fit_dealloc(c);

	printf("Freed 1st and 3rd blocks so new alloc should go to 1st block \n");
	printCurrentAllocs(1);
	printf("---\n");

	best_fit_alloc(70);
	printf("New alloc should go to 1st block \n");
	printCurrentAllocs(1);
	printf("---\n");

	return;
}


void worst_vs_best_fragments()
{ // allocates a lot of small blocks deallocates some and allocates small spaces, makes fragments in best fit
	printf("Test Worst Fit Vs. Best Fit Fragments: Best Fit Case \n");
	int result = best_fit_memory_init(1236);
	if (result == -1)
	{
		return;
	}

	void *a = best_fit_alloc(52);
	best_fit_alloc(4);
	void *b = best_fit_alloc(100);
	best_fit_alloc(4);

	void *c = best_fit_alloc(52);
	best_fit_alloc(4);
	void *d = best_fit_alloc(100);
	best_fit_alloc(4);

	void *e = best_fit_alloc(52);
	best_fit_alloc(4);
	void *f = best_fit_alloc(100);
	best_fit_alloc(4);

	void *g = best_fit_alloc(52);
	best_fit_alloc(4);
	void *h = best_fit_alloc(100);

	printf("After allocating \n");
	printCurrentAllocs(1);
	printf("---\n");

	best_fit_dealloc(a);
	best_fit_dealloc(b);
	best_fit_dealloc(c);
	best_fit_dealloc(d);
	best_fit_dealloc(e);
	best_fit_dealloc(f);
	best_fit_dealloc(g);
	best_fit_dealloc(h);

	printf("After deallocating \n");
	printCurrentAllocs(1);
	printf("---\n");

	best_fit_alloc(8);
	best_fit_alloc(8);
	best_fit_alloc(8);
	best_fit_alloc(8);

	printf("After allocating 8\n");
	printCurrentAllocs(1);
	printf("---\n");

	printf("Best fit fragmentation count below 8 bytes: %d \n", best_fit_count_extfrag(8));
	printf("---\n");

	printf("Test Worst Fit Vs. Best Fit Fragments: Worst Fit Case \n");
	int result2 = worst_fit_memory_init(1236);
	if (result2 == -1)
	{
		return;
	}

	void *a2 = worst_fit_alloc(52);
	worst_fit_alloc(4);
	void *b2 = worst_fit_alloc(100);
	worst_fit_alloc(4);

	void *c2 = worst_fit_alloc(52);
	worst_fit_alloc(4);
	void *d2 = worst_fit_alloc(100);
	worst_fit_alloc(4);

	void *e2 = worst_fit_alloc(52);
	worst_fit_alloc(4);
	void *f2 = worst_fit_alloc(100);
	worst_fit_alloc(4);

	void *g2 = worst_fit_alloc(52);
	worst_fit_alloc(4);
	void *h2 = worst_fit_alloc(100);

	printf("After allocating \n");
	printCurrentAllocs(0);
	printf("---\n");

	worst_fit_dealloc(a2);
	worst_fit_dealloc(b2);
	worst_fit_dealloc(c2);
	worst_fit_dealloc(d2);
	worst_fit_dealloc(e2);
	worst_fit_dealloc(f2);
	worst_fit_dealloc(g2);
	worst_fit_dealloc(h2);

	printf("After deallocating \n");
	printCurrentAllocs(0);
	printf("---\n");

	worst_fit_alloc(8);
	worst_fit_alloc(8);
	worst_fit_alloc(8);
	worst_fit_alloc(8);

	printf("After allocating 8 \n");
	printCurrentAllocs(0);
	printf("---\n");

	printf("worst fit fragmentation count below 8 bytes: %d \n", worst_fit_count_extfrag(8));
	printf("---\n");
}

void best_vs_worst_large_data()
{
	//create worst fit memory space with divider in middle
	worst_fit_memory_init(2124);
	void *a = worst_fit_alloc(1000);
	worst_fit_alloc(4);
	void *b = worst_fit_alloc(1000);
	printCurrentAllocs(0);
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	printCurrentAllocs(0);
	//create best fit memory space with divider in middle
	best_fit_memory_init(2124);
	void *c = best_fit_alloc(1000);
	best_fit_alloc(4);
	void *d = best_fit_alloc(1000);
	printCurrentAllocs(0);
	best_fit_dealloc(c);
	best_fit_dealloc(d);
	printCurrentAllocs(0);

	int i;
	for (i = 0; i < 16; i++)
	{
		worst_fit_alloc(20);
		best_fit_alloc(20);
	}

	void *kB_worst = worst_fit_alloc(1000);
	void *kB_best = best_fit_alloc(1000);

	printf("worst kB: %lu best kB: %lu\n", (long unsigned int)kB_worst, (long unsigned int)kB_best);
}

int main(int argc, char *argv[])
{
	worst_fit1();
	best_fit1();
	// worst_vs_best_fragments();
	best_vs_worst_large_data();

	return 0;
}