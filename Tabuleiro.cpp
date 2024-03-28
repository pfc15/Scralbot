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
        vector<bool> visitados;
        priority_queue<string> retorno;
        

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

        // fazer ação do jogador 0
        string aux = jogadores.at(0).pecas;
        aux += 'a';
        int cont =0;
        vector<queue<item>>  grafo = cria_grafo(aux);
        for (queue<item> fila:grafo){
            item n_item = fila.front();
            fila.pop();
            printf("cabeça da fila: %c; index: %d", n_item.letra, n_item.pos_grafo);
            cout <<endl;
            while (!fila.empty()){
                item n_item = fila.front();
                fila.pop();
                printf("aresta: %c; index: %d", n_item.letra, n_item.pos_grafo);
                cout <<endl;
            }

        }

        retorno = {};
        visitados = {};
        for (int i=0;i<(jogadores.at(0).pecas.size()+1)*(jogadores.at(0).pecas.size()+1);i++){
            visitados.push_back(false);
        }
        dfs(0,string(""), grafo);
        cout << retorno.top() << endl;
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
                        n_item.pos_grafo = i+((voltas+1)*pecas.size());
                        fila_item.emplace(n_item);
                    }
                }
                grafo.push_back(fila_item);
            }
        }
        return grafo;
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

    int dfs(int u, string caminho, vector<queue<item>> grafo){
        if (visitados[u]){
            return 0;
        }
        caminho += grafo[u].front().letra;
        if (dic.procura(caminho)>=0){
            retorno.emplace(caminho);
        }

        visitados[u] = true;
        queue<item> fila = grafo[u];
        fila.pop();
        int index;
        while(!fila.empty()){
            item n = fila.front();
            fila.pop();
            dfs(n.pos_grafo,caminho, grafo);
        }
        return 1;

    }

};


int main(){
    vector<string> lista = {string("pedro"), string("pablo")};
    Jogo j = Jogo(lista);

}