// Codigo feito por Lourenço de Salles Roselino NºUsp 11796805
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<regex.h>
#include<math.h>

#define READLINE_BUFFER 4096 // macro para a readline
#define LISTA3_BUFFER 1024 // macro para mallocs da lista 3

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

/* Verifica se uma string é um palindromo */
int palindromo(char* str) {
	int tam_str = strlen(str);
	for(int i = 0; i < floor(tam_str/2); i++) {
		if(str[i] != str[tam_str-1-i]) return 0;
	}
	return 1;
}

/* Adaptação do strcmp para ser utilizado no qsort() */
int p_strcmp(const void* s1, const void* s2) {
	return strcmp(*(char **)s1, *(char **)s2);
}

/* função suporte para a função distancia */
int diferenca (char* maior, char* menor) {
	int tam_menor = strlen(menor);
	int tam_maior = strlen(maior);
	int similaridade = 0, buffer;
	for(int i = 0; i < tam_maior - tam_menor + 1; i++) {
		buffer = 0;
		for(int j = 0; j < tam_menor; j++) {
			if(menor[j] == maior[j+i]) {
				++buffer;
			}
		}
		similaridade = similaridade < buffer ? buffer : similaridade;
	}
	return similaridade;
}

/* Implementação de distancia entre duas strings */
int distancia (char * string1, char * string2)
{
	if(string1 > string2) {
		return diferenca(string1, string2);
	} else {
		return diferenca(string1, string2);
	}
}

int main(int argc, char* argv[]) {
	/* Declaração de variaveis */
	int qnt_total = 0, qnt_p1 = 0, qnt_palindromos = 0;
	int tam_palavra_curta = 0, tam_palavra_longa = 0, tam_palavra_longa_p2 = 0, tam_buffer, tam_lista_p3 = 0;
	int similaridade; // Essa variavel armazena o quão similar a W a atual palavra mais similar é
	char* n_arquivo;
	char* p1;
	char* p2;
	char* p3;
	char* palavra_w;
	char* buffer;
	char* palavra_curta = NULL;
	char* palavra_longa = NULL;
	char* palavra_longa_p2 = NULL;
	char* similar_w;
	char** lista_p3 = NULL;
	FILE* arquivo;
	regex_t regex1;
	regex_t regex2;
	regex_t regex3;

	/* Leitura das entradas */
	n_arquivo = readline(stdin);
	p1 = readline(stdin);
	p2 = readline(stdin);
	p3 = readline(stdin);
	palavra_w = readline(stdin);

	/* abertura de arquivos e compilação de regex */
	arquivo = fopen(n_arquivo,"r");
	regcomp(&regex1, p1, REG_EXTENDED);
	regcomp(&regex2, p2, REG_EXTENDED);
	regcomp(&regex3, p3, REG_EXTENDED);

	/* Lendo as linhas do arquivo e processando elas */
	buffer = readline(arquivo); // a primeira linha é lida fora do loop para lidar com um \n extra no final do arquivo
	similar_w = malloc((strlen(buffer)+1) * sizeof(char));
	strcpy(similar_w, buffer);
	similaridade = distancia(buffer, palavra_w);
	while(!feof(arquivo)) {
		qnt_total++;
		/* tamanho do buffer vai ser utilizado em varias partes do codigo */
		tam_buffer = strlen(buffer);

		/* pega verifica se o buffer é maior que a atual palavra mais longa */
		if(tam_buffer > tam_palavra_longa) {
			tam_palavra_longa = tam_buffer;
			palavra_longa = realloc(palavra_longa, (tam_buffer+1) * sizeof(char));
			strcpy(palavra_longa, buffer);
		}
		
		/* verifica se o buffer é maior que a palavra mais longa */
		if(tam_buffer < tam_palavra_curta || !tam_palavra_curta) {
			tam_palavra_curta = tam_buffer;
			palavra_curta = realloc(palavra_curta, (tam_buffer+1) * sizeof(char));
			strcpy(palavra_curta, buffer);
		}

		/* verifca se o buffer encaixa no padrão 1 */
		if(!regexec(&regex1, buffer, 0, NULL, 0)) qnt_p1++;

		/* verifica se o buffer se encaixa no padrão 2, se sim verifica se o buffer é maior que a atual maior palavra do padrão 2 */
		if(!regexec(&regex2, buffer, 0, NULL, 0)) {
			if(tam_buffer > tam_palavra_longa_p2) {
				tam_palavra_longa_p2 = tam_buffer;
				palavra_longa_p2 = realloc(palavra_longa_p2, (tam_buffer+1) * sizeof(char));
				strcpy(palavra_longa_p2, buffer);
			}
		}

		/* verifica se o buffer se encaixa no padrão 3, se sim adciona ele no vetor de strings do padrão 3 */
		if(!regexec(&regex3, buffer, 0, NULL, 0)) {
			if (tam_lista_p3 % LISTA3_BUFFER == 0) {
				lista_p3 = (char**) realloc(lista_p3, ((tam_lista_p3 / LISTA3_BUFFER) + 1) * LISTA3_BUFFER * sizeof(char*));
			}
			lista_p3[tam_lista_p3] = (char*) malloc((tam_buffer+1) * sizeof(char));
			strcpy(lista_p3[tam_lista_p3], buffer);
			tam_lista_p3++;
		}

		/* Verifica se o buffer é mais similar a palavra W, se sim, substitui */
		if( similaridade < distancia(buffer, palavra_w) ) {
			similar_w = realloc(similar_w, (strlen(buffer)+1) * sizeof(char));
			strcpy(similar_w, buffer);
			similaridade = distancia(buffer, palavra_w);
		} else if (similaridade == distancia(buffer, palavra_w) && tam_buffer < strlen(similar_w)) {
			similar_w = realloc(similar_w, (strlen(buffer)+1) * sizeof(char));
			strcpy(similar_w, buffer);
			similaridade = distancia(buffer, palavra_w);
		}

		qnt_palindromos += palindromo(buffer);
		
		free(buffer);
		buffer = readline(arquivo);
	}
	/* uso minimo de allocação na matriz e sorting */
	lista_p3 = realloc(lista_p3, tam_lista_p3 * sizeof(char*));
	qsort(&lista_p3[0], tam_lista_p3, sizeof(*lista_p3), p_strcmp);


	printf("%d\n", qnt_total);
	printf("%s\n", palavra_curta);
	printf("%s\n", palavra_longa);
	printf("%d\n", qnt_p1);
	printf("%d\n", qnt_palindromos);
	printf("%s\n", palavra_longa_p2);

	for(int i = 0; i < tam_lista_p3; i++) printf("%s\n", lista_p3[i]); 

	printf("%s\n", similar_w);

	free(n_arquivo);
	free(p1);
	free(p2);
	free(p3);
	free(palavra_w);
	free(palavra_curta);
	free(palavra_longa);
	free(palavra_longa_p2);
	free(buffer);
	free(similar_w); 
	
	for(int i = 0; i < tam_lista_p3; i++) free(lista_p3[i]);
	free(lista_p3);

	fclose(arquivo);

	regfree(&regex1);
	regfree(&regex2);
	regfree(&regex3);
	
	return 0;
}
