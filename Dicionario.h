#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <bits/stdc++.h>
#include <math.h>
using namespace std;

class Dicionario
{
    public: 
    // struct base da hash
    struct item {
        string palavra; //palavra chave
        bool palavra_completa; //se a palavra é completa e no dicionário
    };
    struct item *ht;
    long int M = pow(3, 12); //tamanho da hash
    int COLint = 10; //limite de colisões

    Dicionario();

    int add(item novo)const;

    int procura(string proc) const;

    bool isNull(item i) const;

    int ler_arquivo(const char* nome_arquivo, vector<string>& palavras) const;

    long int encode(string) const;

    bool confere_aresta(char a, char b, int index);

};

#endif