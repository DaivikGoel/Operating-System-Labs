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

double g_time[2];


int main(int argc, char *argv[])
{
	int num;
	int maxmsg;
	int num_p;
	int num_c;
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


	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

	//Create all producer processes
	int i;
	pid_t id;
	int *buffer;
	buffer = malloc( maxmsg * sizeof(int));

	for(i = 0; i < num_p; i++){
		id = fork();
		//If it is the child process it is therefore a producer and should do producer work
		if ( id==0){
		
			producerWork(i);
		}

	}

	//Create all consumer processews
	for(j = 0; j < num_c; j++){
		id = fork();
		//If it is the child process it is therefore a consumer and should do produconsumercer work
		if ( id==0){
			consumerWork(i);
		}

	}
	
	//Wait for processes to finish

    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

//Push integers onto buffer based on formaula integer = id%nump
void producerWork (int id){
	int i = 0;
	while(1){

	buffer.push((i * num_p) + id) % num_p);

	}
	kill;
}
//Take integers off of buffer and calculate square root
void consumerWork (pid_t id){

}
