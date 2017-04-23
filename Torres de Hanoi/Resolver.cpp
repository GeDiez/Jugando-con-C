#include <iostream>
#include <stdio.h>
using namespace std;

struct estado{
    int t1 [8] = {1,2,3,50};
    int t2 [8];
    int t3 [8];  
}e1, e2, e3;

int main(){
   estado ejemplo [3] = {e1, e2, e3};
   int imprime = (sizeof(ejemplo[0].t1[0])/sizeof(int)); 
   cout<< imprime<<" "<<ejemplo[0].t1[3];   
   
   return 0;
}