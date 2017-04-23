#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define NBITS 252
#define MIN 0.0
#define MAX 8.0
#define TVARB 8
#define NIND 50
#define NCEP 0
#define NCEM 2

#define NVARIABLES 2
#define NUMGEN 15 

#define conspena 0.0
void GAB_INDIVIDUO();
void CINDB_RPVAR();
float RF();
void ORDENACIONMAX(float[],int,int);
void ORDENACIONMIN(float[],int,int);
void FITNESS();
void ELITISMO();

void SUSTITUYEVARELIT();

void CRUZA();
void SELECCION();
void RULETA();
void MUTACION();
float BUSQUEDA();
float BUSQUEDAMIN();
void RESTRICCIONES();



int tnind[NIND][TVARB*NVARIABLES],caidas[NIND],resp=0;
int nva_generacion[NIND][TVARB*NVARIABLES],temp_cruza[TVARB*NVARIABLES],indicemayor=0,vectorelite[TVARB*NVARIABLES],numresvio=0;
float var[NVARIABLES], nind[NIND],vacum[NIND],optimo,varelitismo=0.0,mejores[NUMGEN];

int main()
{
  int horac=0,n=0,x=0,acumtv=0,i=0,in=0,indice=0;
  float acum=0.0,numac=0.0,velitismo=0.0;
  long horal=0;
  
  while(resp!=3){
  
  horal= time(NULL);
  horac=(unsigned int)horal/2;
  srand(horac);
  srand(100);
  GAB_INDIVIDUO();
  CINDB_RPVAR();

 for(int j=0; j<NIND; j++)
	{  printf("valor por individuo %d: %.2f",j,nind[j]);
	   printf("\n");
	}
 printf("desea maximizar=0, minimizar=1?\n");
 scanf("%d",&resp);
 
 while (n<NUMGEN)
  {
	
    ORDENACIONMAX(nind,0,NIND-1);
	
	
	if(resp==0)
	{
		FITNESS();
		ELITISMO();
		RULETA();
		SELECCION();
		CRUZA();
		MUTACION();
		CINDB_RPVAR();
		SUSTITUYEVARELIT();
		mejores[n]=BUSQUEDA();
	}

    
	for(int j=0; j<NIND; j++)
	{  printf(" %d: %.2f",j,nind[j]);
	   printf("\n");
	}
	
    n++;
  }

  printf("MEJORES DE CADA GENERACION  \n");
  for (int w=0;w<NUMGEN;w++)
  {
     printf(" %.4f \n", mejores[w]);
  }

   n=0;x=NIND-1;
   if(resp==1)
   {
     while(n!=x)
	 {
       if(nind[n]<=nind[x])
	   {
 	     optimo=nind[n]; 
	     x--;
	    indice=n;
	   }
       else
	   { 
	    optimo=nind[x];
	    n++;
	    indice=x;
	   }
	 }
   }

   n=0;x=NIND-1;
   if(resp==0)
   {
     while(n!=x)
	 {
       if(nind[n]>=nind[x])
	   {
 	     optimo=nind[n]; 
	     x--;
	     indice=n;
	   }
      else
	  { 
	    optimo=nind[x];
	    n++;
	    indice=x;
	  }
	 }
   }
   in=0;
   acumtv=TVARB;
   i=0;
  while(in<NVARIABLES)
	{
	  acum=0.0;
	  n=9;
      
      
	 while(i<acumtv)
	  {
		  numac=tnind[indice][i];
		  if(numac==1)
		  {
		    numac=(int)pow(2,n);
			acum=acum+ (float)numac;
		  }
	   i++;n--;
	  }

	  acum=MIN+(acum*((MAX-MIN)/NBITS));
	 
	  acumtv=acumtv+TVARB;
	  in++;
	}

  printf ("INDIVIDUO : ");
  for (int h=0; h<TVARB*NVARIABLES;h++)
	 printf("%d",tnind[indice][h]);

  printf("\n VALOR OPTIMO %.4f \n",optimo);

  printf("desea Continuar=0 Salir=3 ?\n");
  scanf("%d",&resp);
 }

}

