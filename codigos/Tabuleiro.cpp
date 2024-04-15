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

struct bonus;
struct bonus {
    string tipo;
    int multiplicador;
};



class Jogo
{
    
    public:
        vector<Jogador> jogadores;
        int vez;
        vector<vector<char>> tabuleiro_pecas;
        vector<vector<bonus>> tabuleiro_bonus;
        Dicionario dic;
        //long int: pontos, string: palavra, pair: posição da ancora, int: index da ancora na palavra
        priority_queue<tuple<long int, string, pair<int, int>, int>> resultado_palavras; 
        vector<string> tentativas;
        map<char, int> valores_letras;
        int sem_jogadas = 0;
        // alfabeto é a string com a quantidade de peças que cada letra tem no jogo original. 14 A's, 3 B's etc
        string pecas_total = string("aaaaaaaaaaaaaabbbccccdddddeeeeeeeeeeeffgghhiiiiiiiiiijjkllllllmmmmmmnnnooooooooooopppppqrrrrrrsssssssssttttttuuuuuuuvvxyz");
        

    Jogo(vector<string>  nomes){
        // colocando o valor das letras
        valores_letras = dic.cria_valores();

        // inicializando jogadores
        srand(time(0));
        for (string nome:nomes){
            Jogador player = Jogador(nome, pecas_total);
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

        init_matriz_bonus();
    

        mostrar_tabuleiro();
    };

    void init_matriz_bonus(){
        bonus neutro = {"neutro", 1};
        vector<bonus> limpo = {};
        for (int y=0;y<17;y++){
            tabuleiro_bonus.push_back(limpo);
            for (int x=0; x<17;x++){
                tabuleiro_bonus.at(y).push_back(neutro);
            }
        }

        // posições dos bonus de letra dupla
        vector<pair<int, int>> posicoes = {{7,7}, {7,9}, {9, 9}, {9, 7}, {4, 8}, {3, 7}  
        ,{3, 9}, {1, 4}, {1, 12}, {8, 4}, {7, 3}, {9, 3}, {4, 1}, {12, 1}
        ,{12, 8}, {13, 7}, {13, 9}, {15, 4}, {15, 11}, {8, 12}, {7, 13}
        ,{9, 13}, {4, 15}, {12, 15}}; 
        bonus letra_dupla = {"letra", 2};
        for (pair<int, int> pos:posicoes){
            tabuleiro_bonus.at(pos.second).at(pos.first) = letra_dupla;
        }

        // posições dos bonus de letra tripla
        posicoes = {{6,6}, {6, 10}, {10, 6}, {10, 10}, {2, 6},      
        {2, 10}, {6, 2}, {10, 2}, {14, 6}, {14, 10}, {5, 14}, {10, 14}};
        bonus letra_tripla = {"letra", 3};
        for (pair<int, int> pos:posicoes){
            tabuleiro_bonus.at(pos.second).at(pos.first) = letra_tripla;
        }

        // posições dos bonus de palavra dupla
        posicoes = {{5, 5}, {5, 11}, {11, 5}, {11, 11}, {4, 4}
        ,{4, 12}, {12, 4}, {12, 12}, {3, 3}, {3, 13}, {13, 3}, {13, 13}
        ,{2, 2}, {2, 14}, {14, 2}, {14, 14}};
        bonus palavra_dupla = {"palavra", 2};
        for (pair<int, int> pos:posicoes){
            tabuleiro_bonus.at(pos.second).at(pos.first) = palavra_dupla;
        }

        // posições dos bonus de palavra tripla
        posicoes = {{1, 1}, {15, 15}, {1, 15}, {15, 1}, {1, 8}    
        ,{8, 1}, {15, 8}, {8, 15}};
        bonus palavra_tripla = {"palavra", 3};
        for (pair<int, int> pos:posicoes){
            tabuleiro_bonus.at(pos.second).at(pos.first) = palavra_tripla;
        }

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
        cout << "\033[2J\033[1;1H"; //limpa o terminal
        for (Jogador j: jogadores){
            cout <<"nome: " << j.nome << "; peças: [" << j.pecas << "]; pontos: " << j.ponto << endl;
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
                if (tabuleiro_bonus.at(e).at(i).tipo == "neutro"){
                    printf("| \x1B[33m%c\033[0m ", tabuleiro_pecas.at(e).at(i));
                } else if (tabuleiro_pecas.at(e).at(i) == ' '){
                    if (tabuleiro_bonus.at(e).at(i).tipo == "palavra"){
                        printf("| \x1B[31m*\033[0m ");
                    } else if(tabuleiro_bonus.at(e).at(i).tipo == "letra"){
                        printf("| \x1B[34m*\033[0m ");
                    }
                }else if (tabuleiro_pecas.at(e).at(i) != ' '){
                    if (tabuleiro_bonus.at(e).at(i).tipo == "palavra"){
                        printf("| \x1B[31m%c\033[0m ", tabuleiro_pecas.at(e).at(i));
                    } else if(tabuleiro_bonus.at(e).at(i).tipo == "letra"){
                        printf("| \x1B[34m%c\033[0m ", tabuleiro_pecas.at(e).at(i));
                    }
                }
                
                
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

    // função para calcular pontos que uma palavra faz
    long int calcula_pontos(string palavra, pair<int, int> pos, int index_ancora){
        long int pontos =0;
        int bonus_palavra = 1;
        int direcao = get_direcao(pos);
        int x = pos.first, y=pos.second;
        if (index_ancora == -1) index_ancora = palavra.size()/2;
        // parte antes da ancora
        for (int i=index_ancora;i>=0;i--){
            char letra = palavra.at(i);
            bonus b_atual = tabuleiro_bonus.at(y).at(x);
            if (b_atual.tipo == "palavra"){
                bonus_palavra *= b_atual.multiplicador;
                pontos += valores_letras[letra];
            } else{
                pontos += (valores_letras[letra]*b_atual.multiplicador);
            }
            if (direcao ==1){
                y--;

            } else if (direcao ==0){
                x--;
            }
        }
        x = pos.first; y= pos.second;
        // parte depois da ancora   
        for (int i=index_ancora+1;i<palavra.size();i++){
            if (direcao ==1){
                y++;
            } else if (direcao ==0){
                x++;
            }
            char letra = palavra.at(i);
            bonus b_atual = tabuleiro_bonus.at(y).at(x);
            if (b_atual.tipo == "palavra"){
                bonus_palavra *= b_atual.multiplicador;
                pontos += valores_letras[letra];
            } else{
                pontos += valores_letras[letra]*b_atual.multiplicador;
            }
        }
        return pontos*bonus_palavra;
    }

    // confere se o movimento é legal, depois da busca
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
            legal =true;
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
            x = pos.first; y= pos.second;
            
            for (int i=index+1;i<palavra.size();i++){
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
            if (legal){
                return index;
            }
                
        }
        return -1;
}
        
    

    int dfs(int u, string caminho, vector<queue<item>> grafo, string pecas, pair<int, int> pos){
        
        // visitando o  nó
        caminho += grafo[u].front().letra;
        tentativas.push_back(caminho);
        if (dic.procura(caminho)>=0){
            int index_ancora = confere_movimento_legal(caminho, pos);
            
            if  (index_ancora>=0|| tabuleiro_pecas.at(pos.second).at(pos.first)==' '){
                tuple<long int, string, pair<int, int>, int> entrada = {calcula_pontos(caminho, pos, index_ancora), caminho, pos, index_ancora};
                resultado_palavras.emplace(entrada);
            }
                
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

        if (resultado_palavras.empty()) return 0;
        string entrega = get<string>(resultado_palavras.top());
        pair< int, int> top_pos = get<pair<int, int>>(resultado_palavras.top());
        
        return 1;
    }

    void movimento(){
        resultado_palavras = {};
        tentativas = {};
        pair<int, int> retorno;
        bool tabuleiro_vazio = true;
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

            // trocando peças
            for(char letra:get<string>(resultado_palavras.top())){
                int index = jogadores.at(vez).pecas.find(letra);
                if (index>=0)
                    index_pecas_troca.push_back(index);
            }
            pecas_total = jogadores.at(vez).troca_peca(index_pecas_troca, pecas_total);

            jogadores.at(vez).ponto += get<long int>(resultado_palavras.top());
            sem_jogadas =0;
            vez = (vez+1)%jogadores.size();
            mostrar_tabuleiro();
        } else{
            // troca todas as pecas
            for(int i=0;i<jogadores.at(vez).pecas.size();i++){
                index_pecas_troca.push_back(i);
            }
            string coloca_dvolta = jogadores.at(vez).pecas;
            pecas_total = jogadores.at(vez).troca_peca(index_pecas_troca, pecas_total); 
            pecas_total += coloca_dvolta;
            sem_jogadas++;
            vez = (vez+1)%jogadores.size();
            mostrar_tabuleiro();
            cout << "sem  palavras válidas" << endl;
        }
        
    }

    int get_direcao(pair<int, int> pos){
        if (tabuleiro_pecas.at(pos.second).at((pos.first+1)%17)==' '&&tabuleiro_pecas.at(pos.second).at((pos.first-1)%17)==' '){
            return 0; // horizontal
        } else if (tabuleiro_pecas.at((pos.second+1)%17).at(pos.first)==' '&&tabuleiro_pecas.at((pos.second-1)%17).at(pos.first)==' '){
            return 1; // vertical
        }
        return -1;
    }

    // coloca a palavra no tabuleiro
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
    }

    // anailise de se a posição é viável antes da procura
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
    while(i!=-1) {
        auto start = std::chrono::high_resolution_clock::now();
        j.movimento();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tempo de procura da palavra: " << duration.count() << " milliseconds" << std::endl;
        if (j.sem_jogadas==3 || j.pecas_total == "") // jogo acaba
            break;
        cout << j.pecas_total << endl;
        //cin >> i;
    }
    cout << "Acabou o jogo!" << endl;
    
}