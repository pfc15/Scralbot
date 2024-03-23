
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <iostream>
#include <bits/stdc++.h>
using namespace std;


long int encode(string chave){
        long int h = 0;
        int n =1;
        for(char l:chave){
            h += l*pow(17, n);
            n++;
        }
        long int M = pow(3, 12); //tamanho da hash
        return h%M;
    };
  
int main() 
{ 
    cout << encode(string("abacamartado"))<<endl;
}