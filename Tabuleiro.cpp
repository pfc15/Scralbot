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
        priority_queue<tuple<int, string, pair<int, int>>> resultado_palavras;
        vector<string> tentativas;
        map<char, int> valores_letras;
        

    Jogo(vector<string>  nomes){
        // colocando o valor das letras
        valores_letras = dic.cria_valores();

        // inicializando jogadores
        srand(time(0));
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

    int dfs(int u, string caminho, vector<queue<item>> grafo, string pecas, pair<int, int> pos){
        
        // visitando o  nó
        caminho += grafo[u].front().letra;
        tentativas.push_back(caminho);
        if (dic.procura(caminho)>=0){
            tuple<int, string, pair<int, int>> entrada = {calcula_pontos(caminho), caminho, pos};
            if (caminho.find(tabuleiro_pecas.at(pos.second).at(pos.first))!=string::npos || tabuleiro_pecas.at(pos.second).at(pos.first)==' ')
                resultado_palavras.emplace(entrada);
        }

        // pegandoa as arestas
        queue<item> fila = grafo[u];
        fila.pop();
        int index;
        
        // enfilerando os novos nós a visitar
        while(!fila.empty()){
            item n = fila.front();
            fila.pop();
            string aux_s = caminho +n.letra;
            if (dic.confere_aresta(aux_s)){
                if (pecas.find(n.letra)!=string::npos && find(tentativas.begin(), tentativas.end(), aux_s)==tentativas.end()){
                    string aux = pecas;
                    aux.erase(pecas.find(n.letra), 1);
                    dfs(n.pos_grafo,caminho, grafo, aux, pos);
                }
            }
        }
        return tentativas.size();
    }

    int movimento(Jogador j, pair<int, int> pos){
        string pecas = j.pecas;
        char ancora = tabuleiro_pecas.at(pos.first).at(pos.second);
        if (ancora != ' '){
            pecas += ancora;
        }
        vector<queue<item>>  grafo = cria_grafo(pecas);

        int tentaivas_quant =0;
        tentativas = {};
        for (int i=0;i<8;i++){
            string aux = pecas;
            aux.erase(i,1);
            tentaivas_quant += dfs(i,string(""), grafo, aux, pos);
        }
        cout << "dfs completa! " << tentaivas_quant << " tentativas" << endl;
        if (resultado_palavras.empty()) return 0;
        string entrega = get<string>(resultado_palavras.top());
        cout << "1palavra: " << entrega << " topo: " << get<string>(resultado_palavras.top()) << endl;
        
        
        return 1;
    }

    void escolha_ancora(){
        resultado_palavras = {};
        tentativas = {};
        pair<int, int> retorno;
        bool tabuleiro_vazio = true;
        for (int x=0;x<tabuleiro_pecas.size();x++){
            for (int y=0;y<tabuleiro_pecas.size();y++){
                if (tabuleiro_pecas.at(y).at(x) != ' '){
                    retorno = {x, y};
                    movimento(jogadores.at(vez),retorno);
                    tabuleiro_vazio = false;
                }
            }
        }
        if (tabuleiro_vazio){
            retorno = {7, 7};
            movimento(jogadores.at(vez), retorno);
        }
        vector<int> index_pecas_troca = {};
        if (!resultado_palavras.empty()){
            tuple<int, string, pair<int, int>> vizu = resultado_palavras.top();
            cout << "plavra: " << get<string>(vizu) << " pos: [" << get<pair<int, int>>(vizu).first << ", " << get<pair<int, int>>(vizu).second << "] ancora: " << get<int>(vizu) << endl;
            posicionar(resultado_palavras.top());
            for(char letra:get<string>(resultado_palavras.top())){
                index_pecas_troca.push_back(jogadores.at(vez).pecas.find(letra));
            }
            jogadores.at(vez).troca_peca(index_pecas_troca);
        } else{
            for(int i=0;i<jogadores.at(vez).pecas.size();i++){
                index_pecas_troca.push_back(i);
            }
            jogadores.at(vez).troca_peca(index_pecas_troca);
            cout << "sem  palavras válidas" << endl; 
        }
        vez = (vez+1)%jogadores.size();
    }

    void posicionar(tuple<int, string, pair<int, int>> topo){
        cout <<"entrei em posicionar!" << endl;
        
        pair<int, int> pos = get<pair<int, int>>(topo); 
        string palavra = get<string>(topo);
        int ancora = palavra.find(tabuleiro_pecas.at(pos.second).at(pos.first));
        int x = pos.first;
        int y = pos.second;
        cout << "plavra: " << palavra << "pos: [" << pos.first << ", " << pos.second << "] ancora: " << ancora << endl;
        // definir direcao
        int direcao;
        if (tabuleiro_pecas.at(pos.second).at((pos.first+1)%15)==' '&&tabuleiro_pecas.at(pos.second).at((pos.first-1)%15)==' '){
            direcao =0;
        } else if (tabuleiro_pecas.at((pos.second+1)%15).at(pos.first)==' '&&tabuleiro_pecas.at((pos.second-1)%15).at(pos.first)==' '){
            direcao=1;
        }

        // parte antes da ancora
        for (int i=ancora-1;i>=0;i--){
            if (direcao ==1){
                y--;
            } else if (direcao ==0){
                x--;
            }
            tabuleiro_pecas.at(y).at(x) = palavra.at(i);
        }
        x = pos.first;
        y = pos.second;

        // parte depois da ancora
        for (int i=ancora+1;i<palavra.size();i++){
            if (direcao ==1){
                y++;
            } else if (direcao ==0){
                x++;
            }
            tabuleiro_pecas.at(y).at(x) = palavra.at(i);
        }
    }
};


int main(){
    vector<string> lista = {string("pedro"), string("pablo")};
    Jogo j = Jogo(lista);
    int i = 0;
    j.vez =0;
    while(i!=-1){
        auto start = std::chrono::high_resolution_clock::now();
        j.escolha_ancora();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tempo de processamento: " << duration.count() << " milliseconds" << std::endl;
        while(!j.resultado_palavras.empty()){
            printf("palavra: %s; pontos: %d; posição: [%d, %d]\n", get<string>(j.resultado_palavras.top()).c_str(), get<int>(j.resultado_palavras.top()), get<pair<int, int>>(j.resultado_palavras.top()).first, get<pair<int, int>>(j.resultado_palavras.top()));
            j.resultado_palavras.pop();
        }
        j.mostrar_tabuleiro();
        cout << "digite 1 para prox jogador jogar: " ;
        cin >> i;
        j.vez = (j.vez+1)%j.jogadores.size();
    }
    
    
}