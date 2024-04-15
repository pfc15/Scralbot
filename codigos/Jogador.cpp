# include "Jogador.h"
using namespace std;


Jogador::Jogador(const string nome_, string pecas_total){
    for (int i =0; i<7; i++){
        int novo = sortear_peca(pecas_total);
        pecas.push_back(pecas_total.at(novo));
        pecas_total.erase(pecas_total.begin()+novo);
    }
    pecas[7] = EOF;
    nome = nome_;
}

string Jogador::troca_peca(vector<int> troca, string pecas_total){

        for (int p:troca){
            int novo = sortear_peca(pecas_total);
            pecas[p] = pecas_total.at(novo);
            pecas_total.erase(pecas_total.begin()+novo);
            if (pecas_total == "") break;
        }
        return pecas_total;
    }

int Jogador::sortear_peca(string pecas_total){

        int random_value = rand()%pecas_total.size();
        return random_value;
    }

void Jogador::add_pontos(int add){
        ponto += add;
    }
