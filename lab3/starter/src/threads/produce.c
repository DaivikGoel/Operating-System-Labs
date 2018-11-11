// Use this to see if a number has an integer square root
#define EPS 1.E-7


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#include <semaphore.h> // added thism 


double g_time[2];

pthread_mutex_t mutex;

sem_t empty_list;
sem_t full_list;
int *buffer;
int index_p;


struct arg_struct
{
	int index;
	int maxmsg;
	int num;
	int num_p;
};


int main(int argc, char *argv[])
{
	
	int i;
	struct timeval tv;

	
	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	
	
	buffer = malloc(maxmsg * sizeof(int));
	int total = num_p + num_c;
	pthread_t producers [num_p];
	pthread_t consumers[num_c];
	index_p = 0;

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;


	for (int i = 0; i < num_p; i++)
	{
		struct arg_struct *args;
		args.index = i;
		args.maxmsg = maxmsg;
		args.num = num;
		args.num_p = num_p;


		pthread_create(&producers[i], NULL, &producer, (void*)&args );
	}

	for (int j = 0; j < num_c; j++)
	{

		pthread_create(&consumers[j], NULL, consumer, buffer;
	}

	gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);


}

void *producer(void* arguments )
{
	struct arg_struct *args = arguments;

	int i = 0;
	while (i < args.num / args.num_p)
	{

		sem_wait(&emptylist);								   
		pthread_mutex_lock(&mutex);						   
		buffer[index_p] = i;						   
		index_p = (index_p + 1) % args.maxmsg; 
		pthread_mutex_unlock(&mutex);					   
		sem_post(&full_list);								   
	}
	pthread_exit(NULL);
}
