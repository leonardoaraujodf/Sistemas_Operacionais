#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h> //rand() e srand() estao aqui
#include <time.h> //para a funcao time()

//compile using: gcc Ex_5_43.c -o Ex_5_43 -lpthread -lrt


/*DEFINITIONS*/

#define MIN_PID 30
#define MAX_PID 40
#define NUMBER_THREADS 1000

/*GLOBAL VARIABLES*/

int bitmap[(MAX_PID - MIN_PID)];
int bitmap_status = 0;

/*FUNCTIONS*/

int allocate_map(void);
/*Creates and initilizes a data structure for representing pids; returns - 1 if unsuccessful
retuns 1 if successful */

int allocate_pid(void);
/* Allocates and returns a pid; returns - 1 if unable to allocate a pid (all pids are in use)*/

void release_pid(int pid);
/* Releases a pid */


/*THREADS*/
void *test_pid (void *param);


/*SEMAPHORES*/
sem_t mutex, mutex_print;

int main(){

	sem_init(&mutex, 0, MAX_PID - MIN_PID);
	sem_init(&mutex_print, 0, 1);

	/* Create the semaphore and initialize it to the number of PIDs available (that will be our resource).*/
	/* The second semaphore ensures that only one thread will print in the screen in a time.*/

	pthread_t tid[NUMBER_THREADS];
	pthread_attr_t attr[NUMBER_THREADS];

	int i;

	printf("Initializing a map with process PIDs...\n");

	if(allocate_map() < 0)
	{
		printf("Unable to allocate process PIDs.\n");
		return -1;
	}

	printf("Done.\n");

	srand(time(NULL));

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


	int sleep_time = (rand() % 1000000) + 1;

	/*1,000,000 --> 1 s*/

	/* acquire the semaphore */
	sem_wait(&mutex);
	
	/*START OF CRITICAL SECTION 1*/

		int my_pid = allocate_pid();
	
		/*START OF CRITICAL SECTION 2*/
		sem_wait(&mutex_print);
			printf("My pid is %d. Now I'm gonna sleep for %d micro-seconds.\n", my_pid, sleep_time);
		sem_post(&mutex_print);
		/*END OF CRITICAL SECTION 2*/	

		usleep(sleep_time);
		

		/*START OF CRITICAL SECTION 3*/
		sem_wait(&mutex_print);
			printf("I'm %d and now I'm exiting... \n",my_pid);
		sem_post(&mutex_print);
		/*END OF CRITICAL SECTION 3*/

		release_pid(my_pid);

	/*END OF CRITICAL SECTION 1*/
	sem_post(&mutex);

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

