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
#include <pthread.h>
#include <semaphore.h> // added this

double g_time[2];

pthread_mutex_t mutex;

sem_t empty_list;
sem_t filled_list;

int *buffer;
int index_p;
int index_c;
int numread = 0;

struct arg_struct
{
	int index;
	int maxmsg;
	int num;
	int num_p;
	int num_c;
};

//Producer and consumer functions
void *producer(void *arguments);
void *consumer(void *arguments);

int main(int argc, char *argv[])
{
	
	struct timeval tv;
	int num;
	int maxmsg;
	int num_p;
	int num_c;

	if (argc != 5)
	{
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	//Extract command line arguments
	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */

	sem_init(&empty_list, 0, maxmsg);
	sem_init(&filled_list, 0, 0);

	//Allocate memory for buffer
	buffer = malloc(maxmsg * sizeof(int));
	pthread_mutex_init(&mutex, NULL);
	pthread_t producers[num_p];
	pthread_t consumers[num_c];
	index_p = 0;
	index_c = 0;

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec / 1000000.;


	//Create num_p producer threads
	for (int i = 0; i < num_p; i++)
	{
		//Create structure of data to send to producer thread
		struct arg_struct *pargs;
		pargs = malloc(sizeof(struct arg_struct));
		(*pargs).index = i;
		(*pargs).maxmsg = maxmsg;
		(*pargs).num = num;
		(*pargs).num_p = num_p;

		pthread_create(&producers[i], NULL, producer, (void *)pargs);
	}

	//Create num_p consumer threads
	for (int j = 0; j < num_c; j++)
	{
		//Create structure of data to send to producer thread
		struct arg_struct *cargs;
		cargs = malloc(sizeof(struct arg_struct));
		(*cargs).index = j;
		(*cargs).maxmsg = maxmsg;
		(*cargs).num = num;
		(*cargs).num_c = num_c;

		pthread_create(&consumers[j], NULL, consumer, (void *)cargs);
	}
	//Wait for all producer threads to finish by joining them
	for (int h = 0; h < num_p; h++)
	{
		pthread_join(producers[h], NULL);
	}
	//Wait for all consumer threads to finish by joining them
	for (int e = 0; e < num_c; e++)
	{
		pthread_join(consumers[e], NULL);
	}

	//Free memory allocated for buffer
	free( buffer);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty_list);
	sem_destroy(&filled_list);
	

	gettimeofday(&tv, NULL);
	g_time[1] = (tv.tv_sec) + tv.tv_usec / 1000000.;
	
	printf("System execution time: %.6lf seconds\n",
		   g_time[1] - g_time[0]);
	exit(0);
}

void *producer(void *arguments)
{
	struct arg_struct *args = (struct arg_struct *)(arguments);
	int i = (*args).index;
	while (1)
	{
		if (i > (*args).num - 1 ){
			break;
		}
		//Protect critical section (Writing to buffer) with semaphore
		sem_wait(&empty_list);
		pthread_mutex_lock(&mutex);

		//Write to buffer
		buffer[index_p] = i;
		index_p = (index_p + 1) % (*args).maxmsg;
		pthread_mutex_unlock(&mutex);
		sem_post(&filled_list);
		i = i + (*args).num_p;
	}
	free(args);
	pthread_exit(NULL);
}

void *consumer(void *arguments)
{

	struct arg_struct *args = (struct arg_struct *)arguments;

	int work;
	double root;

	while (numread <= (*args).num)
	{
		//Protect critical section (Reading from buffer) with semaphore
		sem_wait(&filled_list);
		pthread_mutex_lock(&mutex);

		//Read from buffer
		work = buffer[index_c];
		index_c = (index_c + 1) % (*args).maxmsg;
		numread++;
		if (numread == (*args).num)
		{
			sem_post(&filled_list);
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&empty_list);
		//Check if root is an integer
		root = sqrt(work);
		if (floor(root) == root)
		{
			printf("%d %d %d\n", (*args).index, work, (int)root);
		}
	}

	pthread_mutex_unlock(&mutex);
	sem_post(&filled_list);
	free(args);
	pthread_exit(NULL);
}