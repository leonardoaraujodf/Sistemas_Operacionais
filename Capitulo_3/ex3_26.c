#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1


void reverse_charac(char *word, int number_of_letters);

int main(int argc, char *argv[]){

	int fd1[2],fd2[2], number_of_letters = strlen(argv[1]) + 1;
	pid_t pid;


	/* create the pipes */
	if (pipe(fd1) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	if(pipe(fd2) == -1){
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/*fork a child process*/
	pid = fork();

	if(pid < 0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}

	if(pid > 0){/*parent process*/
		/*close the unused end of the pipe1*/
		close(fd1[READ_END]);

		/*write to the pipe1*/
		write(fd1[WRITE_END], argv[1], number_of_letters);
		
		/*close the write end of the pipe1*/
		close(fd1[WRITE_END]);

		/*close the unused end of the pipe2*/

		close(fd2[WRITE_END]);

		char *read_msg = (char*) calloc(number_of_letters,sizeof(char));

		read(fd2[READ_END],read_msg, number_of_letters);

		/*close the read end of the pipe2*/

		close(fd2[READ_END]);

		printf("%s\n",read_msg);

	}

	else{/*child process*/

		/*close the unused end of the pipe1*/
		close(fd1[WRITE_END]);

		char *read_msg = (char*) calloc(number_of_letters,sizeof(char));

		read(fd1[READ_END],read_msg,number_of_letters);

		/*close the read end of the pipe1*/
		reverse_charac(read_msg,number_of_letters);

		/*close the unused end of the pipe2*/
		close(fd2[READ_END]);

		/*write to the pipe2*/
		write(fd2[WRITE_END],read_msg, number_of_letters);

		/*close the write end of the pipe2*/

		close(fd2[WRITE_END]);
	}

	return 0;
}


void reverse_charac(char *word, int number_of_letters){

	int i;
	for(i=0; i<number_of_letters ; i++){
		if((word[i] >= 97) && (word[i] <= 122)){
			word[i] -=  32;
		}
		else if((word[i] >= 65) && (word[i] < 90)){
			word[i] += 32;
		}
	}

}