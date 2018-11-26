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

void worst_fit2()
{
    printf("Worst Fit Test 2 \n");
    worst_fit_memory_init(1000);

    void *a = worst_fit_alloc(100);
    void *b = worst_fit_alloc(100);
    void *c = worst_fit_alloc(100);
    //void *d = worst_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(0);
    printf("---\n");

    worst_fit_dealloc(a);
    //worst_fit_dealloc(b);
    worst_fit_dealloc(c);
    worst_fit_dealloc(b);

    printf("Deallocating all blocks to see if deallocations is working \n");
    printCurrentAllocs(0);
    printf("---\n");

    return;
}
void worst_fit3()
{
    printf("Worst Fit Test 3 \n");
    worst_fit_memory_init(1000);

    void *a = worst_fit_alloc(100);
    void *b = worst_fit_alloc(100);
    void *c = worst_fit_alloc(110);
    void *d = worst_fit_alloc(100);
    void *e = worst_fit_alloc(100);
    void *f = worst_fit_alloc(100);
    void *g = worst_fit_alloc(100);


    printf("Full\n");
    printCurrentAllocs(0);
    printf("---\n");

    worst_fit_dealloc(a);
    worst_fit_dealloc(c);

    printf("Deallocating 1st and 3rd blocks\n");
    printCurrentAllocs(0);
    printf("---\n");

    void *h = worst_fit_alloc(4);
     printf("Allocating 4 bytes. Should be allocated to  3 \n");
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

void best_fit2()
{
    printf("Best Fit Test 2 \n");
    best_fit_memory_init(1000);

    void *a = best_fit_alloc(100);
    void *b = best_fit_alloc(100);
    void *c = best_fit_alloc(100);
    void *d = best_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(1);
    printf("---\n");

    best_fit_dealloc(a);
    best_fit_dealloc(b);
    best_fit_dealloc(c);
    best_fit_dealloc(d);

    printf("Deallocating all blocks to see if deallocations is working \n");
    printCurrentAllocs(1);
    printf("---\n");

    return;
}

void best_fit3()
{
    printf("Best Fit Test 3 \n");
    best_fit_memory_init(1000);

    void *a = best_fit_alloc(100);
    void *b = best_fit_alloc(100);
    void *c = best_fit_alloc(110);
    void *d = best_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(1);
    printf("---\n");

    best_fit_dealloc(a);
    best_fit_dealloc(c);

    printf("Deallocating 1 and 3 if deallocations is working \n");
    printCurrentAllocs(1);
    printf("---\n");

    void *e = best_fit_alloc(4);
    printf("Allocating 4 bytes. Should be allocated to  1 \n");
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
    printf("Worst fit: \n");
    worst_fit_memory_init(2124);
    void *a = worst_fit_alloc(1000);
    void *f = worst_fit_alloc(4);
    void *b = worst_fit_alloc(1000);
    printf("Worst fit before de - alloc: \n");
    printCurrentAllocs(0);

    worst_fit_dealloc(a);
    worst_fit_dealloc(b);
    printf("Worst fit after de - alloc: \n");
    printCurrentAllocs(0);

    //create best fit memory space with divider in middle
    printf("Best fit: \n");
    best_fit_memory_init(2124);
    void *c = best_fit_alloc(1000);
    void *e = best_fit_alloc(4);
    void *d = best_fit_alloc(1000);
    printf("Best fit before de - alloc: \n");
    printCurrentAllocs(1);

    best_fit_dealloc(c);
    best_fit_dealloc(d);

    printf("Best fit after de - alloc: \n");
    printCurrentAllocs(1);

     int i;
     for (i = 0; i < 10; i++)
     {
     	printf("made it to iteration: %d\n", i);
     	worst_fit_alloc(20);
     	best_fit_alloc(20);
    }

    void *kB_worst = worst_fit_alloc(4);
    void *kB_best = best_fit_alloc(4);

    printf("Worst fit after realloc: \n");
    printCurrentAllocs(0);

    printf("Best fit before realloc: \n");
    printCurrentAllocs(1);

    printf("worst kB: %lu best kB: %lu\n", kB_worst, kB_best);
}

int main(int argc, char *argv[])
{
    // worst_fit1();
    //worst_fit2();
    worst_fit3();
    // best_fit1();
    //best_fit2();
    best_fit3();
    // worst_vs_best_fragments();
    //best_vs_worst_large_data();

    return 0;
}