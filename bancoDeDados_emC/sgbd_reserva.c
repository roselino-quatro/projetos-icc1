#include<stdlib.h>
#include<stdio.h>
#include<string.h>

 /* util_strings.h */
#define READLINE_BUFFER 4096 // macro para a readline

// Readline basico com alterações para lidar com \r
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

/* Encontra a ultima palavra de uma string e retorna o resto */
char* ultima_palavra(const char* string) {
	char* buffer;
	buffer = strrchr(string, ' ');
	return &buffer[1];
}

/* troca a extensão do nome de um arquivo pra idx */
char* troca_extensao(const char* string) {
	char* buffer;
	int tam = strlen(string);
	buffer = strdup(string);
	buffer[tam-1] = 'x';
	buffer[tam-2] = 'd';
	buffer[tam-3] = 'i';
	return(buffer);
}

/* campos.h */
typedef struct {
	char** tipos;
	char** nomes;
	int* tam_bytes;
} Campos;

typedef struct {
	int pos;
	void** valores; // O primeiro valor é a chave
} Insercao;

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
void insere_valor(Insercao* linha, Campos tipos, const char* entrada, int pos) {
		if(!strcmp(tipos.tipos[pos], "float")) {
			linha->valores[pos] = malloc(sizeof(float));
		*(float*)&linha->valores[pos] = (float) atof(entrada); 
	} else if(!strcmp(tipos.tipos[pos], "double")) {
		linha->valores[pos] = malloc(sizeof(double));
		*(double*)&linha->valores[pos] = atof(entrada);
		*(float*)&linha->valores[pos] = (float) atof(entrada); 
	}else if(!strcmp(tipos.tipos[pos], "char")) {
		linha->valores[pos] = malloc(sizeof(char));
		*(char*)&linha->valores[pos] = entrada[0];
	}else if(!strcmp(tipos.tipos[pos], "int")) {
		linha->valores[pos] = malloc(sizeof(int));
		*(int*)&linha->valores[pos] = atoi(entrada);
	} else if(!strncmp(tipos.tipos[pos], "char", 4)) {
		linha->valores[pos] = malloc((tamanho(tipos.tipos[pos])) * sizeof(char));

		char* buffer;
		buffer = strdup(&entrada[1]);
		buffer[strlen(buffer)-1]  = '\0';

		strcpy((char*)&linha->valores[pos], buffer);
		free(buffer);
	}
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
int busca_binaria(const Struct_index *vetor, int inicio, int fim, int chave) {
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

int main(int argc, char* argv[]) {
	/* Declaração de variaveis */
	Campos campos;
	Insercao* linhas;
	linhas = NULL;
	Struct_index* index;
	index = NULL;
	char* nome_metadata;
	FILE* arquivo_metadata; 
	char* nome_registro;
	FILE* arquivo_registro; 
	char* nome_index;
	FILE* arquivo_index; 
	char* buffer;
	char* operador;
	int offset = 0, campo_qnt = 0, linhas_qnt = 0, index_existe = 0,  pos;

	/* Abertura do arquivo fornecido na entrada */
	nome_metadata = readline(stdin);
	arquivo_metadata = fopen(nome_metadata, "r");
	campos.tipos = NULL;
	campos.nomes = NULL;
	campos.tam_bytes = NULL;

	/* Recebe o nome do arquivo que guarda os registros e do de index */
	buffer = readline(arquivo_metadata);
	nome_registro = strdup(ultima_palavra(buffer));
	nome_index = troca_extensao(nome_registro);
	free(buffer);

	arquivo_registro = fopen(nome_registro, "wb");
	fclose(arquivo_registro);

	/* realiza a leitura dos tipos e nome dos campos */
	while(!feof(arquivo_metadata)) {
		campo_qnt++;
		campos.tipos = realloc(campos.tipos, campo_qnt * sizeof(char*));
		campos.nomes = realloc(campos.nomes, campo_qnt * sizeof(char*));
		campos.tam_bytes = realloc(campos.tam_bytes, campo_qnt * sizeof(int));
		
		if(parametros_campos(&campos.nomes[campo_qnt-1], arquivo_metadata)) {
		parametros_campos(&campos.tipos[campo_qnt-1], arquivo_metadata);
		campos.tam_bytes[campo_qnt-1] = tamanho(campos.tipos[campo_qnt-1]);
		offset += campos.tam_bytes[campo_qnt-1]; 
		} else {
			campo_qnt--;
		}
	}
	fclose(arquivo_metadata);
	free(nome_metadata);

	/* loop que lê os inputs até o fim do programa */
	operador = readline(stdin);
	while(strncmp("exit", operador, 4)) {
		if(!strncmp("insert", operador, 6)) {
			arquivo_registro = fopen(nome_registro, "ab");

			index_existe = 0;
			pos = 0;
			linhas = realloc(linhas, (linhas_qnt+1) * sizeof(Insercao));
			linhas[linhas_qnt].valores = malloc((campo_qnt+1) * sizeof(void*));

			index = realloc(index, (linhas_qnt+1) * sizeof(Struct_index));

			/* utilizando strtok separa a string de entrada em partes e prepara elas baseado nos tipos dos campos */
			buffer = strdup(strtok(operador, ","));
			insere_valor(&linhas[linhas_qnt], campos, &buffer[7], pos);

			fwrite(&linhas[linhas_qnt].valores[pos], campos.tam_bytes[pos], sizeof(char), arquivo_registro);

			index[linhas_qnt].chave = *(int*)&linhas[linhas_qnt].valores[pos];
			index[linhas_qnt].offset = linhas_qnt * offset;

			free(buffer);
			pos++;
			for(pos = 1; pos < campo_qnt; pos++) {
				buffer = strdup(strtok(NULL, ","));
				insere_valor(&linhas[linhas_qnt], campos, &buffer[1], pos);

				fwrite(&linhas[linhas_qnt].valores[pos], campos.tam_bytes[pos], sizeof(char), arquivo_registro);
				free(buffer);
			}
			fclose(arquivo_registro);
			linhas_qnt++;
		} else if(!strncmp("search", operador, 6)) { 
			if(!index_existe) {
			arquivo_index = fopen(nome_index, "wb");
			bubble_sort(index, linhas_qnt-1);
			for(int i = 0; i < linhas_qnt; i++) {
				fwrite(&index[i].chave, sizeof(int), 1, arquivo_index);
				fwrite(&index[i].offset, sizeof(int), 1, arquivo_index);
				}
			fclose(arquivo_index);
			index_existe = 1;
			}

			arquivo_registro = fopen(nome_registro, "rb");
			pos = busca_binaria(index, 0, linhas_qnt-1, atoi(&operador[7]));
			if(pos != -1) {
			fseek(arquivo_registro, index[pos].offset, SEEK_SET);
			
			for(int i = 0; i < campo_qnt; i++) imprime_valor(arquivo_registro, campos, i);
			printf("\n"); 
			}
		}
		free(operador);
		operador = readline(stdin);
	}
	free(operador);





	/* free e close nos arquivos */
	for(int i = 0; i < campo_qnt; i++) {
		free(campos.nomes[i]);
		free(campos.tipos[i]);
	}
	free(campos.tam_bytes);
	free(campos.nomes);
	free(campos.tipos);

	for(int i = 0; i < linhas_qnt; i++) {
		for(int j = 0; j < campo_qnt; j++) {
			/* free(linhas[i].valores[j]); */
		}
		free(linhas[i].valores);
	}
	free(linhas);
	free(index);

	free(nome_registro);
	free(nome_index);

	return 0;
}
