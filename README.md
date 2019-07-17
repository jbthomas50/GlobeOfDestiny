# POVGlobe
A POV Globe controlled by a raspberry pi and arduino.

The arduino uses the FastLED library to drive the LEDs.

Send data serially from the pi to the arduino.
We haven't been able to fine tune sending the data, so for now the arduino will save
the information sent from the pi to an SD card and will then read from the SD card in
order to display.

Pi processes pictures/video/internet input.
