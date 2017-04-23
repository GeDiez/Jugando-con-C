#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

typedef struct {
	int tab[8][8];
	int dot[2];
} estado;

bool puedeAvanzar(estado, int);
estado avanzar(estado, int);
bool resolver(estado, int);
estado crearTablero();
bool esEstadoFinal(estado);
void printEstado(estado);
stack<estado> stacky;
const int profMax = 31;
const int UP = 1, DOWN = 2, RIGTH = 3, LEFT = 4;
int main()
{
	estado myTab = crearTablero();
	printEstado(myTab);
	if(resolver(myTab, 0)){
		printf("%s\n", "Se llego a una solucion");
		while(!stacky.empty()){
			printEstado(stacky.top());
			stacky.pop();
		}
	}
	else
		printf("%s\n", "Aun no se ha hallado una solucion, intenta con una profundidad mayor");
	return 0;
}

estado avanzarArriba(estado e){

}

estado crearTablero(){
	estado e;
	e.tab[0][0] = 32; e.tab[0][1] = 32;	e.tab[0][2] = 32;	e.tab[0][3] = 32;	e.tab[0][4] = 32;	e.tab[0][5] = 32;	e.tab[0][6] = 32;	e.tab[0][7] = 35;
	e.tab[1][0] = 32;	e.tab[1][1] =	35; e.tab[1][2] =	35;e.tab[1][3] =	35;e.tab[1][4] = 32;e.tab[1][5] = 35;e.tab[1][6] = 32;	e.tab[1][7] =	32;
	e.tab[2][0] = 32;	e.tab[2][1] = 32;	e.tab[2][2] = 32;	e.tab[2][3] = 32;	e.tab[2][4] = 32;e.tab[2][5] = 35;e.tab[2][6] = 32;	e.tab[2][7] = 32;
	e.tab[3][0] = 35; e.tab[3][1] = 32; e.tab[3][2] = 35;e.tab[3][3] = 32;	e.tab[3][4] = 35;e.tab[3][5] = 35;e.tab[3][6] = 32;e.tab[3][7] = 35;
	e.tab[4][0] = 35; e.tab[4][1] = 35; e.tab[4][2] = 35;e.tab[4][3] = 32;	e.tab[4][4] = 35;e.tab[4][5] = 32;	e.tab[4][6] = 32;	e.tab[4][7] = 35;
	e.tab[5][0] = 32; e.tab[5][1] = 32;	e.tab[5][2] = 32;	e.tab[5][3] = 32;	e.tab[5][4] = 35;e.tab[5][5] = 32;	e.tab[5][6] = 35;e.tab[5][7] = 35;
	e.tab[6][0] = 35;	e.tab[6][1] = 32; e.tab[6][2] = 35;e.tab[6][3] = 35;e.tab[6][4] = 35;e.tab[6][5] = 32;	e.tab[6][6] = 32;	e.tab[6][7] = 32;
	e.tab[7][0] = 69;	e.tab[7][1] = 32;	e.tab[7][2] = 32;	e.tab[7][3] = 35;	e.tab[7][4] = 32;	e.tab[7][5] = 32;	e.tab[7][6] = 35;	e.tab[7][7] = 83;
	e.dot[0] = 7;
	e.dot[1] = 0;
	return e;
}
/*
*Metodo puedeAvanzar()
* verificamos si en el laberinto el punto se puede mover a dicha direccion denotado por un entero
* segun las constantes definidas 
* de ser verdadero regresamo un valor true
*/
bool puedeAvanzar(estado e, int dir){
	int x = e.dot[0];
	int y = e.dot[1];
	if(dir == UP)
		x = x-1;
	if(dir == DOWN)
		x = x+1;
	if(dir == RIGTH)
		y = y+1;
	if(dir == LEFT)
		y = y-1;
	if(e.tab[x][y] == 32 || e.tab[x][y] == 83)
		return true;
	return false;
}
/*
*	Metodo Avanzar
* Toma un estado del tablero y mueve el punto(dot) en la direccion
*	del parametro dir definido por una constante
*	RETURN: regresa un nuevo estado con el movimiento 
*/
estado avanzar(estado e, int dir){
	int x = e.dot[0];
	int y = e.dot[1];
	if(dir == UP)
		x = x-1;
	if(dir == DOWN)
		x = x+1;
	if(dir == RIGTH)
		y = y+1;
	if(dir == LEFT)
		y = y-1;
	e.tab[e.dot[0]][e.dot[1]] = 32;
	e.dot[0] = x;
	e.dot[1] = y;
	e.tab[x][y] = 46;
	return e;
}
/*
* Metodo Resolver:
* buscara una solucion mediante el algoritmo de primero en profundidad de arboles
*	verificara la prof, si se llego al estado final en caso contrario
* buscara en un siguiente estado valido
*/

bool resolver(estado e, int prof){
	prof++;
	if(prof >= profMax)
		return false;
	if(esEstadoFinal(e))
		return true;
	if(puedeAvanzar(e, UP)){
		if(resolver(avanzar(e, UP), prof)){
			stacky.push(e);
			return true;
		}
	}
	if(puedeAvanzar(e, DOWN)){
		if(resolver(avanzar(e, DOWN), prof)){
			stacky.push(e);
			return true;
		}
	}
	if(puedeAvanzar(e, RIGTH)){
		if(resolver(avanzar(e, RIGTH), prof)){
			stacky.push(e);
			return true;
		}
	}
	if(puedeAvanzar(e, LEFT)){
		if(resolver(avanzar(e, LEFT), prof)){
			stacky.push(e);
			return true;
		}
	}
	return false;
}

bool esEstadoFinal(estado e){
	int x = e.dot[0];
	int y = e.dot[1];
	if(x==7 && y==7)
		return true;
	return false;
}

void printEstado(estado e){
	printf("%s\n", "----------");
	for (int i = 0; i < 8 ; ++i){
		printf("%c", 124);
		for (int j = 0; j < 8; ++j){
			printf("%c", e.tab[i][j]);
		}
		printf("%c\n", 124);
	}
	printf("%s\n", "----------");
}