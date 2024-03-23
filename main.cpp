
#include <bits/stdc++.h>
#include <math.h>
using namespace std;


class Dicionario{
    public:
        // struct base da hash
        struct item {
            string palavra; //palavra chave
            bool palavra_completa; //se a palavra é completa e no dicionário
        };
        struct item *ht;
        long int M = pow(3, 12); //tamanho da hash
        int COLint = 10; //limite de colisões
    
    Dicionario(){
        // inicializando a hash
        ht = (item*) malloc(sizeof(item)*M);
        item n;
        n.palavra = string("*");
        n.palavra_completa = false;
        for (int i=0;i<M;i++){
            ht[i] = n;
        }

        //lendo o dicionario
        vector<string> palavras = {};
        int quant = ler_arquivo("dic.txt", palavras);
        int cont =0;
        //adiconando todos na hash
        for (string palavra_inteira:palavras){
            string palavra_partida = string("");
            for (char letra:palavra_inteira){
                palavra_partida += letra;
                n.palavra = palavra_partida;
                if (palavra_partida==palavra_inteira)
                    n.palavra_completa = true;
                else n.palavra_completa = false;
                cont += (add(n)+2)%2;
                cout << cont<< endl;
            }
            
        }
        
    };

    int add(item novo){
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

    int procura(string proc){
        int h = encode(proc);
        for (int c=0, i=h;c<COLint; i=(i+43)%M, c++){
            if (ht[i].palavra==proc) return i;
        }
        return -1;
    }

    bool isNull(item i){
        if (i.palavra == "*") return true;
        return false;
    }


    int ler_arquivo(const char* nome_arquivo, vector<string>& palavras){
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

    long int encode(string chave){
        long int h = 0;
        int n =1;
        for(char l:chave){
            h += l*pow(3, n);
            n++;
        }
        return h%M;
    };

};



int main(){
    auto start = std::chrono::steady_clock::now();
    Dicionario *dic = new Dicionario;
    cout << "palavra: " << dic->ht[dic->procura("aba")].palavra << endl;
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;

}