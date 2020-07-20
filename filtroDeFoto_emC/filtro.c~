#include<stdlib.h>
#include<stdio.h>
#include<string.h>

enum modos {
	Negativo = 1, PretoBranco =2};
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

/* muda o nome do arquivo original para o nome do arquivo novo */
char* mudar_nome(char* nome_original, int modo) {
	char* resultado;
	printf("nome %s\n", nome_original);
	if(modo == Negativo) {
		resultado = malloc((strlen(nome_original)+9) * sizeof(char));
		strcpy(resultado, nome_original);
		strchr(resultado, '.')[0] = '\0';
		strcat(resultado, "Negativo.bmp");
	} else {
		resultado = malloc((strlen(nome_original)+12) * sizeof(char));
		strcpy(resultado, nome_original);
		strchr(resultado, '.')[0] = '\0';
		strcat(resultado, "PretoBranco.bmp");
	}
	return resultado;
}

/* realiza o read no arq original e o write no arq novo */
void read_write_int(int* vetor, FILE* arquivo_original, FILE* arquivo_novo, char* print) {
	fread(vetor, sizeof(int), 1, arquivo_original);
	fwrite(vetor, sizeof(int), 1, arquivo_novo);
	if(print != NULL) printf("%s%d\n", print, *vetor);
}

/* mesma coisa que read_write_int mas para short int */
void read_write_short(short int* vetor, FILE* arquivo_original, FILE* arquivo_novo, char* print) {
	fread(vetor, sizeof(short int), 1, arquivo_original);
	fwrite(vetor, sizeof(short int), 1, arquivo_novo);
	if(print != NULL) printf("%s%hi\n", print, *vetor);
}

int main(int argc, char* argv[]) {
	/* Declaração de variaveis */
	FILE* arquivo_original;
	FILE* arquivo_novo;
	char* nome_original;
	char* nome_novo;
	char* buffer;
	int modo, tam_arquivo, camp_reservado, deslocamento;
	int tam_cabecalho, larg, alt, compressao, tam_imagem, res_horizontal, res_vertical, cores_imp, cores_usad;
	short num_planos;
	short bpp;

	/* entradas e abertura de arquivos */
	nome_original = readline(stdin);
	scanf("%d", &modo);

	arquivo_original = fopen(nome_original, "rb");

	/* checagem de erros */
	if(arquivo_original == NULL) {
		printf("Erro no arquivo\n");
		exit(101);
	}
	if(strcmp(strchr(nome_original, '.'), ".bmp")) {
		printf("Arquivo nao eh do formato BMP\n");
		exit(102);
	}

	buffer = malloc(3 * sizeof(char));
	fread(buffer, sizeof(char), 2, arquivo_original);
	buffer[2] = '\0';

	if(strcmp(buffer, "BM")) {
		printf("Arquivo nao eh do formato BMP\n");
		exit(103);
	}

	/* criacao do novo arquivo  */
	nome_novo = mudar_nome(nome_original, modo);
	arquivo_novo = fopen(nome_novo, "wb");

	/* leitura e impressão do cabeçalho */
	printf("CABECALHO:\n");

	/* Cabeçalho do arquivo */
	fwrite(buffer, sizeof(char), 2, arquivo_novo);
	printf("Iniciais: %s\n", buffer);
	free(buffer);

	read_write_int(&tam_arquivo, arquivo_original, arquivo_novo, "Tamanho do arquivo: ");
	read_write_int(&camp_reservado, arquivo_original, arquivo_novo, "Reservado: ");
	read_write_int(&deslocamento, arquivo_original, arquivo_novo, "Deslocamento, em bytes, para o inicio da area de dados: ");
	
	/* Cabeçalho do bitmap */
	read_write_int(&tam_cabecalho, arquivo_original, arquivo_novo, "Tamanho em bytes do segundo cabecalho: ");
	read_write_int(&larg, arquivo_original, arquivo_novo, NULL);
	read_write_int(&alt, arquivo_original, arquivo_novo, NULL);
	printf("Resolucao: %d x %d\n", larg, alt);
	read_write_short(&num_planos, arquivo_original, arquivo_novo, "Numero  de planos: ");
	read_write_short(&bpp, arquivo_original, arquivo_novo, "Bits por pixel: ");
	read_write_int(&compressao, arquivo_original, arquivo_novo, "Compressao usada: ");
	read_write_int(&tam_imagem, arquivo_original, arquivo_novo, "Tamanho imagem: ");
	read_write_int(&res_horizontal, arquivo_original, arquivo_novo, NULL);
	printf("Resolucao horizontal: %d pixel por metro\n", res_horizontal);
	read_write_int(&res_vertical, arquivo_original, arquivo_novo, NULL);
	printf("Resolucao Vertical: %d pixel por metro\n", res_vertical);
	read_write_int(&cores_usad, arquivo_original, arquivo_novo, "Numero de cores usadas: ");
	read_write_int(&cores_imp, arquivo_original, arquivo_novo, "Numero de cores importantes: ");
	



	fclose(arquivo_original);
	fclose(arquivo_novo);

	free(nome_original);
	free(nome_novo);
	return 0;
}
