from PIL import Image
from Lib import Matriz as mtx

VECINO1 = 0
VECINO2 = 1
VECINO3 = 2
VECINO4 = 3
VECINO5 = 4
VECINO6 = 5
VECINO7 = 6  
VECINO8 = 7

def getMatrixImagen(rutaImagen):
  I = Image.open(rutaImagen)
  imagenMatrix = mtx.new(I.size[0], I.size[1])
  for x in range(I.size[0]):
    for y in range(I.size[1]):
      imagenMatrix[x][y] = I.getpixel((x, y))
  return imagenMatrix
  
def ExtraerRGB(arrayImagenRGB):
    R = mtx.new(len(arrayImagenRGB), len(arrayImagenRGB[0]))
    G = mtx.new(len(arrayImagenRGB), len(arrayImagenRGB[0]))
    B = mtx.new(len(arrayImagenRGB), len(arrayImagenRGB[0]))
    for x in range(len(arrayImagenRGB)):
        for y in range(len(arrayImagenRGB[0])):
            R[x][y] = arrayImagenRGB[x][y][0]
            G[x][y] = arrayImagenRGB[x][y][1]
            B[x][y] = arrayImagenRGB[x][y][2]
    return R, G, B
    
def toEscalaGrises(arrayImagenRGB):
    R, G, B = ExtraerRGB(arrayImagenRGB)
    #GRISES = [range(I.size[1]) for i in range(I.size[0])]
    GRISES = mtx.new(len(arrayImagenRGB), len(arrayImagenRGB[0]))
    for x in range(len(arrayImagenRGB)):
        for y in range(len(arrayImagenRGB[0])):
            GRISES[x][y]= (R[x][y] + G[x][y] + B[x][y])/3
    return GRISES

def toBinario(arrayImagenRGB):
    eg = toEscalaGrises(arrayImagenRGB)
    BINARIA = mtx.new(len(arrayImagenRGB), len(arrayImagenRGB[0]))
    umbral = otsu(len(arrayImagenRGB)*len(arrayImagenRGB[0]), histograma(eg))
    print umbral
    pixaux = 0;
    for x in range(len(arrayImagenRGB)):
        for y in range(len(arrayImagenRGB[0])):
            pixaux = eg[x][y]
            if(pixaux<umbral):
                BINARIA[x][y] = 0
            else :
                BINARIA[x][y] = 255
    return BINARIA
    
def matrizToImagen(matriz, nombreDestino):
    I = Image.new('RGB', (len(matriz), len(matriz[0])))
    for x in range(I.size[0]):
        for y in range(I.size[1]):
            color = matriz[x][y]
            I.putpixel((x, y), (color, color, color))
    I.save(nombreDestino);

def otsu(totalPixels, histData):
  sum =0
  for i in range(0, 256):
    sum = sum + i*histData[i]
  sumB = 0
  wB = 0
  wF = 0
  varMax = 0
  threshold = 0
  for i in range(0,256):
    wB = wB + histData[i]
    if(wB==0):
      continue
    wF = totalPixels - wB
    if(wF==0):
      break
    sumB = sumB + i*histData[i]
    mB = sumB/wB
    mF = (sum-sumB)/wF
    varBetween = wB*wF*(mB-mF)*(mB-mF)
    if(varBetween > varMax):
      varMax = varBetween
      threshold = i
  return threshold
  
def histograma(arrEG):
  histograma = []
  for i in range(0,257):
    histograma.append(0)
  for x in arrEG:
    for y in x:
      histograma[y] = histograma[y]+1
  return histograma
  