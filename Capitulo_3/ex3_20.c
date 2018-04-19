#include <stdio.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

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


int main()
{

	if(allocate_map() < 0){
		printf("Unable to allocate pids.\n");
	}

	int my_id = allocate_pid();

	printf("Process allocated with pid: %d \n",my_id);

	release_pid(my_id);


	return 0;
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



