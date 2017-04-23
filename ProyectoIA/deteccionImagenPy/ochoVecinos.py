import math
from Lib import Matriz as matriz
from Lib import Arreglo as arreglo
from Lib import imagen as i

#recibe una matriz, una coordenada y la direccion, regresa el contenido de la celda adelantada
#los valores que recibe como posicion son los declarados en la constantes de arriba y segun a donde se quiera desplazar
#si la coordenada esta fuera de rango devuelve 0
def nextPosition(matriz, x, y, posicion):
  xi = 0
  yi = 0
  if(posicion == 0):
    xi = x-1
    yi = y
  else:
    if(posicion == 1):
      xi = x-1
      yi = y-1
    else:
      if(posicion == 2):
        xi = x
        yi = y-1
      else: 
        if(posicion == 3):
          xi = x+1
          yi = y-1
        else:
          if(posicion == 4):
            xi = x+1 
            yi = y
          else:
            if(posicion == 5):
              xi = x+1
              yi = y+1
            else:
              if(posicion == 6):
                xi = x
                yi = y+1
              else:
                if(posicion == 7):
                  xi = x-1
                  yi = y+1              
                
  if(xi<0 or yi<0 or xi>=len(matriz[0]) or yi>=len(matriz)):
    return -1
  return matriz[yi][xi]

def ochoVecinos(matriz, matrizDestino, x, y, et):
  Etiquetas = []
  if (matriz[y][x]!=0):
    for c in range(0, 4):
      vecino = i.nextPosition(matriz, x, y, c)
      vecino2 = i.nextPosition(matrizDestino, x, y, c)
      if(vecino != -1):
        if(vecino != 0):
          if(Etiquetas.count(vecino2)==0):
            Etiquetas.append(vecino2)
          matrizDestino[x][y] = vecino2
    if(len(Etiquetas) == 0):
      matrizDestino[x][y] = et
      et=et+1
  return Etiquetas, et

def etiquetar(matrizB):
  TI = []
  etiqueta = 2
  mEtiquetada = matriz.copy(matrizB)
  for x in range(len(mEtiquetada)):
    for y in range(len(mEtiquetada[0])):
      if (mEtiquetada[x][y] == 0):
        vecinos = vecinosAnteriores(mEtiquetada, x, y)
        vecinosPorPixel = arreglo.filter(buscaEt, vecinos)
        TI.append(arreglo.quitarRepetidos(vecinosPorPixel))
#        print x, " ", " ", y," ", vecinos, " ", arreglo.quitarRepetidos(vecinosPorPixel)
        if(len(vecinosPorPixel) == 0):
          mEtiquetada[x][y] = etiqueta
          etiqueta = etiqueta + 1
        else:
          mEtiquetada[x][y] =  vecinosPorPixel[0]
      else: 
        mEtiquetada[x][y] = 0
  ti = TablaIgualdad(TI)
  mE = etiquetadoFinal(mEtiquetada, ti)
  return mE
      
def buscaEt(item):
  if(item != -1 and item != 0):
    return item
  
def vecinosAnteriores(matrizB, x, y):
  vector = []
  for i in range(0, 4):
    vector.append(nextPosition(matrizB, y, x, i))
  return vector
  
def masDeDosEts(arrItem):
  if(len(arrItem) > 1):
    return True

def igualdadesRepetidas(vf, subarr):
  subarr.sort()
  if(vf.count(subarr) == 0):
    vf.append(subarr)
  return vf
    
def TablaIgualdad(ti):
  a = arreglo.filter(masDeDosEts, ti)
  b = arreglo.reduce([], igualdadesRepetidas, ti)
  c = arreglo.filter(masDeDosEts, b)
  c2 = matriz.copy(c)
  for x in c2:
    for x2 in c:
      if(compartenIgualdad(x, x2)):
        x.extend(x2)
  c2 = arreglo.map(arreglo.quitarRepetidos, c2)
  return c2
  
def compartenIgualdad(arr1, arr2):
  for x in arr1:
    for y in arr2:
      if(x == y):
        return True
  return False

def etiquetadoFinal(mE, TI):
  for fila in range(len(mE)):
    for col in range(len(mE[0])):
      if (mE[fila][col] != 0):
        for ti in TI:
          if(ti.count(mE[fila][col]) != 0): 
            mE[fila][col] = ti[0]       
  return mE
  
def cuentaObjetos(mE):
  arreglo = []
  existe = False
  for x in mE:
    for y in x:
      if(y != 0):
        if (len(arreglo) == 0):
          arreglo.append([y, 1, 0])
        else:
          for i in arreglo:
            if(y == i[0]):
              i[1] = i[1] + 1
              existe = True
              break
          if(existe):
            existe = False
          else:
            arreglo.append([y, 1, 0])
            existe = False
  return arreglo            

#pasamos la matriz etiquetada y las etiquetas de los objetos que 
#existen en la imagen 

def perimetro(mE, OAP, mB):
  for x in range(len(mE)):
    for y in range(len(mE[0])):
      item = mE[x][y]
      if(item != 0):
        obj = objeto(OAP, item)
        for i in range(0,8):
          v = nextPosition(mE, y, x, i)
          if(v == 0 or v == -1):
            obj[2] += 1
            mB[x][y] = 100
            break
  return OAP, mE, mB
  
def objeto(arr, et):
  for subarr in arr:
    if(subarr[0] == et):
      return subarr
      
def compacidad(arr):
  p2 = arr[2]*arr[2]
  a = float (arr[1])
  k = 4*math.pi*(a/p2)
  return k
  