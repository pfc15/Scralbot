# include "Jogador.h"
using namespace std;


Jogador::Jogador(const string nome_){
    std::srand(std::time(nullptr)+2);
    for (int i =0; i<8; i++){
        pecas.push_back(sortear_peca());
    }
    pecas[8] = EOF;
    nome = nome_;
}

void Jogador::troca_peca(vector<int> troca){
        for (int p:troca){
            pecas[p] = sortear_peca();
        }
    }

char Jogador::sortear_peca(){
        string alfabeto = string("aaaaaaaaaaaaaabbbccccdddddeeeeeeeeeeeffgghhiiiiiiiiiijjkllllllmmmmmmnnnooooooooooopppppqrrrrrrsssssssssttttttuuuuuuuvvxyz");
        int random_value = rand()%120;
        cout << random_value << endl;
        return alfabeto.at(random_value);
    }

void Jogador::add_pontos(int add){
        ponto += add;
    }



