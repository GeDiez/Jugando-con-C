#include <queue>
#include <stdio.h>
using namespace std;

typedef struct {
	int tab[3][3];
	int x0;
	int y0;
} tablero;

queue<tablero> cola;

void insertNodosHijo(tablero nodoPadre);
bool estadoFinal(tablero nodo);
void run();
void printT(tablero);

main(){
	tablero inicial;
	inicial.tab[0][0] = 1;
	inicial.tab[0][1] = 2;
	inicial.tab[0][2] = 3;
	inicial.tab[1][0] = 0;
	inicial.tab[1][1] = 5;
	inicial.tab[1][2] = 6;
	inicial.tab[2][0] = 4;
	inicial.tab[2][1] = 7;
	inicial.tab[2][2] = 8;
	inicial.x0 = 1; inicial.y0 = 0;
	cola.push(inicial);
	run();
	printf("%s\n", "se encontro una solucion");
	return 0;
}

void run(){
	tablero t = cola.front();
	printf("%s\n", "<--->");
	printT(t);
	cola.pop();
	insertNodosHijo(t);
	if(estadoFinal(t))
		return;
	run();
}

void insertNodosHijo(tablero nodoPadre){
	if(nodoPadre.y0 != 2){ // Derecha
		tablero e = nodoPadre;
		e.tab[e.x0][e.y0] = e.tab[e.x0][e.y0+1];
		e.tab[e.x0][e.y0+1] = 0;
		e.y0++;
		cola.push(e);
	}
	if(nodoPadre.y0 != 0){ //izquierda
		tablero t = nodoPadre;
		t.tab[t.x0][t.y0] = t.tab[t.x0][t.y0-1];
		t.tab[t.x0][t.y0-1] = 0;
		t.y0--;
		cola.push(t);
	}
	if(nodoPadre.x0 != 2){//
		tablero t = nodoPadre;
		t.tab[t.x0][t.y0] = t.tab[t.x0+1][t.y0];
		t.tab[t.x0+1][t.y0] = 0;
		t.x0++;
		cola.push(t);
	}
	if(nodoPadre.x0 != 0){
		tablero t = nodoPadre;
		t.tab[t.x0][t.y0] = t.tab[t.x0-1][t.y0];
		t.tab[t.x0-1][t.y0] = 0;
		t.x0--;
		cola.push(t);
	}
}

bool estadoFinal(tablero t){
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

void printT(tablero t){
	for (int i = 0; i < 3; i++){
		printf(" ");
		for (int j = 0; j < 3; j++)
			printf("%d ", t.tab[i][j]);
		printf("\n");
	}
}