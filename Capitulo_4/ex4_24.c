# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>


//compile using: $ gcc ex4_22.c -o ex4_22 -lpthread 


void *get_primes(void *param);
int isprime(int number);

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: ex4_24.c <integer value>\n");
    	return -1;
	}


	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, get_primes, argv[1]);

	pthread_join(tid,NULL);
	
	return 0;
}

void *get_primes(void *param){

	int i, number = atoi(param);
	for(i=0;i<=number;i++){
		if(isprime(i) == 1)
		{
			printf("%d ",i);
		}

	}

	printf("\n");
	pthread_exit(0);
}

int isprime(int n){

	if(n == 0 || n == 1)
		return 0;

	//if the number is equal to 0 or 1, so it's not prime.
	else{
		if(n == 2 || n == 3)
			return 1;
			//if the number is equal to 2 or 3, so it's prime. 
		else if((n % 2 == 0) || (n % 3 == 0))
			//if the number is divisible by 2 or 3, so it's not prime.
			return 0;
		else{

			int i = 5, turn = 0;
			while(i < n){
				//i starts with 5
				// if i == n then the number is prime.
				if(n % i == 0)
				{
					// if the number n is divisible by i, then it's not prime.
					return 0;
				}
				else if (turn == 0)
				{
					i += 2;
					turn = 1;
				}
				else
				{
					i += 4;
					turn = 0;
				}

			}

			return 1;
			
		}
	}

}