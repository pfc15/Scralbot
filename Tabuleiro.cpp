#include <bits/stdc++.h>
//#include "Jogador.h"
//#include "Dicionario.h"
using namespace std;

class Jogo
{
    public:
        //vector<Jogador> jogadores;
        int vez;
        vector<vector<char>> tabuleiro_pecas;
        vector<vector<int>> tabuleiro_bonus;
        //Dicionario dic;

    Jogo(){
        for (int i=0; i<15;i++){
            vector<char> aux = {};
            tabuleiro_pecas.push_back(aux);
            for (int e=0;e<15;e++){
                tabuleiro_pecas.at(i).push_back(' ');
            }
        }
        mostrar_tabuleiro();
    };

    void mostrar_tabuleiro(){
        cout << tabuleiro_pecas.size() <<endl;
        int cont =0;
        char l = 'a';
        cout << "  ";
        for (int i=0;i<15;i++){
            cout << "  " << l << " ";
            l++;
        }
        cout << endl;
        for (vector<char> linha:tabuleiro_pecas){
            cout <<"  ";
            for (int i=0;i<(15);i++){
                cout << "+---";
            }
            cout << "+" <<endl;
            printf("%02d", cont);
            for (char letra: linha){
                cout << "| " << letra << " ";
            }
            cout << "|" << endl;
            cont++;
        }
        cout << "  ";
        for (int i=0;i<(15);i++){
            cout << "+---";
        }
        cout << "+" <<endl;
    }

};


int main(){
    Jogo j;

}