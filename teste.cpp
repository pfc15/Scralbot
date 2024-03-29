
#include "Dicionario.h"
# include "Jogador.h"
using namespace std;


int main(){
    vector<string> a = {"p", "dsks", "sdsa"};
    vector< string> b = {"ols", "dsjnks", "salkda"};
    a.insert(a.end(), b.begin(), b.end());
    cout << a.size() << endl;

}