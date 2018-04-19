#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* print_1(void) //fica continuamente
{
	// Imprime '1' continuamente em stderr.
	while(1)
	{
		fputc('1', stderr);//faz stderr escreve no terminal
		usleep(50000); // Atraso de 50000 us, ou 50 ms
	}
	return NULL;
}

void* print_2(void) //fica continumte faz a mesma copia porem escrever 2
{
	// Imprime '2' continuamente em stderr.
	while(1)
	{
		fputc('2', stderr);
		usleep(50000);
	}
	return NULL;
}
int main ()
{
	pthread_t thread_id1; // indentificadores de thread
	pthread_t thread_id2; // indentificand as thread
	printf("Serao criadas duas threads:\n");
	printf("   - A primeira ira chamar a funcao print_1(),\n");
	printf("     que escreve continuamente '1' na tela;\n");
	printf("   - A segunda ira chamar a funcao print_2(),\n");
	printf("     que escreve continuamente '2' na tela;\n");
	printf("Enquanto isso, o programa principal ira escrever\n");
	printf("continuamente '-' na tela.\n\n");
	printf("Repare na ordem com que os caracteres sao escritos.\n");
	printf("Percebe algum padrao?\n");
	system("pause");
	printf("Pressione CONTROL+C para sair do programa\n\n");
	pthread_create (&thread_id1, NULL, &print_1, NULL); //querendo escrever algo na tela, 1- recebe o identificador, 2 esta tudo padrao, está passando a função, null não tem parametro nenhum para função
	// Cria um novo thread. A nova thread irá chamar a função print_2
	pthread_create (&thread_id2, NULL, &print_2, NULL); // tambem quendo escrever algo na tela.
	// Imprime '-' continuamente em stderr.
	while(1)
	{
		fputc('-', stderr);
		usleep(50000);
	}
	// fputc ('-', stderr);
	return 0;
}













