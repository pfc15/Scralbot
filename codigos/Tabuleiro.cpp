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
        priority_queue<tuple<long int, string, pair<int, int>, int>> resultado_palavras;
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
        vector<char> linha_mortas;
        for (int i=0; i<17;i++) linha_mortas.push_back('/');
        tabuleiro_pecas.push_back(linha_mortas);
        for (int i=1; i<16;i++){
            vector<char> aux = {};
            tabuleiro_pecas.push_back(aux);
            tabuleiro_pecas.at(i).push_back('/');
            for (int e=1;e<16;e++){
                tabuleiro_pecas.at(i).push_back(' ');
            }
            tabuleiro_pecas.at(i).push_back('/');
        }
        tabuleiro_pecas.push_back(linha_mortas);
        cout << tabuleiro_pecas.at(15).size() << endl;

        mostrar_tabuleiro();
        cout << "criei o objeto!" << endl;
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
        cout << "  ";
        for (int i=0;i<15;i++){
            printf(" %02d ", i);
        }
        cout << endl;
        for (int e=1;e<16;e++){
            cout <<"  ";
            for (int i=0;i<(15);i++){
                cout << "+---";
            }
            cout << "+" <<endl;
            printf("%02d", cont);
            for (int i=1;i<tabuleiro_pecas.at(e).size()-1;i++){
                cout << "| " << tabuleiro_pecas.at(e).at(i) << " ";
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

    long int calcula_pontos(string palavra){
        long int pontos =0;
        for (char letra:palavra){
            pontos += valores_letras[letra];
        }
        return pontos;
    }

    int confere_movimento_legal(string palavra, pair<int, int> pos){
        char ancora = tabuleiro_pecas.at(pos.second).at(pos.first);
        vector<int> index_ancoras = {};
        int ancora_index = palavra.find(ancora);
        for (int i=0;i<palavra.size(); i++){
            if (palavra.at(i) == ancora){
                index_ancoras.push_back(i);
            }
        }
        if (ancora == ' ') return ancora_index;
        bool legal = true;
        for (int index:index_ancoras){
            int direcao = get_direcao(pos);
            if (direcao == -1) legal = false;
            int x = pos.first, y= pos.second;
            for (int i=index-1;i>=0;i--){
                if (direcao ==1){
                    y--;
                    if (tabuleiro_pecas.at(y-1).at(x) != ' ' || tabuleiro_pecas.at(y).at(x-1) != ' ' || tabuleiro_pecas.at(y).at(x+1) != ' '){
                        legal = false;
                        break;
                    }
                        
                } else if (direcao ==0){
                    x--;
                    if (tabuleiro_pecas.at(y).at(x-1) != ' ' || tabuleiro_pecas.at(y-1).at(x) != ' ' || tabuleiro_pecas.at(y+1).at(x) != ' '){
                        legal = false;
                        break;
                    }
                }
            }
            
            for (int i=ancora+1;i<palavra.size(),legal!=true;i++){
                if (direcao ==1){
                    y++;
                    if (tabuleiro_pecas.at(y+1).at(x) != ' ' || tabuleiro_pecas.at(y).at(x-1) != ' ' || tabuleiro_pecas.at(y).at(x+1) != ' '){
                        legal = false;
                        break;
                    }
                        
                } else if (direcao ==0){
                    x++;
                    if (tabuleiro_pecas.at(y).at(x+1) != ' ' || tabuleiro_pecas.at(y-1).at(x) != ' ' || tabuleiro_pecas.at(y+1).at(x) != ' '){
                        legal = false;
                        break;
                    }
                        
                }
            }
            if (legal)
                return index;
        }
        return -1;
}
        
    

    int dfs(int u, string caminho, vector<queue<item>> grafo, string pecas, pair<int, int> pos){
        
        // visitando o  nó
        caminho += grafo[u].front().letra;
        tentativas.push_back(caminho);
        if (dic.procura(caminho)>=0){
            int index_ancora = confere_movimento_legal(caminho, pos);
            tuple<long int, string, pair<int, int>, int> entrada = {calcula_pontos(caminho), caminho, pos, index_ancora};
            if  (index_ancora>=0|| tabuleiro_pecas.at(pos.second).at(pos.first)==' ')
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

    int busca_palavra(Jogador j, pair<int, int> pos){
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

    void movimento(){
        resultado_palavras = {};
        tentativas = {};
        pair<int, int> retorno;
        bool tabuleiro_vazio = true;
        printf("procurando por letras\n");
        // procurando por letras
        for (int x=1;x<tabuleiro_pecas.size()-1;x++){
            for (int y=1;y<tabuleiro_pecas.size()-1;y++){
                retorno = {x, y};
                if (analise_pos(retorno)){
                    busca_palavra(jogadores.at(vez),retorno);
                    tabuleiro_vazio = false;
                }
            }
        }
        if (tabuleiro_vazio){
            retorno = {8, 8};
            busca_palavra(jogadores.at(vez), retorno);
        }

        // colocando as peças no tabuleiro
        vector<int> index_pecas_troca = {};
        if (!resultado_palavras.empty()){
            tuple<long int, string, pair<int, int>, int> vizu = resultado_palavras.top();
            cout << "plavra: " << get<string>(vizu) << " pos: [" << get<pair<int, int>>(vizu).first << ", " << get<pair<int, int>>(vizu).second << "] ancora: " << get<int>(vizu) << endl;
            posicionar(resultado_palavras.top());
            for(char letra:get<string>(resultado_palavras.top())){
                int index = jogadores.at(vez).pecas.find(letra);
                if (index>=0)
                    index_pecas_troca.push_back(index);
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
        cout << "vez: " <<vez << endl;
    }

    int get_direcao(pair<int, int> pos){
        if (tabuleiro_pecas.at(pos.second).at((pos.first+1)%17)==' '&&tabuleiro_pecas.at(pos.second).at((pos.first-1)%17)==' '){
            return 0; // horizontal
        } else if (tabuleiro_pecas.at((pos.second+1)%17).at(pos.first)==' '&&tabuleiro_pecas.at((pos.second-1)%17).at(pos.first)==' '){
            return 1; // vertical
        }
        return -1;
    }

    void posicionar(tuple<long int, string, pair<int, int>, int> topo){
        
        pair<int, int> pos = get<pair<int, int>>(topo); 
        string palavra = get<string>(topo);
        int ancora = get<int>(topo);
        int x = pos.first;
        int y = pos.second;
        cout << "plavra: " << palavra << " pos: [" << pos.first << ", " << pos.second << "] ancora: " << ancora << endl;
        // definir direcao
        int direcao = get_direcao(pos);
        

        // parte antes da ancora
        int meio = ancora -1;
        if (ancora == -1){
            meio = palavra.size()/2;
            x++; 
        }
        
        for (int i=meio;i>=0;i--){
            if (direcao ==1){
                y--;
            } else if (direcao ==0){
                x--;
            }
            tabuleiro_pecas.at(y).at(x) = palavra.at(i);
            
        }
        x = pos.first;
        y = pos.second;

        meio = ancora+1;
        if (ancora ==-1){
            meio = (palavra.size()/2)+1;
        }
        // parte depois da ancora
        for (int i=meio;i<palavra.size();i++){
            if (direcao ==1){
                y++;
            } else if (direcao ==0){
                x++;
            }
            tabuleiro_pecas.at(y).at(x) = palavra.at(i);
        }
        mostrar_tabuleiro();
    }

    // anailise de se a posição é viável
    bool analise_pos(pair<int, int> pos){
        if (tabuleiro_pecas.at(pos.second).at(pos.first) != ' '){
            // verificando se é a ponta do tabuleiro
            if (tabuleiro_pecas.at(pos.second).at(pos.first) == '/'){
                return false;
            }
            // vendo se a peça esta cercada por outras peças
            int direcao = get_direcao(pos);
            if (direcao==-1){
                return false;
            }

            return true;
        }

        return false;
    }
};



int main(){
    vector<string> lista = {string("pedro"), string("pablo")};
    Jogo j = Jogo(lista);
    int i = 0;
    j.vez =0;
    while(i!=-1){
        auto start = std::chrono::high_resolution_clock::now();
        j.movimento();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tempo de processamento: " << duration.count() << " milliseconds" << std::endl;
        //while(!j.resultado_palavras.empty()){
        //    printf("palavra: %s; pontos: %d; posição: [%d, %d]\n", get<string>(j.resultado_palavras.top()).c_str(), get<int>(j.resultado_palavras.top()), get<pair<int, int>>(j.resultado_palavras.top()).first, get<pair<int, int>>(j.resultado_palavras.top()));
        //    j.resultado_palavras.pop();
        //}
        cout << "digite 1 para prox jogador jogar: " ;
        cin >> i;
    }
    
}