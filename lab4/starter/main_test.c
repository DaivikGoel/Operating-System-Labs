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

void large_data()
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

    void **memory_bf = malloc(sizeof(void *) * 20);
    void **memory_wf = malloc(sizeof(void *) * 20);

    for (int i = 0; i < 20; i++)
    {
        memory_bf[i] = best_fit_alloc(4);
        memory_wf[i] = worst_fit_alloc(4);
        
    }

    for(int i=0; i< 20; i +=3){

        best_fit_dealloc(memory_bf[i]);
        best_fit_dealloc(memory_bf[i + 1]);
        worst_fit_dealloc(memory_wf[i]);
        worst_fit_dealloc(memory_wf[i + 1]);
    }
    printf("-------------------\n");
    printf("Worst Fit after Multiple Allocs\n");
    printCurrentAllocs(0);
    printf("-------------------\n");
    printf("Best Fit after Multiple Allocs\n");
    printCurrentAllocs(1);
    printf("-------------------\n");
    printf("\nFragments below 4 Worst Fit %i\n", worst_fit_count_extfrag(4));
    printf("\nFragments below 8 Worst Fit %i\n", worst_fit_count_extfrag(8));
    printf("\nFragments below 32 Worst Fit %i\n", worst_fit_count_extfrag(32));
    printf("\nFragments below 64 Worst Fit %i\n", worst_fit_count_extfrag(64));
    printf("\nFragments below 128 Worst Fit %i\n", worst_fit_count_extfrag(128));
    printf("\nFragments below 256 Worst Fit %i\n", worst_fit_count_extfrag(256));
    printf("\nFragments below 512 Worst Fit %i\n", worst_fit_count_extfrag(512));
    printf("\nFragments below 1024 Worst Fit %i\n", worst_fit_count_extfrag(1024));
    printf("\nFragments below 2048 Worst Fit %i\n", worst_fit_count_extfrag(2048));
    printf("-------------------\n");
    printf("\nFragments below 4 Best Fit %i\n", best_fit_count_extfrag(4));
    printf("\nFragments below 8 Best Fit %i\n", best_fit_count_extfrag(8));
    printf("\nFragments below 32 Best Fit %i\n", best_fit_count_extfrag(32));
    printf("\nFragments below 64 Best Fit %i\n", best_fit_count_extfrag(64));
    printf("\nFragments below 128 Best Fit %i\n", best_fit_count_extfrag(128));
    printf("\nFragments below 256 Best Fit %i\n", best_fit_count_extfrag(256));
    printf("\nFragments below 512 Best Fit %i\n", best_fit_count_extfrag(512));
    printf("\nFragments below 1024 Best Fit %i\n", best_fit_count_extfrag(1024));
    printf("\nFragments below 2048 Best Fit %i\n", best_fit_count_extfrag(2048));
    printf("-------------------\n");
}
// constantly allocates and deallocates memory in small chunks to count fragmentation

void compare_fragments_4()
{

    printf("Comparing fragments of worst and best\n");

    
    worst_fit_memory_init(12000);
    best_fit_memory_init(12000);

    void **memory_bf = malloc(sizeof(void *) * 50);
    void **memory_wf = malloc(sizeof(void *) * 50);

    for (int k = 0; k < 50; k++)
    {
        memory_bf[k] = best_fit_alloc(104);
        memory_wf[k] = worst_fit_alloc(104);
    }

    for (int i = 0; i < 25; i += 2)
    {
        best_fit_dealloc(memory_bf[i]);
        
    }
    for (int i = 0; i < 50; i += 2)
    {
        worst_fit_dealloc(memory_wf[i]);
    }
    for (int k = 0; k < 50; k++)
    {
        memory_bf[k] = best_fit_alloc(24);
        memory_wf[k] = worst_fit_alloc(24);
    }

    printCurrentAllocs(0);
    printCurrentAllocs(1);

    printf("Fragmentation below 8 bytes - Best Fit %i\n", best_fit_count_extfrag(8));
    printf("Fragmentation below 8 bytes - Worst Fit %i\n", worst_fit_count_extfrag(8));
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
    large_data();
   // compare_fragments_4();
    //compare_test_performance_small();
    return 0;
}
