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

#include <signal.h>

double g_time[2];

void producerWork(int p_id, int P , int N);
void consumerWork(int c_id);

mqd_t mq;
struct mq_attr attr;
int killSignal = -1;

//Track how many nums are produced
int numCreated = 0;

int main(int argc, char *argv[])
{
	int num;
	int maxmsg;
	int num_p;
	int num_c;
	int i;
	struct timeval tv;

	mode_t mode = S_IRUSR | S_IWUSR;

	char *qname = "/mailbox_rmschmie";

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

	//Initialize and open message queue for inter-process communication

	/* initialize the queue attributes */
	 attr.mq_flags = 0;
	 attr.mq_maxmsg = maxmsg;
	 attr.mq_msgsize = sizeof(int);
	 attr.mq_curmsgs = 0;

	/* create the message queue */
	mq = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);
	
	if(mq == -1){
		printf("Opening message queue failed.\n");
		return -1;
	}

	//Create array of ids for producers and consumers
	pid_t* producer_ids = malloc(sizeof(pid_t)*num_p);
	pid_t* consumer_ids = malloc(sizeof(pid_t)*num_c);

	//Create all producers
	for(i = 0; i < num_p; i++){
		producer_ids[i] = fork();
		//If it is the child process it is therefore a producer and should do producer work
		if ( producer_ids[i] == 0){
			producerWork(i, num_p, num);
			exit(0);
		}
	}
	if(getpid() != 0){
	//Create all consumer processes
		for(i = 0; i < num_c; i++){
			consumer_ids[i] = fork();
			//If it is the child process it is therefore a consumer and should do produconsumercer work
			if ( consumer_ids[i] == 0){
				consumerWork(i);
				break;
			}
		}
	}

	int* return_value;
	//Wait for producer processes to be finished so we can send kill signal to end of message queue
	for(i = 0; i < num_p; i++){
		waitpid(producer_ids[i], return_value, 0);
	}

	//Since all producers are done, send kill signal to message queue for consumers
	int sendKill;
	for(i = 0; i < num_c; i++){
		sendKill = mq_send(mq, (char*)&killSignal, sizeof(int), 0);
		if(sendKill == -1){
			perror("Error sending kill signal to message queue.\n");
			return -1;
		}
	} 

	//Wait for consumer proccesses to be finished so we can close the queue and end program
	for(i = 0; i < num_c; i++){
		waitpid(consumer_ids[i], return_value, 0);
	}
	
	// Close message queue as it is no longer needed
	int close = mq_close(mq);

	if(close == -1){
		perror("Error closing message queue.\n");
		return -1;
	}

	//Free memory allocated for producer/consumer ids
	free(producer_ids);
	free(consumer_ids);

    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

//Push integers onto buffer based on formula integer = id%nump
void producerWork (int p_id, int P, int N){
	int i;
	int send;
	
	for(i = 0; i < N; i++){
		//Chceck if number meets reuqirements to be put on message queue
		if(i%P==p_id){
			//Send to message queue
			send = mq_send(mq, (char*)&i, sizeof(int), 0);
			if(send == -1){
				perror("Error in sending to message queue.\n");
				return -1;
			}	
		}
	}
	
}
// Take integers off of buffer and calculate square root, print if root is an integer
void consumerWork (int c_id){
	double root;
	int work;
	ssize_t receive;
	while(1){
		//Read from message queue
		receive = mq_receive(mq, (char*)&work, sizeof(int), 0);
		if(receive == -1){
			perror("Error in receiving message from message queue.\n");
			return -1;
		}
			
		//Check if kill signal was sent by producer therefore all numbers have been sent
		if(work == killSignal){
			exit(0);
		}

		root = sqrt(work);
		//Check if root is an integer
		if(floor(root) == root){
			printf("%d %d %d\n", c_id, work, (int)root);
		}
	}
}
