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

	//Initialize and open message queue for inter-preocess communication
	mqd_t mq;
	struct mq_attr attr;
	char buffer[maxmsg + 1];

	/* initialize the queue attributes */
	 attr.mq_flags = 0;
	 attr.mq_maxmsg = maxmsg;
	 attr.mq_msgsize = sizeof(int);
	 attr.mq_curmsgs = 0;

	/* create the message queue */
	mq = mq_open(buffer, O_RDWR);

	//Create all producer processes
	int id; //Id for forks
	int pid; // Prroducer ID

	//Track how many nums are produced
	int numProduced = 0;

	//Create all producers
	for(pid = 0; pid < num_p; pid++){
		id = fork();
		//If it is the child process it is therefore a producer and should do producer work
		if ( id==0){
			producerWork(p_id, num_p, numProduced, num);
		}
	}

	int cid; //Consumer ID
	//Create all consumer processes
	for(cid = 0; cid < num_c; cid++){
		id = fork();
		//If it is the child process it is therefore a consumer and should do produconsumercer work
		if ( id==0){
			consumerWork(i);
		}
	}
	
	//Close message queue as it is no longer needed
	int close = mq_close(mq);
	if(close == -1){
		printf("Error closing message queue.")
		return -1;
	}

    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

//Push integers onto buffer based on formula integer = id%nump
void producerWork (int p_id, int P , int &numCreated, int N){
	int i = 0;
	int product;
	int send;
	while(1){
		if(i%P==p_id){
			product = i;
			send = mq_send(mq, (char*)product, sizeof(char*), 1);
			if(send == -1){
				printf("Error in sending to message queue.")
				return -1;
			}	
			i++;
			numCreated++;
		}

		//Check if we've produced all the required values, if so, send kill signal to consumers
		if(numCreated == N){
			mq_send(mq, (char*)(-1), sizeof(int), 1);
			kill;
		}

	}	
}
//Take integers off of buffer and calculate square root
void consumerWork (int c_id, int N, int &numCreated){
	char *buffer;
	double root;
	ssize_t receive;
	while(1){
		receive = mq_receive(mq, buffer, sizeof(char*), 1);
		if(receive == -1){
			printf("Error in receiving message from message queue.");
			return -1;
		}
		//Cast buffer to value of message (int)
		buffer = (int)buffer;

		//Check if kill signal was sentt by producer therefore all numbers have been sent
		if(buffer == -1){
			kill;
		}

		root = sqrt(buffer);
		//Check if root is an integer
		if(floor(root) == root){
			printf("%d %d %d", c_id, buffer, root)
		}
	}
}
