# <-- funciones sobre Matrices -->

def new(filas, cols):
  matriz = [None] * filas
  for i in range(filas):
    matriz[i]=[0]*cols
  return matriz

def map(f, matriz):
  retmatriz = []
  for x in matriz:
    vector = []
    for item in x:
      vector.append(f(item))
    retmatriz.append(vector)
    vector = []
  return retmatriz
  
def for_each(f, matriz):
  for x in matriz:
    for item in x:
      f(item)
  
def filter(f, matriz):
  retmatriz = []
  for x in matriz:
    vector = []
    for item in x:
      if(f(item)):
        vector.append(item)
    retmatriz.append(vector)
    vector = []
  return retmatriz
  
def toFile(matriz, path):
  file = open(path, 'w')
  for x in range(len(matriz[0])):
    for y in range(len(matriz)):
      file.write(str(matriz[y][x]))
    file.write('\n')
  file.close()
 
def copy(matriz):
  return map(self, matriz)

def self(item):
  return item