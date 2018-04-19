#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

	pid_t pid;

	pid = fork();

	if(pid == 0){

		/*Child Process*/
		int n = atoi(argv[1]);
		printf("%d ",n);

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

			printf("%d ",n);
		}
		printf("\n");

	}

	else{
		/*Parent Process*/
		wait(NULL);
	}

	return 0;

}