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
        // alfabeto é a string com a quantidade de peças que cada letra tem no jogo original. 14 A's, 3 B's etc
        string alfabeto = string("aaaaaaaaaaaaaabbbccccdddddeeeeeeeeeeeffgghhiiiiiiiiiijjkllllllmmmmmmnnnooooooooooopppppqrrrrrrsssssssssttttttuuuuuuuvvxyz");
        int random_value = rand()%alfabeto.size();
        return alfabeto.at(random_value);
    }

void Jogador::add_pontos(int add){
        ponto += add;
    }
