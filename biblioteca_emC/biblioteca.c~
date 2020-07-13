#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define READLINE_BUFFER 4096 // macro para a readline

/* Struct responsavel por armazenar informações dos livros */
struct Livro {
	char* nome;
	int dias;
};

/* Cria um vetor de struct Livro e preenche de livros vazios */
struct Livro* construirColecao(int tam) {
	struct Livro* colecao;
	colecao = (struct Livro*) malloc(tam * sizeof(struct Livro));
	for (int i = 0; i < tam; i++) { // Depois da allocação todo espaço recebe valores vazios
		colecao[i].nome = malloc(256 * sizeof(char));
		strcpy(colecao[i].nome, "vazio\0");
		colecao[i].dias = 0;
	}

	return colecao;
}

/* Retorna a primeira occorencia de um livro em um vetor */
struct Livro* buscarLivro(struct Livro* colecao, char* nome, int tam) {
	for(int i = 0; i < tam; i++) {
		if(strcmp(colecao[i].nome,nome) == 0) {
			return &colecao[i];
		}
	}
	return NULL;
}

/* Adciona um livro a um vetor de livros, substituindo um espaço vazio */
int adcionarLivro(struct Livro* livro, struct Livro* colecao, int tam) {
	if(buscarLivro(colecao, livro->nome, tam)) {
		return 0; // Retorna zero caso o vetor já tenha um livro de mesmo nome
	} else {
	struct Livro* vazio = buscarLivro(colecao, "vazio", tam);
	strcpy(vazio->nome, livro[0].nome);
	vazio->dias = livro->dias;
	return 1;
	}
}

/* Sobrescreve um livro */
void deletarLivro(struct Livro* livro, struct Livro* colecao, int tam) {
	for(int i = 0; &livro[i] < &colecao[tam-1]; i++) { // Repete o for até o penultimo valor da coleção
		if(strcmp(livro[i].nome, "vazio\0") != 0) {
		strcpy(livro[i].nome, livro[i+1].nome);
		livro[i].dias = livro[i+1].dias; 
		}
	}
	strcpy(colecao[tam-1].nome, "vazio\0");
	colecao[tam-1].dias = 0;
}

/* Lê uma linha e retorna um ponteiro para a string */
char *readline(FILE *stream) { 
	char *string = 0;
	int pos = 0;
	do {
		if (pos % READLINE_BUFFER == 0) {
			string = (char *) realloc(string,
					(pos / READLINE_BUFFER + 1) * READLINE_BUFFER);
		}
		string[pos] = (char) fgetc(stream);
		pos++;
	} while (string[pos-1] != '\n' && string[pos-1] != EOF);
	
	if (pos >= 2 && string[pos - 2] == '\r') {
    	string[pos - 2] = '\0';
		string = (char *) realloc(string, pos-1);

	}
	else {
		string[pos-1] = '\0';
	}
	return string;
}


int main(int argc, char* argv[]) {

	/* Declaração de Variaveis */
			/* Variaveis para vetores e vetores */
	struct Livro* colecaoBiblioteca;
	struct Livro* colecaoUsuario;
	int tamBiblioteca, tamUsuario = 0;

			/* Variaveis para buffers */
	struct Livro* buffer;
	buffer = (struct Livro*) malloc(1 * sizeof(struct Livro));
	char* nome;
	char op;

	scanf("%d", &tamBiblioteca);
	getc(stdin);
	getc(stdin);
	colecaoBiblioteca = construirColecao(tamBiblioteca);

	/* For que ira receber e armazenar as informações dos livros da biblioteca */
	for(int i = 0; i < tamBiblioteca; i++) {
		buffer->nome = readline(stdin);
	 	scanf("%d",	&buffer->dias);
		getc(stdin);
		getc(stdin);
		adcionarLivro(buffer, colecaoBiblioteca, tamBiblioteca);


	}

	colecaoUsuario = construirColecao(10);

	do { // Se repete enquanto o usuario não digitar 4
		op = fgetc(stdin);
		getc(stdin);
		getc(stdin);

		switch(op) {
			case '1': // Operações para alugar um livro
				// fgetc(stdin); // fgetc para limpar o stdin
				printf("Digite o livro que voce procura:\n");
				nome = readline(stdin);
				buffer = buscarLivro(colecaoBiblioteca, nome, tamBiblioteca);
				if(!buffer) {
					printf("Livro nao encontrado na biblioteca\n");
				} else if(tamUsuario > 9) {
					printf("Voce ja tem 10 livros alugados\n");
				} else if(!adcionarLivro(buffer, colecaoUsuario, 10)){
					printf("Livro ja alugado\n");
				} else {
					printf("%s alugado com sucesso\n", buffer->nome);
					tamUsuario++;
				}
				free(nome);
				break;
			case '2': // Listar livros
				if (tamUsuario != 0) {
					printf("Voce tem %d livro(s) alugado(s)\n", tamUsuario);
					for (int i = 0; i < 10; i++) {
						if(strcmp(colecaoUsuario[i].nome, "vazio")) {
						printf("Livro nome: %s\n", colecaoUsuario[i].nome);
						printf("Devolve-lo daqui %d dias\n", colecaoUsuario[i].dias);
						
						}
					}
				}
				else {
						printf("Voce nao tem livros alugados\n");
					}
				break;
			case '3': // Devolver livros
				// fgetc(stdin);
				printf("Digite o livro que deseja devolver:\n");
				nome = readline(stdin);
				buffer = buscarLivro(colecaoUsuario, nome, tamUsuario);
				if(!buffer) {
					printf("Voce nao possui esse livro\n");
				} else {
					printf("Livro %s foi devolvido com sucesso\n", buffer->nome);
					deletarLivro(buffer, colecaoUsuario, 10);
					tamUsuario--;
				}
				free(nome);
				break;
			default:
					break;
				}
	} while(op != '4');

	
	printf("Programa finalizado\n");

	free(colecaoUsuario);
	free(colecaoBiblioteca);

	return 0;
}

