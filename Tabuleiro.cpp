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
        priority_queue<pair<int, string>> resultado_palavras;
        vector<string> tentativas;
        map<char, int> valores_letras;
        

    Jogo(vector<string>  nomes){
        // colocando o valor das letras
        valores_letras = dic.cria_valores();

        // inicializando jogadores
        std::srand(std::time(nullptr));
        for (string nome:nomes){
            Jogador player = Jogador(nome);
            jogadores.push_back(player);
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
        //cout << "\033[2J\033[1;1H"; //limpa o terminal
        for (Jogador j: jogadores){
            cout <<"nome: " << j.nome << "; peças: [" << j.pecas << "]" << endl;
        }
        int cont =0;
        int l = 0;
        cout << "  ";
        for (int i=0;i<15;i++){
            printf(" %02d ", l);
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

    int calcula_pontos(string palavra){
        int pontos =0;
        for (char letra:palavra){
            pontos += valores_letras[letra];
        }
        return pontos;
    }

    int dfs(int u, string caminho, vector<queue<item>> grafo, string pecas){
        
        // visitando o  nó
        caminho += grafo[u].front().letra;
        tentativas.push_back(caminho);
        if (dic.procura(caminho)>=0){
            pair<int, string> entrada = {calcula_pontos(caminho), caminho};
            resultado_palavras.emplace(entrada);
        }

        queue<item> fila = grafo[u];
        fila.pop();
        int index;
        
        while(!fila.empty()){
            item n = fila.front();
            fila.pop();
            string aux_s = caminho +n.letra;
            if (dic.confere_aresta(aux_s)){
                if (pecas.find(n.letra)!=string::npos && find(tentativas.begin(), tentativas.end(), aux_s)==tentativas.end()){
                    string aux = pecas;
                    aux.erase(pecas.find(n.letra), 1);
                    dfs(n.pos_grafo,caminho, grafo, aux);
                }
            }
                
            
        }
        return tentativas.size();
    }

    int movimento(Jogador j){
        string pecas = j.pecas;
        pair<int, int> pos = escolha_ancora();
        char ancora = tabuleiro_pecas.at(pos.first).at(pos.second);
        if (ancora != ' '){
            pecas += ancora;
        }
        vector<queue<item>>  grafo = cria_grafo(pecas);

        resultado_palavras = {};
        int tentaivas_quant =0;
        for (int i=0;i<8;i++){
            string aux = pecas;
            aux.erase(i,1);
            tentaivas_quant += dfs(i,string(""), grafo, aux);
        }
        cout << "dfs completa! " << tentaivas_quant << " tentativas" << endl;
        if (resultado_palavras.empty()) return 0;
        string entrega = resultado_palavras.top().second;
        cout << "1palavra: " << entrega << " topo: " << resultado_palavras.top().second << endl;
        int direcao;
        if (tabuleiro_pecas.at(pos.second).at((pos.first+1)%15)==' '&&tabuleiro_pecas.at(pos.second).at((pos.first-1)%15)==' '){
            direcao =0;
        } else {
            direcao=1;
        }

        int x = pos.first;
        int y = pos.second;
        for (int i=0;i<entrega.size();i++){
            tabuleiro_pecas.at(y).at(x) = entrega.at(i);
            if (direcao ==1){
                y++;
            } else if (direcao ==0){
                x++;
            }
        }
        return 1;
        
    }

    pair<int, int> escolha_ancora(){
        pair<int, int> retorno; 
        for (int x=0;x<tabuleiro_pecas.size();x++){
            for (int y=0;y<tabuleiro_pecas.size();y++){
                if (tabuleiro_pecas.at(y).at(x) == 'a'|| tabuleiro_pecas.at(y).at(x) == 'e' || tabuleiro_pecas.at(y).at(x) == 'i' || tabuleiro_pecas.at(y).at(x) == 'o' || tabuleiro_pecas.at(y).at(x) == 'u'){
                    retorno = {x, y};
                    return retorno;
                }
            }
        }
        retorno = {7, 6};
        return retorno;
    }

    void posicionar(pair<int, int> pos, int direcao){
        int cont =0; 
        cout << cont << "ola:0 " << resultado_palavras.top().second << endl;
        for (char letra:resultado_palavras.top().second){
            
            cont ++;
            tabuleiro_pecas.at(pos.second).at(pos.first) = letra;
            if (direcao ==1){
                pos.second++;
            } else if (direcao ==0){
                pos.first++;
            }
        }
    }




};


int main(){
    vector<string> lista = {string("pedro"), string("pablo")};
    Jogo j = Jogo(lista);
    auto start = std::chrono::high_resolution_clock::now();
    j.movimento(j.jogadores.at(0));
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tempo de processamento: " << duration.count() << " milliseconds" << std::endl;
    while(!j.resultado_palavras.empty()){
        printf("palavra: %s; pontos: %d\n", j.resultado_palavras.top().second.c_str(), j.resultado_palavras.top().first);
        j.resultado_palavras.pop();
    }

    j.mostrar_tabuleiro();
    int i;
    cout << "digite 1 para prox jogador jogar: " ;
    cin >> i;
    start = std::chrono::high_resolution_clock::now();
    cout << j.movimento(j.jogadores.at(1)) << endl;
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tempo de processamento: " << duration.count() << " milliseconds" << std::endl;
    j.mostrar_tabuleiro();
}