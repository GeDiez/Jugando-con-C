#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

//Definios al estado como una estructura
typedef struct {
	int tab[3][3];
	int x0;
	int y0;
} tablero;

/*
*Los siguientes metodos permiten mover el espacio vacio (denotado por 0 en la matriz)
*una posicion ya se a la der., izq., abajo o arriba
*regresa un tablero como resultado con la nueva modificacion.
*/
tablero moverEspacioArriba(tablero);
tablero moverEspacioAbajo(tablero);
tablero moverEspacioDerecha(tablero);
tablero moverEspacioIzq(tablero);
/*
* Estos metodos permiten identificar si el estado es final,
* e inicializa la recursividad para reolver el problema
* print permite mostrar el tablero en consola.
* Variables Globales*
* definimos a prof y profMax para definir en que punto del arbol estamos
* y cual es el limite al que se llegara recursuvamente.
*/
bool esEstadoFinal(int[3][3]);
bool resolver(tablero);
void printT(tablero);
int prof = 0, profMax = 5;
stack <tablero> stacky;

main(){
	tablero t;
	t.tab[0][0] = 1;
	t.tab[0][1] = 2;
	t.tab[0][2] = 3;
	t.tab[1][0] = 0;
	t.tab[1][1] = 5;
	t.tab[1][2] = 6;
	t.tab[2][0] = 4;
	t.tab[2][1] = 7;
	t.tab[2][2] = 8;
	t.x0 = 1; t.y0 = 0;
	if(resolver(t)){
		printf("%s\n", "se encontro una solucion.");
		while(!stacky.empty()){
			printT(stacky.top());
			printf("%s\n", "<->");
			stacky.pop();
		}
	}
	else{
		printf("%s\n", "aun no se encuentra una solucion. Prueba una prof. mayor");
	}
	return 0;
}

tablero moverEspacioDerecha(tablero t){
	t.tab[t.x0][t.y0] = t.tab[t.x0][t.y0+1];
	t.tab[t.x0][t.y0+1] = 0;
	t.y0++;
	return t;
}

tablero moverEspacioIzq(tablero t){
	t.tab[t.x0][t.y0] = t.tab[t.x0][t.y0-1];
	t.tab[t.x0][t.y0-1] = 0;
	t.y0--;
	return t;
}

tablero moverEspacioArriba(tablero t){
	t.tab[t.x0][t.y0] = t.tab[t.x0-1][t.y0];
	t.tab[t.x0-1][t.y0] = 0;
	t.x0--;
	return t;
}

tablero moverEspacioAbajo(tablero t){
	t.tab[t.x0][t.y0] = t.tab[t.x0+1][t.y0];
	t.tab[t.x0+1][t.y0] = 0;
	t.x0++;
	return t;
}

bool esEstadoFinal(tablero t){
	if(
		t.tab[0][0] == 1 &&
		t.tab[0][1] == 2 &&
		t.tab[0][2] == 3 &&
		t.tab[1][0] == 4 &&
		t.tab[1][1] == 5 &&
		t.tab[1][2] == 6 &&
		t.tab[2][0] == 7 &&
		t.tab[2][1] == 8 &&
		t.tab[2][2] == 0
		)
		return true;
	return false;
}

bool resolver(tablero t){
	printT(t);
	prof++;
	if(prof >= profMax)
		return false;
	if(esEstadoFinal(t)){
		stacky.push(t);
		return true;
	}
	if(t.y0 != 2){
		if(resolver(moverEspacioDerecha(t))){
			stacky.push(t);
			return true;
		}
		prof--;
	}
	if(t.y0 != 0){
		if(resolver(moverEspacioIzq(t))){
			stacky.push(t);
			return true;
		}
		prof--;
	}
	if(t.x0 != 2){
		if(resolver(moverEspacioAbajo(t))){
			stacky.push(t);
			return true;
		}
		prof--;
	}
	if(t.x0 != 0){
		if(resolver(moverEspacioArriba(t))){
			stacky.push(t);
			return true;
		}
		prof--;
	}
	return false;
}

void printT(tablero t){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
			printf("%d ", t.tab[i][j]);
		printf("\n");
	}
}
