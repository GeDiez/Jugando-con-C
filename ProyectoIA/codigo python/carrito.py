import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)
gpio.setup(7,gpio.OUT)
gpio.setup(11,gpio.OUT)
gpio.setup(13,gpio.OUT)
gpio.setup(15,gpio.OUT)

while True:
    gpio.output(13,False)
    gpio.output(15,False)
    time.sleep(2)
    while True:
        gpio.output(7,True)
        gpio.output(11,False)
        time.sleep(0.001)
        gpio.output(7,False)
        gpio.output(11,False)
        time.sleep(0.005)
