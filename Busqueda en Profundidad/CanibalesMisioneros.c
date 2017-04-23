#include <stdio.h>

typedef struct {
	int m[2];
	int c[2];
	bool bote;
} estado;

//Definimos acciones
//movemos un canibal y un misionero del lado der al izq
bool mcdi(estado es){
	if(es.m[1]!=0 && es.c[0]!=0){
		 	if(es.m[0]+1 > es.c[0]+1)
			return false;
			return true;
	}
	return false;	
}

bool mcid(estado es){
	if(es.m[1]+1 > es.c[1]+1)
		return false;
	return true;
}

bool  m2id(estado es){
	if (es.m2[0] > 2)
	{
		if(es.m[1]+2 > es.c[1])
			return true;
		return false;
	}
}

int main(){

	return 0;
}
