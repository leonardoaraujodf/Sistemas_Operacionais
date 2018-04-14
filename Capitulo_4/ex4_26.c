# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

// compile using: $ gcc ex4_26.c -o ex4_26 -lpthread 

struct information {
	int number;
	int *terms;
};


void *fibbo(void *param);
void *print_fibbo(void *param);

int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		fprintf(stderr, "usage: ex4_24.c <integer value>\n");
    	return -1;
	}

	struct information thread_args;
	thread_args.number = atoi(argv[1]) + 1;
	pthread_t tid[2];
	pthread_attr_t attr[2];

	pthread_attr_init(&attr[0]);
	pthread_create(&tid[0], &attr[0], fibbo, &thread_args);
	pthread_join(tid[0],NULL);
	pthread_attr_init(&attr[1]);
	pthread_create(&tid[1], &attr[1], print_fibbo, &thread_args);
	pthread_join(tid[1],NULL);

	return 0;
}


void *fibbo(void *param){

	struct information *value  = (struct information *) param;
	int i;
	value->terms = (int*) calloc(value->number,sizeof(int));

	for(i=0;i < value->number; i++){
		if(i == 0)
		{
			value->terms[i] = 0;
		}
		else if(i == 1)
		{
			value->terms[i] = 1;
		}
		else
			value->terms[i] = value->terms[i-1] + value->terms[i-2];
	}

	pthread_exit(0);
}

void *print_fibbo(void *param){
	struct information *value  = (struct information *) param;
	int i;
	for(i=0; i < (value->number - 1); i++)
		printf("%d ",value->terms[i]);

	printf("\n");
	free(value->terms);
	pthread_exit(0);
}




