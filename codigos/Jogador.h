#ifndef JOGADOR_H
#define JOGADOR_H
#include <bits/stdc++.h>
using namespace std;

class Jogador
{
public:
    string pecas;
    string nome;
    int ponto =0;

    Jogador(const string nome_);
    void troca_peca(vector<int> troca);
    char sortear_peca();
    void add_pontos(int add);
};


#endif