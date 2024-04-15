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

    Jogador(const string nome_, string pecas_total);
    string troca_peca(vector<int> troca, string pecas_total);
    int sortear_peca(string pecas_total);
    void add_pontos(int add);
};


#endif