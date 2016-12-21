#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Constantes del Algoritmo Genetico Simple
const int tP = 20; //Tamaño de la poblacion (Unicamente multiplos de 2).
const int probMutacion = 5; //Porcentaje de que un hijo tenga alguna mutacion.
const int genes = 4; //numero de genes por individuo.

typedef struct{
  int genotipoD;
  int genotipoB[genes];
  double vAptitud;
}Individuo;

bool converge(Individuo[]);
void seleccion(Individuo[], Individuo[]);
void mutacion(Individuo[]);
void cruza(Individuo[],Individuo[]);
void crearPoblacion(Individuo[]);
Individuo crearIndividuo(int);
double Aptitud(int);
int* decToBin(int);
int binToDec(int[]);

int main(){
  srand(time(NULL));
  int numGeneraciones = 1;
  Individuo poblacion[tP];
  crearPoblacion(poblacion);
  Individuo nGeneracion[tP];
  printf("Poblacion Inicial \n");
  for(int i = 0; i<tP; i++){
    printf(" Individuo %d con Genotipo %d\n",i, poblacion[i].genotipoD);
  }
  do{
    cruza(poblacion, nGeneracion);
    mutacion(nGeneracion);
    seleccion(poblacion, nGeneracion);
    printf("Datos de la Generacion %d\n", numGeneraciones);    
    for(int i = 0; i<tP; i++){
      printf(" Individuo %d con Genotipo %d valor de Aptitud %lf\n",i, poblacion[i].genotipoD, poblacion[i].vAptitud);
    }
    numGeneraciones++;
  }while(converge(poblacion) == false);
    printf("***************************************************\nConvergio en %d generaciones Poblacion final: \n", numGeneraciones);
  for(int i = 0; i<tP; i++){
    printf(" Individuo %d con valor de Aptitud %lf\n", i, poblacion[i].vAptitud);
  }
  
  return 0;
}

bool converge(Individuo p[]){
  float sumaGenotipos = 0;
  for(int i = 0; i<tP; i++){
    sumaGenotipos = sumaGenotipos + p[i].vAptitud;
  }
  float promedio = sumaGenotipos/tP;
  float dif = fabs(promedio - p[0].vAptitud);
  float epsilon = 0.001;
  if(dif < epsilon){
    return true;
  }
  else{
    return false;    
  }
}

void seleccion(Individuo p[], Individuo ng[]){
  for(int i = 0; i<tP; i++){
    for(int j = 0; j<tP; j++){
      if(ng[i].vAptitud > p[j].vAptitud){
        p[j] = ng[i];
        break;
      }
    }
  }
}

void cruza(Individuo p[], Individuo ng[]){
  int j = tP-1;
  for(int i=0; i<(tP/2); i++){
    int nuevoGen1[genes], nuevoGen2[genes];
    int aux = 0, mitadGenes = genes/2;
    for(int x=0; x<genes; x++){
      if (aux < mitadGenes){
        nuevoGen1[x] = p[i].genotipoB[x];
        nuevoGen2[x] = p[j].genotipoB[x];
      }
      else{
        nuevoGen1[x] = p[j].genotipoB[x];
        nuevoGen2[x] = p[i].genotipoB[x];
      }
    }
    ng[i] = crearIndividuo(binToDec(nuevoGen1));
    ng[j] = crearIndividuo(binToDec(nuevoGen2));
    j--;
  }
}

void mutacion(Individuo ng[]){
  for(int i=0; i<tP; i++){
   int aleatorio = rand() % 100;
    if(aleatorio <= probMutacion){
      int bitRand = rand() % genes;
      if(ng[i].genotipoB[bitRand] == 0)
        ng[i].genotipoB[bitRand] = 1;
      else
        ng[i].genotipoB[bitRand] = 0;
    } 
  }
}

void crearPoblacion(Individuo p[]){
  int maxValor = (int)pow(2, genes);
  for(int i=0; i<tP; i++){
    int genotipoAleatorio = rand() % maxValor;
    p[i]=crearIndividuo(genotipoAleatorio);
  }
}

Individuo crearIndividuo(int gD){
  Individuo* ip = (Individuo*)malloc(sizeof(Individuo));
  (*ip).genotipoD = gD;
  int* binario = decToBin(gD);
  for(int j = 0; j< genes; j++){
    (*ip).genotipoB[j] = *(binario+j);
  }
  free(binario);
  (*ip).vAptitud = Aptitud(gD);
  Individuo i = (*ip);
  free(ip);
  return i;
}

double Aptitud(int genotipoD){
  //return (float)genotipoD*genotipoD;
  return (double) fabs((genotipoD-5)/(2+sin(genotipoD)));
}

int* decToBin(int dec){
  int* bp = (int*)malloc(genes*sizeof(int)); 
  int mod = 0, pos = genes;
  do{
    mod = dec % 2;
    dec = dec/2;
    pos--;
    *(bp+pos) = mod;
  }while(dec >= 1);
  return bp;
}

int binToDec(int binario[]){
  int dec = 0, bin = 1, nB = genes;
  do{
    nB--;
    if(binario[nB] == 1){
      dec = dec + bin;
    }
    bin = bin*2;
  }while(nB > 0);
  return dec;
}