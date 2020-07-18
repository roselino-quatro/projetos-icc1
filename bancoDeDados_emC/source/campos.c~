#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<util_strings.h>



typedef struct {
	char** tipos;
	char** nomes;
	int* tam_bytes;
} Campos;

typedef struct {
	int offset;
	int chave;
} Struct_index;

/* preenche os parametros dos campos */
int parametros_campos(char** campo, FILE* arquivo_metadata) {
	char* buffer;
	buffer = readline(arquivo_metadata);
	if(buffer[0] == '\0' || buffer[0] == '\r' || buffer[0] == '\n') {
		free(buffer);
		return 0;
	}
	*campo = strdup(ultima_palavra(buffer));
	free(buffer);
	return 1;
}

/* Retorna o tamanho de um tipo pelo seu nome */
int tamanho(char* string) {
	if(!strcmp(string, "int")) return 4;
	if(!strcmp(string, "float")) return 4;
	if(!strcmp(string, "double")) return 8;
	if(!strcmp(string, "char")) return 1;

	if(!strncmp(string, "char", 4)) {
		char* buffer;
		int resultado;
		buffer = strdup(&strchr(string, '[')[1]);
		strchr(buffer, ']')[0] = '\0';
		resultado = atoi(buffer);
		free(buffer);
		return resultado;
	}

	return 0;
}

/* Trata uma string de entrada e adciona ela em uma inserção de modo apropriado para seu tipo */
void* insere_valor(void** linhas, Campos tipos, const char* entrada, int pos) {
	void* linha = *linhas;
	if(!strcmp(tipos.tipos[pos], "float")) {
		linha = malloc(sizeof(float));
		*(float*)linha = (float) atof(entrada); 
		return linha;
	} else if(!strcmp(tipos.tipos[pos], "double")) {
		linha = malloc(sizeof(double));
		*(double*)linha = atof(entrada);
		return linha;
	}else if(!strcmp(tipos.tipos[pos], "char")) {
		linha = malloc(sizeof(char));
		*(char*)linha = entrada[0];
		return linha;
	}else if(!strcmp(tipos.tipos[pos], "int")) {
		linha = malloc(sizeof(int));
		*(int*)linha = atoi(entrada);
		return linha;
	} else if(!strncmp(tipos.tipos[pos], "char", 4)) {
		linha = malloc((tamanho(tipos.tipos[pos])) * sizeof(char));

		char* buffer;
		buffer = strdup(&entrada[1]);
		buffer[strlen(buffer)-1]  = '\0';

		strcpy((char*)linha, buffer);
		free(buffer);
		return linha;
	}
		return linha;
}

void imprime_valor(FILE* arquivo, Campos caracteristicas, int pos) {
	void* buffer;

	if(!strcmp(caracteristicas.tipos[pos], "float")) {
		buffer = malloc(sizeof(float));
		fread(buffer, sizeof(float), 1, arquivo);
		printf("%s: %.2f\n", caracteristicas.nomes[pos], *(float*)buffer);
	} else if(!strcmp(caracteristicas.tipos[pos], "double")) {
		buffer = malloc(sizeof(double));
		fread(buffer, sizeof(double), 1, arquivo);
		printf("%s: %.2lf\n", caracteristicas.nomes[pos], *(double*)buffer);
	}else if(!strcmp(caracteristicas.tipos[pos], "char")) {
		buffer = malloc(sizeof(char));
		fread(buffer, sizeof(char), 1, arquivo);
		printf("%s: %c\n", caracteristicas.nomes[pos], *(char*)buffer);
	}else if(!strcmp(caracteristicas.tipos[pos], "int")) {
		buffer = malloc(sizeof(int));
		fread(buffer, sizeof(int), 1, arquivo);
		printf("%s: %d\n", caracteristicas.nomes[pos], *(int*)buffer);
	} else if(!strncmp(caracteristicas.tipos[pos], "char", 4)) {
		buffer = malloc(tamanho(caracteristicas.tipos[pos])*sizeof(char));
		fread(buffer, tamanho(caracteristicas.tipos[pos]), sizeof(char), arquivo);
		printf("%s: %s\n", caracteristicas.nomes[pos], (char*)buffer);
	}
	free(buffer);
}

/* função auxiliar pro bubble sort */
void trocar(Struct_index* i1, Struct_index* i2) {
	Struct_index buffer;
	buffer = *i1;
	*i1 = *i2;
	*i2 = buffer;
}

/* Realiza bubble sort recursivamente */
void bubble_sort(Struct_index* vetor, int tam_index) {
	if(tam_index < 1) return;
	for (int i = 0; i < tam_index; i++) {
		if(vetor[i].chave > vetor[i+1].chave) {
			trocar(&vetor[i], &vetor[i+1]);
		}
	}
	bubble_sort(vetor, tam_index-1);
}

/* realiza uma busca binaria de maneira recursiva */
int busca_binaria(const Struct_index* vetor, int inicio, int fim, int chave) {
	if (fim < inicio) return -1;
	int meio = (fim+inicio) / 2;
	if (vetor[meio].chave == chave) {
		return meio;
	} else if (chave < vetor[meio].chave) {
		return busca_binaria(vetor, inicio, meio-1, chave);
	} else {
		return busca_binaria(vetor, meio+1, fim, chave);
	}
}
