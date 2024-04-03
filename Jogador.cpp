# include "Jogador.h"
using namespace std;


Jogador::Jogador(const string nome_){
    for (int i =0; i<7; i++){
        pecas.push_back(sortear_peca());
    }
    pecas[7] = EOF;
    nome = nome_;
}

void Jogador::troca_peca(vector<int> troca){
        for (int p:troca){
            char novo = sortear_peca();
            pecas[p] = novo;
        }
    }

char Jogador::sortear_peca(){
        string alfabeto = string("aaaaaaaaaaaaaabbbccccdddddeeeeeeeeeeeffgghhiiiiiiiiiijjkllllllmmmmmmnnnooooooooooopppppqrrrrrrsssssssssttttttuuuuuuuvvxyz");
        int random_value = rand()%120;
        return alfabeto.at(random_value);
    }

void Jogador::add_pontos(int add){
        ponto += add;
    }
