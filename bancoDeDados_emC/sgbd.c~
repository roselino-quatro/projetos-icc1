#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<util_strings.h>
#include<campos.h>

int main(int argc, char* argv[]) {
	/* Declaração de variaveis */
	Campos campos;
	Struct_index* index;
	index = NULL;
	void* valor;
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

			index = realloc(index, (linhas_qnt+1) * sizeof(Struct_index));

			/* utilizando strtok separa a string de entrada em partes e prepara elas baseado nos tipos dos campos */
			buffer = strdup(strtok(operador, ","));
			valor = insere_valor(&valor, campos, &buffer[7], pos);

			fwrite(valor, campos.tam_bytes[pos], sizeof(char), arquivo_registro);

			index[linhas_qnt].chave = *(int*)valor;
			index[linhas_qnt].offset = linhas_qnt * offset;

			free(buffer);
			free(valor);
			pos++;
			for(pos = 1; pos < campo_qnt; pos++) {
				buffer = strdup(strtok(NULL, ","));
				valor = insere_valor(&valor, campos, &buffer[1], pos);

				fwrite(valor, campos.tam_bytes[pos], sizeof(char), arquivo_registro);
				free(buffer);
				free(valor);
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

	free(index);

	free(nome_registro);
	free(nome_index);

	return 0;
}
