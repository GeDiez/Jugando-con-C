#include <queue>
#include <stdio.h>
using namespace std;

typedef struct {
	int j3;
	int j5;
} estado;

queue<estado> cola;

void insertNodosHijo(estado nodoPadre);
bool estadoFinal(estado nodo);
void run();

int main(){
	estado inicial;
	inicial.j3 = 0;
	inicial.j5 = 0;
	cola.push(inicial);
	run();
	printf("%s\n", "Encontro una solucion");
	return 0;
}

void run(){
	estado e = cola.front();
	printf("Jarra 5 con %d\n jarra 3 con %d\n", e.j5, e.j3);
	cola.pop();
	insertNodosHijo(e);
	if (estadoFinal(e))
		return;
	run();
}

bool estadoFinal(estado nodo){
	if(nodo.j5 == 4)
		return true;
	return false;
}

void insertNodosHijo(estado nodoPadre){
	//llenar jarra de 3
	if(nodoPadre.j3 < 3){
		estado e;
		e.j3 = 3;
		e.j5 = nodoPadre.j5;
		cola.push(e);
	}
	//llenar jarra de 5
	if(nodoPadre.j5 < 5){
		estado e;
		e.j3 = nodoPadre.j3;
		e.j5 = 5;
		cola.push(e);
	}
	//vaciar la jarra de 3
	if(nodoPadre.j3 > 0){
		estado e;
		e.j3 = 0;
		e.j5 = nodoPadre.j5;
		cola.push(e);
	}
	//vaciar jarra de 5
	if(nodoPadre.j5 > 0){
		estado e;
		e.j3 = nodoPadre.j3;
		e.j5 = 0;
		cola.push(e);
	}
	//cambiar de jarra 3 a la de 5
	if(nodoPadre.j3 > 0 && nodoPadre.j5 < 5){
		estado e;
		int aux = nodoPadre.j3 + nodoPadre.j5;
		if(aux > 5){
			e.j5 = 5;
			e.j3 = aux - 5;
		}else{
			e.j5 = aux;
			e.j3 = 0;
		}
		cola.push(e);
	}
	//cambiar de 5 a 3
	if(nodoPadre.j3 < 3 && nodoPadre.j5 > 0){
		estado e;
		int aux = nodoPadre.j3 + nodoPadre.j5;
		if(aux > 3){
			e.j5 = aux - 3;
			e.j3 = 3;
		}else{
			e.j5 = 0;
			e.j3 = aux;
		}
		cola.push(e);
	}
}