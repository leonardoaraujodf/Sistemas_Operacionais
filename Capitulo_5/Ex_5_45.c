#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h> //rand() e srand() estao aqui
#include <time.h>


/*compile using: gcc Ex_5_45.c -o Ex_5_45 -lpthread -lrt*/

#define NUMBER_THREADS_BARRIER 5

#define NUMBER_THREADS 10

int global_threads_reached;

sem_t mutex;


int init(int N);
int barrier_point(void);
void *thread_func(void *param);

int main(){

	srand(time(NULL));

	pthread_t tid[NUMBER_THREADS];
	pthread_attr_t attr[NUMBER_THREADS];

	int i;

	if(init(NUMBER_THREADS_BARRIER) < 0){
		printf("Error creating barrier.\n");
		return -1;
	}
	else
		printf("Barrier created.\n");

	for(i=0;i<NUMBER_THREADS;i++){
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], thread_func, NULL);
	}

	for(i=0;i<NUMBER_THREADS;i++){
		pthread_join(tid[i], NULL);
	}


	return 0;
}

void *thread_func(void *param){

	int sleep_time = 1000000;//(rand() % 1000000) + 1;

	long int my_pid = (int) pthread_self();

	printf("My PID is %ld and I will sleep for %d micro-seconds.\n",my_pid,sleep_time);

	usleep(sleep_time);

	/*BARRIER POINT*/
	if(barrier_point() < 0){
		printf("Error trying to enter in the barrier point.\n");
		pthread_exit(0);
	}

	printf("I'm %ld and I'm gonna finish now.\n",my_pid);

	pthread_exit(0);
}

int init(int N){
	global_threads_reached = N;
	
	return sem_init(&mutex, 0, 0);

}

int barrier_point(void){
	if(global_threads_reached > 1){
		global_threads_reached--;
		return sem_wait(&mutex);
	}
	else if(global_threads_reached == 1){
		global_threads_reached--;

		int i;

		for(i=0; i<(NUMBER_THREADS_BARRIER); i++){
			sem_post(&mutex);
		}

		return 0;
	}
	else{
		return 0;
	}
}