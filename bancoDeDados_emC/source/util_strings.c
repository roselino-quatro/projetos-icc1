#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<util_strings.h>

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
