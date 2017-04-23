#include <stdio.h>
#include <string.h>
#include <stack>

using namespace std;

typedef struct {
	int j5;
	int j3;
} jarras;
//metodos
jarras llenarJarra5(jarras);
jarras llenarJarra3(jarras);
jarras vaciarJarra3(jarras);
jarras vaciarJarra5(jarras);
jarras Jarra3AJarra5(jarras);
jarras Jarra5AJarra3(jarras);
bool esEstadoFinal(jarras);
bool resolver(jarras);
void printJarras(jarras);
/*
* @int jarras[2]; inicializamos las jarras vacias, la jarra de 5 lts
* esta en la posicion 0, y la de 3 en la posicion 1 del
* arreglo llamado jarras.
* 
* @int prof; Contador que guarda la profundidad en cada instante
* @int profMax; Es el limite al que el algoritmo descendera por el arbol
* @stack<> s; es la pila que contendra los estados solucion.
*/
int prof = 0, profMax = 10;
stack<jarras> stacky;
int main(){
	jarras j;
	j.j5 = 0;
	j.j3 = 0;
	if(resolver(j)){
		printf("%s\n", "Se hallo una solucion");
		while(!stacky.empty()){
			printJarras(stacky.top());
			stacky.pop();
		}
	}
	else
		printf("%s\n", "No se ha encontrado una solucion, pueba una prof mayor");
	return 0;
}

jarras llenarJarra3(jarras j){
	j.j3 = 3;
	return j;
}

jarras llenarJarra5(jarras j){
	j.j5 = 5;
	return j;
}

jarras vaciarJarra3(jarras j){
	j.j3 = 0;
	return j;
}

jarras vaciarJarra5(jarras j){
	j.j5 = 0;
	return j;
}

jarras Jarra3AJarra5(jarras j){
	int aux = j.j3+j.j5;
		if(aux > 5){
			j.j5 = 5;
			j.j3 = aux - 5;
		}else{
			j.j5 = aux;
			j.j3 = 0;
		}
		return j;
}

jarras Jarra5AJarra3(jarras j){
	int aux = j.j5+j.j3;
	if(aux > 3){
			j.j3 = 3;
			j.j5 = aux-3;
		}
		else{
			j.j3 = aux;
			j.j5 = 0;
		}
		return j;
}

bool esEstadoFinal(jarras j){
	if (j.j5 == 4)
		return true;
	return false;
}

bool resolver(jarras j){
	prof++;
	if (prof >= profMax)
		return false;
	if (esEstadoFinal(j)){
		stacky.push(j);
		return true;
	}
	if(j.j3 < 3){
		if(resolver(llenarJarra3(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	if (j.j5 < 5){
		if(resolver(llenarJarra5(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	if (j.j5 > 0){
		if(resolver(vaciarJarra5(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	if (j.j3 > 0){
		if(resolver(vaciarJarra3(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	if (j.j5 < 5 && j.j3 > 0){
		if(resolver(Jarra3AJarra5(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	if (j.j5 > 0 && j.j3 < 3){
		if(resolver(Jarra5AJarra3(j))){
			stacky.push(j);
			return true;
		}
		prof--;
	}
	return false;
}
void printJarras(jarras j){
	printf("%s%d\n%s%d \n<->\n","jarra de 3 lts: ", j.j3, "jarra de 5 lts: ", j.j5);
}