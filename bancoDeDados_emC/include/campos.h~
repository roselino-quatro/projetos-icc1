#ifndef _CAMPOS_H_
#define _CAMPOS_H_

typedef struct {
	char** tipos;
	char** nomes;
	int* tam_bytes;
} Campos;

typedef struct {
	int offset;
	int chave;
} Struct_index;

int parametros_campos(char**, FILE*);
int tamanho(char*);
void* insere_valor(void**, Campos, const char*, int);
int tamanho(char*);
void* insere_valor(void**, Campos, const char*, int);
void imprime_valor(FILE*, Campos, int);
void trocar(Struct_index*, Struct_index*);
void bubble_sort(Struct_index*, int);
int busca_binaria(const Struct_index, int, int, int);

#endif
