#include <bits/stdc++.h>
#include "Jogador.h"
#include "Dicionario.h"
# include <algorithm>
using namespace std;

struct item;
struct item {
            char letra;
            int pos_palavra;
            int pos_grafo;
};


class Jogo
{
    
    public:
        vector<Jogador> jogadores;
        int vez;
        vector<vector<char>> tabuleiro_pecas;
        vector<vector<int>> tabuleiro_bonus;
        Dicionario dic;
        priority_queue<string> retorno;
        vector<string> tentativas;
        

    Jogo(vector<string>  nomes){
        std::srand(std::time(nullptr));
        for (string nome:nomes){
            Jogador player = Jogador(nome);
            jogadores.push_back(player);
            cout << "nome: " <<player.nome << "; pecas: [" << player.pecas << "]" << endl; 
        }

        // init da matiz
        for (int i=0; i<15;i++){
            vector<char> aux = {};
            tabuleiro_pecas.push_back(aux);
            for (int e=0;e<15;e++){
                tabuleiro_pecas.at(i).push_back(' ');
            }
        }
        mostrar_tabuleiro();

        
        
    };

    vector<queue<item>> cria_grafo(string pecas){

        vector<queue<item>> grafo;
        queue<item> fila_item;
        for (int voltas =0;voltas<pecas.size();voltas++){
            for (int i=0; i<pecas.size();i++){
                fila_item = {};
                item n_item;
                n_item.letra = pecas[i];
                n_item.pos_palavra = i;
                n_item.pos_grafo = i+(voltas*pecas.size());
                fila_item.emplace(n_item);
                for (int e=0;e<pecas.size();e++){
                    if (voltas!= pecas.size()-1 && e!=i){
                        n_item.letra = pecas[e];
                        n_item.pos_palavra = i+1;
                        n_item.pos_grafo = e+((voltas+1)*pecas.size());
                        fila_item.emplace(n_item);
                    }
                }
                grafo.push_back(fila_item);
            }
        }
        return grafo;
    };


    void mostrar_tabuleiro(){
        cout << "\033[2J\033[1;1H";
        for (Jogador j: jogadores){
            cout <<"nome: " << j.nome << "peças: [" << j.pecas << "]" << endl;
        }
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

    int dfs(int u, string caminho, vector<queue<item>> grafo, string pecas){
        caminho += grafo[u].front().letra;
        tentativas.push_back(caminho);
        if (dic.procura(caminho)>=0){
            retorno.emplace(caminho);
        }
        
        queue<item> fila = grafo[u];
        fila.pop();
        int index;
        
        while(!fila.empty()){
            item n = fila.front();
            fila.pop();
            string aux_s = caminho +n.letra;
            if (pecas.find(n.letra)!=string::npos && find(tentativas.begin(), tentativas.end(), aux_s)==tentativas.end()){
                string aux = pecas;
                aux.erase(pecas.find(n.letra), 1);
                dfs(n.pos_grafo,caminho, grafo, aux);
            }
            
        }
        return 1;

    }

    void movimento(Jogador j){
        string pecas = jogadores.at(0).pecas;
        pecas += 'a';
        vector<queue<item>>  grafo = cria_grafo(pecas);

        retorno = {};

        for (int i=0;i<8;i++){
            string aux = pecas;
            aux.erase(i,1);
            dfs(i,string(""), grafo, aux);
        }
        cout << "dfs completa!" << endl;
        pair<int, int> pos = {7, 6};
        posicionar(retorno.top(), pos, 0);
        
    }

    void posicionar(string palavra, pair<int, int> pos, int direcao){
        for (char letra:palavra){
            if (direcao ==0){
                tabuleiro_pecas.at(pos.first).at(pos.second) = letra;
                pos.second++;
            }
            
        }
    }

};


int main(){
    vector<string> lista = {string("pedro"), string("pablo")};
    Jogo j = Jogo(lista);
    j.movimento(j.jogadores.at(0));
    j.mostrar_tabuleiro();
}