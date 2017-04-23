import picamera
import picamera.array
from PIL import Image
import numpy as np

with picamera.PiCamera() as camera:
    while True:
        with picamera.array.PiRGBArray(camera) as output:
            #camera.resolution = (340,340)
            camera.capture(output, 'rgb')
            print('Capturada  %dx %d imagen'%(output.array.shape[1], output.array.shape[0]))
            matriz = output.array
            #Image.fromarray(matriz.astype(np.uint8)).save("prueba5.jpg")
            
