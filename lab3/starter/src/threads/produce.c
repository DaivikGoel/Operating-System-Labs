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
sem_t filled_list;
int *buffer;
int index_p;
int read = 0;

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
	pthread_mutex_init(&mutex, NULL);
	int total = num_p + num_c;
	pthread_t producers [num_p];
	pthread_t consumers[num_c];
	index_p = 0;
	index_c = 0;

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;


	for (int i = 0; i < num_p; i++)
	{
		struct arg_struct *pargs;
		pargs.index = i;
		pargs.maxmsg = maxmsg;
		pargs.num = num;
		pargs.num_p = num_p;


		pthread_create(&producers[i], NULL, &producer, (void*)&pargs );
	}

	for (int j = 0; j < num_c; j++)
	{
		struct arg_struct *cargs;
		cargs.index = j;
		cargs.maxmsg = maxmsg;
		cargs.num = num;
		cargs.num_c = num_c;

		pthread_create(&consumers[j], NULL, &consumer, (void*)&cargs;
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
		sem_post(&filled_list);								   
	}
	free(args);
	pthread_exit(NULL);
}

void *consumer(void *arguments){

	struct arg_struct *args = arguments;

	int work;
	double root;
	while(read < args.num){

		sem_wait(&filled_list);
		pthread_mutex_lock(&mutex);

		work = buffer[index_c];
		index_c = (index_c + 1 ) % args.maxmsg;
		read++;
		if(read == args.num){
			sem+_(&filled_list)
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&empty_list);
		//Check if root is an integer
		root = sqrt(work);
		if (floor(root) == root)
		{
			printf("%d %d %d", c_id, work, root)
		}
	}
	pthread_mutex_unlock(&mutex);
	sem_post(&filled_list)

	pthread_exit(NULL);
}