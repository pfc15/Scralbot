
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <iostream>
#include <bits/stdc++.h>
using namespace std;


void func(vector<string>& vect) {
    char *a = (char*) malloc(sizeof(char)*20);
    strcpy(a, "ola mundo");
    vect.insert(vect.end(), a);
    free(a);
    
} 
  
int main() 
{ 
    vector<string> vect; 
    vect.push_back("vsf"); 
    vect.push_back("babaca"); 
    string a = "vsf";
    if (vect.at(0)==a) cout << "sim!\n";
}