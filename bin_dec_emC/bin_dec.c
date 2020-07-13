#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

int main(int argc, char *argv[]) {
// Declaração das variaveis, ponteiro para armazenar o número em binário e int para armazenar resultado e tamanho da string pega no scanf
    char* bin;
    bin =calloc(31, sizeof(char));
    int dec = 0, str_len;

// scanf e strlen() para realizar a conversão sabendo o tamanho do número binário
    scanf("%s", bin);
    str_len = strlen(bin);
// for para iterar sobre todos os digitos do num bin, (bin[i]-48) evita ter que verificar se é um "0" ou "1", já nullificando a conta no caso do "0"
    for(int i = 0; i < str_len; i++) {
        dec += (bin[i]-48) * pow(2,str_len-i-1);
    }
// printf e free() do ponteiro
    printf("%d", dec);
    free(bin);
}
