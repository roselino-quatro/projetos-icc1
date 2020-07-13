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

void parametros_campos(char** campo, FILE* arquivo_metadata) {
	char* buffer;
	buffer = readline(arquivo_metadata);
	*campo = strdup(ultima_palavra(buffer));
	free(buffer);
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

int main(int argc, char* argv[]) {
	/* Declaração de variaveis */
	Campos campos;
	char* nome_metadata;
	FILE* arquivo_metadata; 
	char* nome_registro;
	FILE* arquivo_registro; 
	char* nome_index;
	FILE* arquivo_index; 
	char* buffer;
	char* operador;
	int offset = 0, campo_qnt = 0;

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

	/* realiza a leitura dos tipos e nome dos campos */
	while(!feof(arquivo_metadata)) {
		campo_qnt++;
		campos.tipos = realloc(campos.tipos, campo_qnt * sizeof(char*));
		campos.nomes = realloc(campos.nomes, campo_qnt * sizeof(char*));
		campos.tam_bytes = realloc(campos.tam_bytes, campo_qnt * sizeof(int));
		
		parametros_campos(&campos.nomes[campo_qnt-1], arquivo_metadata);
		parametros_campos(&campos.tipos[campo_qnt-1], arquivo_metadata);
		campos.tam_bytes[campo_qnt-1] = tamanho(campos.tipos[campo_qnt-1]);
		offset += campos.tam_bytes[campo_qnt-1];
		printf("nome %s tipo %s tamanho %d\n", campos.nomes[campo_qnt-1], campos.tipos[campo_qnt-1], campos.tam_bytes[campo_qnt-1]);
	}

	/* loop que lê os inputs até o fim do programa */
	operador = malloc(7 * sizeof(char)); // O maximo que um comando tem de tamanho são 6 caracteres 7 incluindo o \0
	scanf("%s", operador);
	while(strcmp("exit", operador)) {
		printf("%s\n", operador);
		if(!strcmp("insert", operador)) {
			buffer = readline(stdin);
		} else if(!strcmp("search", operador)) { 
		}
		scanf("%s", operador);
	}

	/* free e close nos arquivos */
	for(int i = 0; i < campo_qnt; i++) {
		free(campos.nomes[i]);
		free(campos.tipos[i]);
	}
	free(campos.tam_bytes);
	free(campos.nomes);
	free(campos.tipos);


	return 0;
}
