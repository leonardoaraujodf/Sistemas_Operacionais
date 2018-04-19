#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Imprime continuamente um caractere em stderr
void* print_xs (void* c) //QUANDO É VOID PODE ESCREVER QUALQUER COISA DOUBLE CHAR INT...
{
	char *charactere = (char *) c; //(CHAR *) INTRERPRETA COMO SE FOSSE PONTEIRA PARA VOID, TÁ DANDO ENDEREÇÕ 3000 ENTÃO VAI NO ENDEREÇO 3000 E ESCREVE A VARIAVEL DENTRO DESSE ENDEREÇO
	while (1)
	{
		fputc(*charactere, stderr); // QUALQUER CARACTERE PARA SER ESCRITO NA TELA
		usleep(50000);
	}

	return NULL;
}
int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	char c1 = 'A';
	char c2 = 'B';
	printf("Serao criadas duas threads:\n");
	printf("   - A primeira ira chamar a funcao print_xs(),\n");
	printf("     para escrever continuamente 'A' na tela;\n");
	printf("   - A segunda ira chamar a funcao print_xs(),\n");
	printf("     que escreve continuamente 'B' na tela;\n");
	printf("Enquanto isso, o programa principal ira escrever\n");
	printf("continuamente '-' na tela.\n\n");
	printf("A diferenca deste exemplo para o anterior eh que\n");
	printf("neste a funcao print_xs() recebeu paramentos de entrada.\n");
	system("pause");
	printf("Pressione CONTROL+C para sair do programa\n\n");
	pthread_create (&thread_id1, NULL, &print_xs, &c1); ///VAI ESCREVER NO ENDEREÇO EM C1 QUE É A MAIUSCULO
	pthread_create (&thread_id2, NULL, &print_xs, &c2);// A MESMA COISA POREM B MAIUSCULO
	// Imprime '-' continuamente em stderr
	while(1)
	{
		fputc('-', stderr);
		usleep(50000);
	}
	return 0;
}















