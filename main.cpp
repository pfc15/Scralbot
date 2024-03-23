
#include <bits/stdc++.h>
using namespace std;


class Dicionario{
    public:
        struct item {
            string palavra;
            bool palavra_completa;
        };
        struct item *hash;
        long int M;
    
    Dicionario(){
        vector<string> palavras = {};
        int quant = ler_arquivo("dic.txt", palavras);
        for (string p:palavras){
            cout << p << endl;
        }
    };

    void add(long int h, item i){
        

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

    int encode(string chave){
        long int h = 0;
        int n =1;
        for(char l:chave){
            h += l*pow(73, n);
            n++;
        }
        return h%M;
    };

};



int main(){
    Dicionario *dic = new Dicionario;

}