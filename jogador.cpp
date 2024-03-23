#include <bits/stdc++.h>
using namespace std;

class Jogador
{
    public:
        char pecas[8];
        string nome;
        int ponto =0;
    
    Jogador(const string nome_){
        std::srand(std::time(nullptr)+2);
        string a = string("");
        for (int i =0; i<8; i++){
            pecas[i] = tirar_peca();
        }
        nome = nome_;
    }

    void troca_peca(vector<int> troca){
        for (int p:troca){
            pecas[p] = tirar_peca();
        }
    }

    char tirar_peca(){
        string alfabeto = string("aaaaaaaaaaaaaabbbccccdddddeeeeeeeeeeeffgghhiiiiiiiiiijjkllllllmmmmmmnnnooooooooooopppppqrrrrrrsssssssssttttttuuuuuuuvvxyz");
        int random_value = rand()%120;
        cout << random_value << endl;

        return alfabeto.at(random_value);
    }

    void add_pontos(int add){
        ponto += add;
    }
};


int main(){
    Jogador j = Jogador("pedro");

}

