#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include<ctype.h>

#define READLINE_BUFFER 4096 // macro para a readline

// Struct para armazenar items da lista
typedef struct {
	char* nome;
	long numero;
} Item;

// Separa a string recebida em string e numero e coloca dentro da variavel Item, além de allocar espaço para string
void separarString(char* string, Item* resultado) {
	int i;
	for(i = 0; i<strlen(string); i++) {
		if(isdigit(string[i]) || (string[i] == '-' && isdigit(string[i+1]))) {
			string[i-1] = '\0'; // Quando encontra a parte numerica da entrada ele coloca um 0 no char anterior, separando em duas strings, como um char foi colocado logo atras da posição do i o strlen() diminui para o tamanho dele
		}
	}
		resultado->nome = (char*) malloc(1 + (int) strlen(string));
		resultado->nome = strcpy(resultado->nome, string);
		resultado->numero = atol(&string[i-1]);
}

/* Troca os valores de dois items */
void swapItems(Item* i1, Item* i2) {
	Item buffer = *i1;
	*i1 = *i2;
	*i2 = buffer;
}


/* Organiza a lista por Selection Sort */
void organizarLista(Item* resultado, int op, int tamLista) {
	if (op == 1) { // Ordem Alfabetica
		for(int i = 0; i<tamLista; i++) {
			for(int j = 1; j+i<tamLista; j++) {
				if(strcmp(resultado[i].nome, resultado[i+j].nome) > 0)	{ // Se o numero atual for menor troca de lugar, itera todos os numeros com todos os numeros na ordem da lista
					swapItems(&resultado[i+j], &resultado[i]);
				}
			}
		}
	}
	else { // Ordem númerica
		for(int i = 0; i<tamLista; i++) {
			for(int j = 1; j+i<tamLista; j++) {
				if(resultado[i].numero > resultado[i+j].numero)	{ // Se o numero atual for menor troca de lugar, itera todos os numeros com todos os numeros na ordem da lista
					swapItems(&resultado[i+j], &resultado[i]);
				}
			}
		}
	}
}

// readline com alterações para lidar com \r
char *readline(FILE *stream) { 
	char *string = 0;
	int pos = 0;

	if(feof(stream)) { // Retorna NULL caso seja end of the file
		return NULL;
	}

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
	/* declaração variaveis  */
	int op, tamLista = 0;
	char* buffer;
	Item* lista;

	/* Recebe o input da operação que vai ser feita e transforma em inteiro para evitar problemas com \n e \r */
	buffer = readline(stdin);
	op = atoi(buffer);

	lista = (Item*) malloc(sizeof(Item) * 4096); //Alloc inicial, depois do input se usa um realloc para o tamanho total

	/* While lê os inputs até o fim do arquivo */
	buffer = readline(stdin);
	while(buffer) {
		separarString(buffer, &lista[tamLista]);
		tamLista++;
		free(buffer);
		buffer = readline(stdin);
	} 
	lista = (Item*) realloc(lista, sizeof(Item) * tamLista);

	/* organiza a lista */
	organizarLista(lista, op, tamLista);

	/* Imprime a lista */
	for(int i = 0; i<tamLista; i++) {
		printf("%ld\t%s\n", lista[i].numero, lista[i].nome);
	}


	/* free das variaveis alocadas */
	for(int i = 0; i<tamLista; i++) {
		free(lista[i].nome);
	}
	free(lista);

	return 0;
}