void GAB_INDIVIDUO()
{
  int x=0, i=0, numa, sigue;

  while(x<NIND)
  {
    for(i=0; i<(TVARB*NVARIABLES); i++)
	{
	  numa=rand()%65;
	  if(numa<50)
		  tnind[x][i]=0;
	  else
		  tnind[x][i]=1;
	}
	x++;
    printf("\n");
  }
    printf("\n");
}

void CINDB_RPVAR()
{
  float acum=0.0;
  int j=0, x=0, i=0, numac=0, n=9, acumtv=TVARB, sigue;

  printf("\n");

  while(j<NIND)
  {
	x=0;
	acum=0.0;
	acumtv=TVARB;
	i=0;
    while(x<NVARIABLES)
	{
	  acum=0.0;
	  n=9;
	 while(i<acumtv)
	  {
		  numac=tnind[j][i];
		  if(numac==1)
		  {
		    numac=(int)pow(2,n);
			acum=acum+ (float)numac;
		  }
	   i++;n--;
	  }

	  acum=MIN+(acum*((float)(MAX-MIN)/NBITS));
	  var[x]=acum;
	  acumtv=acumtv+TVARB;
	  x++;
	}
	nind[j]=RF();
	j++;
  }
}

float RF()//
{
  int i;
  float vind;
  vind=0.0;
  i=0;
    vind = (float) (abs((var[i])-5)/(2+sin(i)));

  return vind;
}
void RESTRICCIONES()
{
	int i;
	float rest1=0.0,rest2=0.0,rest3=0.0;
	numresvio=0;
	rest1=(2*var[0])+(3*var[1]);
	rest2=(-3*var[0])+(2*var[1]);
	rest3=(2*var[0])+var[1];
	if(rest1>6)
		numresvio++;		
	if(rest2>3)
		numresvio++;
	if(rest3>4)
		numresvio++;
	
}

void ORDENACIONMAX(float a[NIND], int izq, int der)
{

 int i=izq, j=der, vectoraux[TVARB*NVARIABLES]; 
 float pivote = a[(izq+der)/2];

 do {
    while(a[i]<pivote)
		i++;
	while(a[j]>pivote)
		j--;
	if (i<=j){
      float aux=a[i];
	  
	  for(int y=0;y<TVARB*NVARIABLES;y++)
		  vectoraux[y]=tnind[i][y];
	  
	  a[i]=a[j];
	  
	  for(int z=0;z<TVARB*NVARIABLES;z++)
		  tnind[i][z]=tnind[j][z];
	  
	  a[j]=aux;
	  
	  for(int x=0;x<TVARB*NVARIABLES;x++)
		  tnind[j][x]=vectoraux[x];
	  i++;
	  j--;
	}

 }while(i<=j);

 if(izq<j) ORDENACIONMAX(a,izq, j);
 if(i<der) ORDENACIONMAX(a,i,der);
 
 for (int k=0;k<NIND;k++)
 {
	nind[k]=a[k];
 }
 

}
void ELITISMO ()
{

 varelitismo=nind[NIND-1];

 for(int y=0;y<TVARB*NVARIABLES;y++)
	vectorelite[y]=tnind[NIND-1][y];

}
void SUSTITUYEVARELIT()
{
 int n=0,x=NIND-1,indice=0;;
 
 while(n!=x)
 {
   if(nind[n]<=nind[x])
   {
	   
	   x--;
	   indice=n;
   }
   else

   {
	   
	   n++;
	   indice=x;
   }
 }

 nind[indice]=varelitismo;

 for(int y=0;y<(TVARB*NVARIABLES);y++)
 {
	nva_generacion[indice][y]=vectorelite[y];
 }
 

  for(int s=0;s<NIND;s++)
	{
		  for(int c=0;c<(TVARB*NVARIABLES);c++)
		  {
		    tnind[s][c]=nva_generacion[s][c];
		  }

	}

}
void FITNESS() 
{
 int i=0;
 float temp=0.0, temp1=0.0,temp2=0.0;

 for (i=0;i<NIND;i++)
 {
     temp1=(float)i/((float)NIND-1);
	 temp2=temp1 *(NCEM-NCEP);
	 temp=(NCEP+temp2)/NIND;
	 vacum[i]=temp;//guarda el valor relativo
 }	
}

