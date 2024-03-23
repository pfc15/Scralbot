
#include "Dicionario.h"
using namespace std;


int main(){
    auto start = std::chrono::steady_clock::now();
    Dicionario *dic = new Dicionario;
    cout << "palavra: " << dic->ht[dic->procura("aba")].palavra << endl;
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
}