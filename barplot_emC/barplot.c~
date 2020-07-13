#include<stdlib.h>
#include<stdio.h>

int main(int argc, char* argv[]) {

	/* Declaração de variaveis */
	int* dados; // Vetor para guardar os dados das barras
	int qnt_dados, qnt_barras, input, i, j; // Quantidade de dados e quantidade de barras e input para armazenar pra qual barra deve ir a informação

	/* Inputs */
	scanf("%d", &qnt_barras);
	scanf("%d", &qnt_dados);

	/* Calloc do vetor de dados */
	dados = (int*) malloc(qnt_barras * sizeof(int));

	/* For para limpar o lixo do vetor */
	for(i = 0; i < qnt_barras; i++) {
		dados[i] = 0;
	}

	/* For para pegar os inputs de dados */
	for(i = 0; i<qnt_dados; i++)	{
		scanf("%d", &input);
		dados[input]++;
	}

	/* Nested for para imprimir os resultados */
	for(i = 0; i < qnt_barras; i++) {
		printf("%d - ",i);
		for(j = 0; j < dados[i]; j++) { printf("#"); }
		printf("\n");
	}



	/* Free e return */
	free(dados);
	return 0;
}
