
#include "Dicionario.h"
# include "Jogador.h"
using namespace std;


int main(){
    auto start = chrono::steady_clock::now();
    Dicionario *dic = new Dicionario;
    cout << "palavra: " << dic->ht[dic->procura("aba")].palavra << endl;
    Jogador *j = new Jogador("pedro");
    cout << "jogador: " << j->nome <<" peças: " << string(j->pecas) << endl;
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
    free(j);
    free(dic->ht);
    free(dic);
}