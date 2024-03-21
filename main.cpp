
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <iostream>
using namespace std;

int ler_arquivo(const char* nome_arquivo, char*** array_palavras){
    FILE *arquivo;
    char*linha = NULL;
    size_t len = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL){
        return -1;
    }
    int cont =0;
    while ((getline(&linha,&len,arquivo))!= -1){
        printf("%d, %s",cont, linha);
        cont++;
        
        //strcpy();
    }

    fclose(arquivo);
    if (linha){
        free(linha);
    }

    return 0;
}

int main(){
    char ** array_palavras = (char**) malloc(sizeof(char*)*100);
    ler_arquivo("br-sem-acentos.txt", &array_palavras);
    free(array_palavras);
}