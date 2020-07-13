#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define READLINE_BUFFER 4096 // macro para a readline

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
	} while (string[pos++] != '\n' && !feof(stream));
	string[pos-1] = '\0';
	string = (char *) realloc(string, pos);
	return string;
}

/* Separa uma string em duas partes apartir do pontei de uma palavra nessa string, concactena a palavra substituta na primeira parte */
void separaString(char* stringOrg, char* stringResultado, char* palavra, int size_palavra) {
	palavra[0] = '\0'; // Substitui a primeira letra da palavra por 0
	strcat(stringResultado, stringOrg); // Concatena a parte anterior a palavra no ponteiro de resultado
	strcpy(stringOrg, &palavra[size_palavra]); // Copia o resto no ponteiro da stringOriginal
	
}

int main(int argc, char* argv[]) {

	/* Declaração de variaveis */
	char* plavr_new; // Palavra substituta
	char* plavr_old; // Palavra a ser substituida
	char* frase;     // Frase a ser modificada
	char* resultado; // Frase final
	char* buffer;    // Buffer para lidar com junções
	int size_plavr_old;


	/* Leitura de Inputs */
	plavr_old = readline(stdin);
	plavr_new = readline(stdin);
	frase = readline(stdin);

	/* Allocação de memória e pegar o tamanho da palavra substituta */
	resultado = malloc(sizeof(char) * READLINE_BUFFER);
	size_plavr_old = strlen(plavr_old);

	/* While se repete enquanto existir palavras a serem substituidas na frase */
	while((buffer = strstr(frase, plavr_old))) {
		separaString(frase, resultado, buffer, size_plavr_old);
		strcat(resultado, plavr_new);
	}

	strcat(resultado, frase);

	printf("%s", resultado);
	
	free(plavr_new);
	free(plavr_old);
	free(frase);
	free(resultado);
	return 0;
}
