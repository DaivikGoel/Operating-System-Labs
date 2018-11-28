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
    printf("Worst Fit Test 1 Testing Alloc and Dealloc\n");
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
    printf("Worst Fit Test 2 Testing Coalescing\n");
    worst_fit_memory_init(1000);

    void *a = worst_fit_alloc(100);
    void *b = worst_fit_alloc(100);
    void *c = worst_fit_alloc(100);
    void *d = worst_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(0);
    printf("---\n");

    worst_fit_dealloc(a);
    worst_fit_dealloc(b);
    worst_fit_dealloc(c);
    worst_fit_dealloc(d);

    printf("Deallocating all blocks to see if deallocations is working \n");
    printCurrentAllocs(0);
    printf("---\n");

    return;
}
void worst_fit3()
{
    printf("Worst Fit Test 3 Testing difference between worst and best\n");
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
void worst_fit4()
{
    printf("Worst Fit Test 4 Testing Fragmentation code\n");
    worst_fit_memory_init(1000);

    void *a = worst_fit_alloc(100);
    void *b = worst_fit_alloc(100);
    void *c = worst_fit_alloc(110);
    void *d = worst_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(0);
    printf("---\n");

    void *h = worst_fit_alloc(4);
    void *i = worst_fit_alloc(4);
    void *j = worst_fit_alloc(4);
    void *k = worst_fit_alloc(4);
    void *l = worst_fit_alloc(4);
    worst_fit_dealloc(h);
    worst_fit_dealloc(k);
    printf("Should only have 2 data fragments below 8\n");
    printCurrentAllocs(0);
    printf("---\n");

    printf("Worst fit fragments under 8 bytes: %d \n", worst_fit_count_extfrag(8));
    printf("---\n");

    return;
}

void best_fit1()
{
    printf("Best Fit Test 1 Testing Alloc and Dealloc\n");
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

void best_fit2() // Testing Coalescing
{
    printf("Best Fit Test 2 Testing Coalescing \n");
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
    printf("Best Fit Test 3 Testing difference between worst and best \n");
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

void best_fit4()
{
    printf("Worst Fit Test 4 Testing Fragmentation code\n");
    best_fit_memory_init(1000);

    void *a = best_fit_alloc(100);
    void *b = best_fit_alloc(100);
    void *c = best_fit_alloc(110);
    void *d = best_fit_alloc(100);

    printf("Full\n");
    printCurrentAllocs(1);
    printf("---\n");

    void *h = best_fit_alloc(4);
    void *i = best_fit_alloc(4);
    void *j = best_fit_alloc(4);
    void *k = best_fit_alloc(4);
    void *l = best_fit_alloc(4);
    best_fit_dealloc(h);
    best_fit_dealloc(k);
    printf("Should only have 2 data fragments below 8\n");
    printCurrentAllocs(1);
    printf("---\n");

    printf("Worst fit fragments under 8 bytes: %d \n", best_fit_count_extfrag(8));
    printf("---\n");

    return;
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
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("made it to iteration: %d\n", i);
        worst_fit_alloc(20);
    }

    void *kB_worst = worst_fit_alloc(4);

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

     for (i = 0; i < 10; i++)
     {
     	printf("made it to iteration: %d\n", i);
     	best_fit_alloc(20);
    }

   
    void *kB_best = best_fit_alloc(4);

    printf("worst kB: %lu best kB: %lu\n", kB_worst, kB_best);
}

int main(int argc, char *argv[])
{
    // worst_fit1();
    // worst_fit2();
    // worst_fit3();
    // worst_fit4();
    // best_fit1();
    // best_fit2();
    // best_fit3();
    // best_fit4();
 
    best_vs_worst_large_data();

    return 0;
}