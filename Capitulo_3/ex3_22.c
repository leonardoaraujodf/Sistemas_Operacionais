#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <string.h> 


/* Compile usando: $ sudo gcc ex3_22.c -o ex3_22 -lrt*/

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("Use: ./ex3_21 <integer>\n");
		return -1;
	}
	else if(atoi(argv[1]) <= 0){
		printf("Number should be greater than 1.\n");
		return -2;
	}

	const int SIZE = 4096;
	const char *name = "My_numbers";

	int shm_fd;
	void *ptr;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	
	pid_t pid;
	pid = fork();

	if(pid == 0){

		/*Child Process*/
		/*The child will write to the shared memory*/
		ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		int n = atoi(argv[1]);
		char message[8];
		sprintf(message,"%d ",n);
		sprintf(ptr,"%s",message);
		ptr += strlen(message);

		while(n > 1)
		{
			if(n % 2 == 0)
			{
				n = n/2;
			}
			else
			{
				n = 3*n + 1;
			}

			sprintf(message,"%d ",n);
			sprintf(ptr,"%s",message);
			ptr += strlen(message);
		}
		sprintf(ptr,"\n");

	}

	else{
		/*Parent Process*/
		/*Should wait until the children writes the values in the shared memory*/
		/*After that, it will read the data and print it.*/
		wait(NULL);

		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		printf("%s",(char *)ptr);
		shm_unlink(name);
	}

	return 0;
}