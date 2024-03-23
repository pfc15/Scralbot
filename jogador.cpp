#include <bits/stdc++.h>
using namespace std;

class Jogador
{
    public:
        char pecas[8];
        string nome;
        int pontos =0;
    
    Jogador(){
        cout << trocar_pecas() << endl;
    }

    int trocar_pecas(){
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        int random_value = std::rand();
        return random_value;
    }

    void add_pontos(int add){

    }
};


int main(){
    Jogador j;
    

}

