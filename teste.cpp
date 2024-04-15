#include <bits/stdc++.h>
using namespace std;


int main(){
    string a = string("ola tudo bem");
    a += string(" testando");
    a.erase(a.begin()+2);
    cout << a << endl;

    printf("\x1B[31mTexting\033[0m\t\t"); // vermelho
    printf("\x1B[32mTexting\033[0m\t\t"); // verde
    printf("\x1B[33mTexting\033[0m\t\t"); // amarelo
    printf("\x1B[34mTexting\033[0m\t\t"); // azul
    printf("\x1B[35mTexting\033[0m\n"); // roxo
    
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[37mTexting\033[0m\t\t");
    printf("\x1B[93mTexting\033[0m\n");
    
    printf("\033[3;42;30mTexting\033[0m\t\t");
    printf("\033[3;43;30mTexting\033[0m\t\t");
    printf("\033[3;44;30mTexting\033[0m\t\t");
    printf("\033[3;104;30mTexting\033[0m\t\t");
    printf("\033[3;100;30mTexting\033[0m\n");

    printf("\033[3;47;35mTexting\033[0m\t\t");
    printf("\033[2;47;35mTexting\033[0m\t\t");
    printf("\033[1;47;35mTexting\033[0m\t\t");
    

}