void RULETA()
{
 float sumind=0,arg=0,gale,sumacum=0;
 int cont=0,i,indeli=0;

 for(i=0;i<NIND;i++)
		caidas[i]=0;
 gale=rand()%99;
 gale=gale/100;
 i=0;
 sumacum=vacum[i];

 while(cont<NIND)
 {
   if(gale>=arg && gale<=sumacum)
   {
	   caidas[i]=caidas[i]+1;
	   cont++;
	   i=0;
	   arg=0;
	   sumacum=vacum[0];
	   gale=rand()%99;
	   gale=gale/100;
   }
   else
   {
	   arg=sumacum;
	   i++;
	   sumacum+=vacum[i];
   }
 }

}
void SELECCION()
{
  int cont=0,temp=0,i=0,x,y;
  while(i<NIND)
  {
	  temp=caidas[i];
	  if(temp>0)
	  {
	    for(x=0;x<temp;x++)
		{
		  for(y=0;y<(TVARB*NVARIABLES);y++)
			  nva_generacion[cont][y]=tnind[i][y];
		  cont++;
		}
	  }
    i++;
  }
}

void CRUZA()
{
	int gale=0,probc=0,pos=0,i=0, contcruza=0, aceptacruza[NIND],temp=0,x=0,y=0;

	gale=rand()%(TVARB*NVARIABLES-2);

	for(i=0;i<NIND;i++)
	{
		aceptacruza[i]=0;
	}
	i=0;
	while(i<NIND)
	{
	    probc=rand()%99;
		if(probc>70)
		{
			aceptacruza[i]=1;
			contcruza++;
		}
		else
			aceptacruza[i]=0;
		i++;
	}

	contcruza=contcruza/2;
	i=0;temp=0;y=0;
	if(contcruza>=1)
	{
		while(i<contcruza)
		{
			while(y<NIND)
				{
					if(aceptacruza[y]==1)
					{
					  temp++;
					  if(temp==1)
					  {
						for(x=0;x<gale;x++)
						temp_cruza[x]=nva_generacion[y][x];
						 pos=y;
					  }
					  if (temp==2)
					  {
						  for(x=0;x<gale;x++)
						  {
							  nva_generacion[pos][x]=nva_generacion[y][x];
						    nva_generacion[y][x]=temp_cruza[x];
						  }
						  temp=0;
					  }
					}
				   y++;
				}
			i++;
		   gale=rand()%((TVARB*NVARIABLES)-2);
		}
	}
}

void MUTACION()
{
	int galemut,muta[TVARB*NVARIABLES]={0};
	
	
  for (int v=0;v<NIND;v++)
  {
    
	for (int i=0;i<TVARB*NVARIABLES;i++)
	{
		galemut=rand()%99;
		if (galemut<1)
			muta[i]=1;
	   else
		    muta[i]=0;
	}
   	  
	  for (int j=0;j<TVARB*NVARIABLES;j++)
	  {
		if (muta[j]==1)
		
			if(tnind[v][j]==1)
	   
			   nva_generacion[v][j]=0;
		    else

		  	   nva_generacion[v][j]=1;
	  }
  }

    for(int s=0;s<NIND;s++)
	{
		  for(int c=0;c<(TVARB*NVARIABLES);c++)
		  {
		    tnind[s][c]=nva_generacion[s][c];
		  }

	}
}

float BUSQUEDA()
{

int n=0,x=NIND-1;
 while(n!=x)
 {
   if(nind[n]>=nind[x])
   {
	   x--;
	   indicemayor=n;
   }
 
   else
   {
	   n++;
	   indicemayor=x;
   }
 }
 optimo=nind[indicemayor];
 return optimo;
}

