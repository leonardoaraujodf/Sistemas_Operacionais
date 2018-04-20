#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

int main (int argc, char *argv[]){

	if(argc < 3){
		fprintf(stderr,"Use: $ ./ex3_27.c input.txt copy.txt");
		return -1;
	}

	int fp1,fp2,fd[1], number_letters = 0;

	pid_t pid;


	if(pipe(fd) == -1){
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid = fork();

	if(pid > 0){/*parent process*/

		/*Open the file*/
		fp1 = open(argv[1], O_RDONLY);

		if(fp1 == -1){
			perror("Cannot open the file.\n");
			exit(-1);
		}
		/*Variables that will verify how many characteres the file has.*/
		char c;

		/*Taking how many characteres*/
		while(read(fp1,&c,1) != 0){
			number_letters++;
		}
		/*Repositioning the file pointer */
		lseek(fp1,0,SEEK_SET);

		/*creating a buffer to copy that file into memory*/
		char *buffer = (char*) calloc(number_letters,sizeof(char));
		/*reading the file*/
		read(fp1,buffer,number_letters);

		/*closing the unused end of pipe*/
		close(fd[READ_END]);

		/*writing how many characteres will be sent*/
		write(fd[WRITE_END],&number_letters,sizeof(int));

		/*writing the data read*/
		write(fd[WRITE_END],buffer,number_letters + 1);

		/*closing the file*/
		close(fp1);

		/*closing the write end of pipe*/
		close(fd[WRITE_END]);
		/*Waiting until the child finishes*/
		wait(NULL);

	}
	else{/*childen process*/

		
		/*closing the unused end of the pipe*/
		close(fd[WRITE_END]);

		/*Taking how many characteres was read by the parent*/
		read(fd[READ_END],&number_letters,sizeof(int));

		/*Creating a buffer to read the data sended by the parent*/
		char *buffer = (char*) calloc(number_letters,sizeof(char));

		/*Reading the data sended by pipe*/

		read(fd[READ_END],buffer,number_letters + 1);

		/*creating the new file copy*/

		fp2 = open(argv[2], O_RDWR | O_CREAT, S_IRWXU);

		/*writing the data to the new file*/

		write(fp2,buffer,number_letters);

		/*closing the read end of the pipe*/
		close(fd[READ_END]);

		/*closing the new file created*/
		close(fp2);
	}
	return 0;
}