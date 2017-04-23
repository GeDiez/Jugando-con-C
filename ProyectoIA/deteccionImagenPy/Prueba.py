from Lib import imagen as im
from Lib import Matriz as matriz
import ochoVecinos as ov

#Convertimos una imagen a una matriz binaria
matrizRGB = im.getMatrixImagen('imagenes/prueba5.jpg')
B = im.toBinario(matrizRGB)
#Segementamos la imagen Binaria por objetos para recnocer objetos
mE = ov.etiquetar(B)
#obtenemos los objetos dentro de una imagen con su area
OAP = ov.cuentaObjetos(mE)
#calculamos el perimetro de cada objeto
OAP, mE, B = ov.perimetro(mE, OAP, B)
im.matrizToImagen(B, 'bn.jpg')
#OAP es un arreglo que contiene sub arreglos, con la siguient informacion
# OAP = [ [x1, x2, x3], [x1, x2, x3] ...]
## x1 es la etiqueta que identifica a un objeto dentro de la imagen
## x2 es el Area de dicho objeto (suma de todos los pixeles)
## x3 es el perimetro del objeto en pixeles

#obtenemos la opacidad del objeto con la formula k = (0.28 * perimetro )/area
for i in OAP:
  print ov.compacidad(i)


#_------- Reconocimiento con camara
