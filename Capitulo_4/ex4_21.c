#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/*Compile using: gcc ex4_21.c -o ex4_21 -lpthread -lm*/
/*Execute using: ./ex4_21 "90 81 78 95 79 72 85"*/


int global_minimum;
int global_maximum;
double global_average;


double average(int *data);
int minimum(int *data);
int maximum(int *data);
void *thr_minimum(void *param);
void *thr_maximum(void *param);
void *thr_average(void *param);
int *convert_char_int(char *data);
int number_spaces(char *data);


int main(int argc, char *argv[]){

	if(argc < 2){

		printf("Use: ./ex4_21 \"<Vector of numbers>\"\n");
		return -1;
	}

	int *data = convert_char_int(argv[1]), i;

	pthread_t tid[3];
	pthread_attr_t attr[3];

	pthread_attr_init(&attr[0]);
	pthread_create(&tid[0], &attr[0], thr_average, data);

	pthread_attr_init(&attr[1]);
	pthread_create(&tid[1], &attr[1], thr_minimum, data);

	pthread_attr_init(&attr[2]);
	pthread_create(&tid[2], &attr[2], thr_maximum, data);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	printf("Average: %.2lf \n",global_average);
	printf("Minimum: %d \n",global_minimum);
	printf("Maximum: %d \n",global_maximum);
	

	return 0;
}

double average(int *data){

	int i = 0;
	double d_average = 0;

	while(data[i] != '\0'){
		d_average += data[i];
		i++;
	}

	d_average = d_average/i;

	return d_average;
}

int minimum(int *data){

	int i = 0, i_minimum;

	while(data[i] != '\0'){
		if(i == 0){
			i_minimum = data[i];
		}
		else if (data[i] < i_minimum){
			i_minimum = data[i];
		}
		i++;
	}

	return i_minimum;

}

int maximum(int *data){

	int i = 0, d_maximum;
	while(data[i] != '\0'){
		if(i == 0){
			d_maximum = data[i];
		}
		else if(data[i] > d_maximum){
			d_maximum = data[i];
		}
		i++;
	}

	return d_maximum;
}

void *thr_minimum(void *param){

	int *data = (int *) param;

	global_minimum = minimum(data);

	pthread_exit(0);
}

void *thr_maximum(void *param){

	int *data = (int *) param;

	global_maximum = maximum(data);

	pthread_exit(0);

}

void *thr_average(void *param){

	int *data = (int *) param;

	global_average = average(data);

	pthread_exit(0);

}

int *convert_char_int(char *data){


	int num_numbers = number_spaces(data) + 1;
	int *i_data = (int *)calloc(num_numbers, sizeof(int)), i, j = 0, k = 1, data_length = strlen(data);


	for(i = (data_length - 1); i >= 0; i--){
		
		if(data[i] != ' '){
			i_data[(num_numbers - k)] = (data[i] - '0')*pow(10,j) + i_data[(num_numbers - k)];
			j++;
		}
		else{
			j = 0 ;
			k++;
		}

	}

	return i_data;


}


int number_spaces(char *data){

	int i = 0,number_spaces = 0;
	while(data[i] != '\0'){

		if(data[i] == ' '){
			number_spaces ++;
		}
		i++;
	}

	return number_spaces;
}



