
//compile usando: $ gcc ex4_22.c -o ex4_22 -lpthread -lm

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h> //rand() e srand() estao aqui
# include <time.h> //para a funcao time()
# include <math.h>

#define NUMBER_POINTS 1000000
double in_circle = 0;
//long int point_inside_circle = 0;

//void *random_points(void *point){
//}

void *pi_finder(void *param);

int main(int argc, char *argv[])
{
	double pi;
	srand(time(NULL));
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, pi_finder, NULL);
	pthread_join(tid, NULL);

	pi = (4.0*in_circle)/NUMBER_POINTS;
	printf("Pi number is %.2lf.\n",pi);
	
	return 0;
}

void *pi_finder(void *param){

	srand(time(NULL));
	int i,quadrante;
	double point_x, point_y,verify_point;
	
	for (i=0;i<NUMBER_POINTS;i++){
		//definir aleatoriamente um quadrante para o ponto
		// quadrante = 0 -> primeiro quadrante
		// quadrante = 1 -> segundo quadrante
		// quadrante = 2 -> terceiro quadrante
		// quadrante = 3 -> quarto quadrante

		quadrante = rand () % 4;
		
		if(quadrante == 0){
			point_x = (rand() % 1001)/1000.0;
			point_y = (rand() % 1001)/1000.0;
		}
		else if (quadrante == 1){
			point_x = (-1.00)*(rand() % 1001)/1000.0;
			point_y = (rand() % 1001)/1000.0;
		}
		else if (quadrante == 2){
			point_x = (-1.00)*(rand() % 1001)/1000.0;
			point_y = (-1.00)*(rand() % 1001)/1000.0;
		}
		else
		{
			point_x = (rand() % 1001)/1000.0;
			point_y = (-1.00)*(rand() % 1001)/1000.0;
		}

		verify_point = sqrt(pow(point_x,2.0) + pow(point_y,2.0));

		if(verify_point <= 1.0)
			in_circle ++;
			//printf("Ponto fora do circulo. Ponto em x: %.2lf , ponto em y: %.2lf \n",point_x[i],point_y[i]);
			//printf("Ponto dentro do circulo. Ponto em x: %.2lf , ponto em y: %.2lf \n",point_x[i],point_y[i]);			
	}
	pthread_exit(0);

}
