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

	mqd_t mq;
    struct mq_attr attr;
    char buffer[maxmsg + 1];

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = maxmsg;
    attr.mq_msgsize = maxmsg;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    CHECK((mqd_t)-1 != mq);

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

	//Create all producer processes
	int id;
	int pid;
	int numProduced = 0;
	buffer = malloc( maxmsg * sizeof(int));

	//Create all producers
	for(pid = 0; pid < num_p; pid++){
		id = fork();
		//If it is the child process it is therefore a producer and should do producer work
		if ( id==0){
			//Critical section
			semWait();
			producerWork(id, num, num_p, numProduced);
			semSignal();
			kill;
		}
	}

	int cid;
	//Create all consumer processes
	for(cid = 0; cid < num_c; cid++){
		id = fork();
		//If it is the child process it is therefore a consumer and should do produconsumercer work
		if ( id==0){
			//Critical section
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

//Push integers onto buffer based on formula integer = id%nump
void producerWork (int p_id, int N, int P, int &numCreated){
	int i = 0;
	while(i < N/P){
		if(mq_curmsgs >= maxmsg)
			wait();
		if(i%P ==id){
			// buffer.push(i);
			mq_send(mq, buffer, size_t, unsigned)
			mq_curmsgs++;
			i++;
		}
	}	
}
//Take integers off of buffer and calculate square root
void consumerWork (int c_id, int N, int &numCreated)
	int work;
	double root;
	while(buffer.size > 0){
		if(numCreated == 0)
			//Exit
		work = buffer.pop;
		root = sqrt(work);
		//Check if root is an integer
		if(floor(root) == root){
			printf("%d %d %d", c_id, work, root)
		}
	}
	printf(id, input, output);
}
