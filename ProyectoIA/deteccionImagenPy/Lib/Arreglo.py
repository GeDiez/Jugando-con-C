# <-- funciones sobre arreglos -->

def map(f, arreglo):
  retarreglo = []
  for x in arreglo:
    retarreglo.append(f(x))
  return retarreglo
  
def filter(f, arreglo):
  retarreglo = []
  for x in arreglo:
    if(f(x)):
      retarreglo.append(x)
  return retarreglo
  
def quitarRepetidos(arr):
  retarr = []
  for a in arr:
    if(retarr.count(a)==0):
      retarr.append(a)
  return retarr
  
def reduce(vi, f, arreglo):
  vf = vi
  for x in arreglo:
    vf = f(vf, x)
  return vf

def copy(arr):
  retarr = []
  for x in arr:
    retarr.append(x)
  return retarr