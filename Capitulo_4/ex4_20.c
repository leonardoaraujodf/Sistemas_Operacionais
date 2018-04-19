
//compile usando: $ gcc ex4_20.c -o ex4_20 -lpthread 
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //rand() e srand() estao aqui
#include <time.h> //para a funcao time()

#define MIN_PID 300
#define MAX_PID 5000

#define NUMBER_THREADS 200

int bitmap[(MAX_PID - MIN_PID)];
int bitmap_status = 0;


int allocate_map(void);
/*Creates and initilizes a data structure						
for representing pids; 
returns - 1 if unsuccessful
retuns 1 if successful
*/

int allocate_pid(void);
/*
Allocates and returns a pid; returns - 1 if
unable to allocate a pid (all pids are in use)
*/

void release_pid(int pid);
/*
Releases a pid
*/

void *test_pid (void *param);


int main(){

	pthread_t tid[NUMBER_THREADS];
	pthread_attr_t attr[NUMBER_THREADS];
	int i;

	if(allocate_map() < 0)
	{
		printf("Unable to allocate process pids.\n");
		return -1;
	}

	for(i=0;i<NUMBER_THREADS;i++){
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], test_pid, NULL);
	}

	for(i=0;i<NUMBER_THREADS;i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}


void *test_pid(void *param){

	srand(time(NULL));
	int my_pid = allocate_pid(), sleep_time = (rand() % 10) + 1;
	printf("My pid is %d. Now I'm gonna sleep for %d seconds.\n", my_pid, sleep_time);
	sleep(sleep_time);
	release_pid(my_pid);

	pthread_exit(0);

}

int allocate_map(void){

	int i;
	if(bitmap_status == 0){
		for(i=0;i<(MAX_PID - MIN_PID); i++){
			bitmap[i] = 0;
		}

		bitmap_status = 1;
		return 1;
	}
	else
	{
		return -1;
	}
}

int allocate_pid(void){

	int i;
	for(i=0;i<(MAX_PID - MIN_PID); i++){
		if(bitmap[i] == 0){
			bitmap[i] = 1;
			return (i + MIN_PID);
		}
	}

	return -1;
}

void release_pid(int pid){

	bitmap[(pid - MIN_PID)] = 0;
}
