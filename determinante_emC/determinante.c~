#include<stdlib.h>
#include<stdio.h>

/* Declaração de funções  */

/* Da free em uma matriz usando seu número de linhas */
void freeMatrix(int** M, int row) {
	for (int i = 0; i < row; i++) { 
		free(M[i]);
	}
	free(M);
}

int main(int argc, char* argv[]) {
	
	/* Declaração de variaveis */
	int** matriz; // Matriz 
	int row, col; // Linhas e colunas
	int i, j; 	  // variaveis para for loop
	int determinante; // Resultado

	/* Inputs do usuario */
	scanf("%d", &row);
	scanf("%d", &col);

	/* Checagem da matriz */
	if(row > 3 || col > 3) { // Checa se a entrada é valida
		printf("Entradas invalidas!");

	} else if (row != col) { // Checa se a matriz é quadrada
		printf("A matriz de entrada nao possui determinante!");

	} else { 				 // Calculo caso ela seja valida e quadrada

		/* Criação da matriz */
		matriz = malloc(row * sizeof(int*));
			for (i = 0; i < row; i++) {
				matriz[i] = malloc(col * sizeof(int));
		}


		for(i = 0; i < row; i++) { // Itera por cada linha da matriz
			for(j = 0; j < col; j++) { // Itera por cada coluna da matriz
				scanf("%d", &matriz[i][j]);
			}
		}

		/* Switch que seleciona as operações adequadas pra cada tamanho de matriz */
		switch(col) {
			case 1:
				determinante = matriz[0][0];
				printf("O determinante da matriz de entrada equivale a %d e tem ordem %d", determinante, col);
				break;
			case 2:
				determinante = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
				printf("O determinante da matriz de entrada equivale a %d e tem ordem %d", determinante, col);
				break;
			case 3:
				determinante = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]);
				determinante = determinante - (matriz[0][2] * matriz[1][1] * matriz[2][0]) - (matriz[0][0] * matriz[1][2] * matriz[2][1]) - (matriz[0][1] * matriz[1][0] * matriz[2][2]);
				printf("O determinante da matriz de entrada equivale a %d e tem ordem %d", determinante, col);
				break;
		}

		freeMatrix(matriz, row);
	}


	return 0;
}
