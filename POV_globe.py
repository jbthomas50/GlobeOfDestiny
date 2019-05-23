#!/usr/bin/env python3

import time
import pigpio

pi = pigpio.pi()

pi.set_mode(18, pigpio.OUTPUT)

start = time.time()

while (time.time() - start) < 60.0:
    pi.write(18, 1) # on
    time.sleep(0.5)
    pi.write(18, 0) # off
    time.sleep(0.5)

pi.stop() # terminate connection and release resources
