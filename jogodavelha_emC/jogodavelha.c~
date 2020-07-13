#include<stdlib.h>
#include<stdio.h>

/* Criação de Funções  */

/* Alloca e retorna uma matriz de chars já preenchidos  para usar de tabuleiro */
char** montarTabuleiro() {
	char** M; 
	M = (char**) malloc(3 * sizeof(char*));
	for (int i = 0; i < 3; i++) {
		M[i] = (char*) malloc(3);
		for(int j = 0; j < 3; j++) {
			M[i][j] = ((i * 3) + j + 1) + '0';
		}
	}
	return M;
}

/* Da free no tabuleiro */
void freeTabuleiro(char** M) {
	for (int i = 0; i < 3; i++) {
	free(M[i]);
	}
	free(M);
}

/* Imprime o estado atual do tabuleiro */
void imprimeTabuleiro(char** M) {
	for (int i = 0; i < 3; i++) {
			printf("%c   |%c   |%c   |\n", M[i][0],M[i][1],M[i][2]);
			printf("----+----+-----\n");
		}
}

/* Checa se um jogador venceu */
int checaTabuleiro(char** M, int num_jogadas) {
	for(int i = 0; i < 3; i++) { // Checa por todas as linhas
		if( M[i][0] ==  M[i][1] && M[i][1] == M[i][2] ) {
			imprimeTabuleiro(M);
			printf("Fim do jogo! O jogador %c venceu!", M[i][0]);
			return 1;
		}
	}

	for(int i = 0; i < 3; i++) { // Checa por todas as colunas
		if( M[i][0] ==  M[0][i] && M[1][i] == M[2][i] ) {
			imprimeTabuleiro(M);
			printf("Fim do jogo! O jogador %c venceu!", M[0][i]);
			return 1;
		}
	}

	if( M[0][0] ==  M[1][1] && M[1][1] == M[2][2] ) { // Checa a primeira diagonal
		imprimeTabuleiro(M);
		printf("Fim do jogo! O jogador %c venceu!", M[0][0]);
		return 1;
		}

	if( M[2][0] ==  M[1][1] && M[1][1] == M[0][2] ) { // Checa a segunda diagonal
		imprimeTabuleiro(M);
		printf("Fim do jogo! O jogador %c venceu!", M[2][0]);
		return 1;
		}

	if(num_jogadas == 9) { // Caso todas as casa tenham sido preenchidas
		imprimeTabuleiro(M);
		printf("Deu velha!");
		return 1;
	}

	return 0;
}

/* Recebe e uma jogada e se ela for possivel retorna true */
int jogada(char** M, char jogadorAtual) {
	int row, col, input;
	scanf("%d", &input); 
	row = (int) (input - 0.1) / 3; // Calcula a linha baseado no input do usuario
	col = (int) input - 1 - (3 * row); // Calcula a coluna baseado no input do usuario

	if (M[row][col] != 'X' && M[row][col] != 'O') { // Verifica se a jogada é valida ou não
		M[row][col] = jogadorAtual;
		return 1;
	} else {
	printf("Jogada inválida! Escolha outra casa.\n");
	return 0;
	}
}
int main(int argc, char* argv[]) {

	/* Declaração de variaveis */
	char** tabuleiro;
	tabuleiro = montarTabuleiro();
	char jogadorAtual = 'X';
	int num_jogadas = 0;

	/* Impressões Iniciais */
	imprimeTabuleiro(tabuleiro);
	printf("Jogo da velha!\n");
	printf("Escolha um número para jogar, jogador %c!\n", jogadorAtual);

	/* Primeira jogada separada das outras */
	while(!jogada(tabuleiro, jogadorAtual)) {}
	num_jogadas++;
	jogadorAtual = jogadorAtual == 'X' ? 'O' : 'X';

	/* do loop que se repete até um jogador vencer */
	do {
	imprimeTabuleiro(tabuleiro);
	printf("Escolha um número para jogar, jogador %c!\n", jogadorAtual);
	while(!jogada(tabuleiro, jogadorAtual)) {}
	num_jogadas++;
	jogadorAtual = jogadorAtual == 'X' ? 'O' : 'X';

	}	while(!checaTabuleiro(tabuleiro, num_jogadas));



	freeTabuleiro(tabuleiro);
	return 0;
}
