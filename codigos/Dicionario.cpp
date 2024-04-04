
#include "Dicionario.h"
using namespace std;


Dicionario::Dicionario(){
    // inicializando a hash
    ht = (item*) malloc(sizeof(item)*M);
    item n;
    n.palavra = string("*");
    n.palavra_completa = false;
    for (int i=0;i<M;i++){
        ht[i] = n;
    }

    //lendo o dicionario
    palavras = {};
    int quant = ler_arquivo("../dic.txt", palavras);
    int cont =0;
    //adiconando todos na hash
    for (string p:palavras){
        n.palavra = p;
        n.palavra_completa = true;
        cont += (add(n)+3)%2;
    }
};

int Dicionario::add(item novo)const{
        int c=0;
        long int h = encode(novo.palavra);
        int f = procura(novo.palavra);
        if (f>=0) return -1;
        while(!isNull(ht[h])&&c<COLint){
            h =((h+43)%M);
            c++;
        }
        if (c>COLint){
            return -1;
        }
        ht[h] = novo;
        return 1;
    }

int Dicionario::procura(string proc)const{
        int h = encode(proc);
        for (int c=0, i=h;c<COLint; i=(i+43)%M, c++){
            if (ht[i].palavra==proc) return i;
        }
        return -1;
    }

bool Dicionario::isNull(item i)const{
        if (i.palavra == "*") return true;
        return false;
    }

int Dicionario::ler_arquivo(const char* nome_arquivo, vector<string>& palavras)const{
        std::ifstream file(nome_arquivo);
        std::string word;
        int count = 0;
        if (file.is_open()) {
            while (file >> word) {
                palavras.push_back(word);
                count++;
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << nome_arquivo << endl;
        }
        return count;
    };

long int Dicionario::encode(string chave)const{
        long int h = 0;
        int n =1;
        for(char l:chave){
            h += l*pow(3, n);
            n++;
        }
        return h%M;
    };

bool Dicionario::confere_aresta(string p){
    int comeco = 0; int final = palavras.size();
    int posicao;
    while (posicao<palavras.size() && comeco<=final){
        posicao = (comeco +final)/2;
        if (palavras.at(posicao).substr(0, p.size())==p){
            return true;
        }
        if (palavras.at(posicao)>p){
            final = posicao-1;
        } else if (palavras.at(posicao)<p){
            comeco = posicao+1;
        }
    }
    return false;
};

map<char, int> Dicionario::cria_valores(){
    map<char, int> valores;
    valores['a'] = 1;
    valores['e'] = 1;
    valores['i'] = 1;
    valores['o'] = 1;
    valores['s'] = 1;
    valores['u'] = 1;
    valores['m'] = 1;
    valores['r'] = 1;
    valores['t'] = 1;
    valores['d'] = 2; 
    valores['l'] = 2; 
    valores['c'] = 2; 
    valores['p'] = 2; 
    valores['f'] = 4; 
    valores['g'] = 4; 
    valores['h'] = 4; 
    valores['v'] = 4; 
    valores['j'] = 5;
    valores['q'] = 6;
    valores['x'] = 8;
    valores['z'] = 8;
    valores['n'] = 3;
    valores['b'] = 3;
    return valores;
};




