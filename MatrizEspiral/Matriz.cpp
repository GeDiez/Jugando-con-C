#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main(){
    system("clear");
    int long_x;
    int x1 = 0, y1 = 0, inc_x, inc_y, ret = 0, numero = 1;
    int patronY[4];
    int patronX[4];
    cout<<"Ingresa las dimension X de la Matriz NxN \n     X: ";
    cin>>long_x;
    int matriz[long_x][long_x];
    for(int i=0; i<long_x; i++){
        for(int j=0; j<long_x; j++){
            matriz[i][j] = 0;
        }
    }
    int opcion;
    cout<<"Elige una opcion del Menu \n  1) Girar a la derecha\n  2) Girar a la izquierda\n ¿Qué eliges? ";
    cin>>opcion;
    switch(opcion){
        case 1:
            patronX[0] = 0; patronX[1]=1; patronX[2]=0; patronX[3]=-1;
            patronY[0] = 1; patronY[1]=0; patronY[2]=-1; patronY[3]=0;
        break;
        case 2:
            patronY[0] = 0; patronY[1]=1; patronY[2]=0; patronY[3]=-1;
            patronX[0] = 1; patronX[1]=0; patronX[2]=-1; patronX[3]=0;
        break;
        default:
            cout<<"Opcion fuera de rango\n";
    } 
    inc_x = patronX[0]; inc_y = patronY[0];
    while(true){
        matriz[x1][y1] = numero++;
        if((x1+inc_x)==long_x || (y1+inc_y)==long_x || (x1+inc_x)== -1 || (y1+inc_y)== -1){
            ret++;                    
            if(ret == 4){ret = 0;}
            inc_x = patronX[ret];
            inc_y = patronY[ret];
        }
        if(matriz[x1+inc_x][y1+inc_y] > 0){
            ret++;
            if(ret == 4){ret = 0;}
            inc_x = patronX[ret];
            inc_y = patronY[ret];
            if(matriz[x1+inc_x][y1+inc_y] > 0){
                break;
            }
        }
        x1 = x1+inc_x; y1 = y1+inc_y;
    }
    cout<<"\n";
    for(int i=0; i<long_x; i++){
        for(int j=0; j<long_x; j++){
            cout<<" "<<matriz[i][j];
        }cout<<"\n";
    }cout<<"\n";
}