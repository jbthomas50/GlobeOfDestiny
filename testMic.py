import pigpio
import time

pi = pigpio.pi()
pi.set_mode(4, pigpio.INPUT)
start = time.time()
elaspedTime = 0;

while 1:
    value = pi.read(4)
    if value == 0:
        elaspedTime = time.time()-start
        print(elaspedTime / 200)
        start = time.time()
    while value == 0:
        value = pi.read(4)
    
#time it goes from 0 to 1
