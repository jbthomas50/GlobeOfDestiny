#include "FastLED.h"
#define NUM_LEDS 17
const int dataline = 3;
CRGB leds[NUM_LEDS];

void setup() {
Serial.begin(9600); 
LEDS.addLeds<WS2812B, dataline, GRB>(leds, NUM_LEDS);
       
for (int p=0;p< NUM_LEDS;p++){
leds[p] = CRGB::Black;  
FastLED.show();}
}

int serialReadBlocking() {
  int num = 0;
  int multiplier = 100;
  bool done = false;
  while (!done)
  {
    while (!Serial.available()) {}
    int tempNum = (Serial.read() - 48); 
    if (tempNum != -38 && tempNum != -16)
    {
      num += (tempNum * multiplier);
      multiplier /= 10;
    }
    else
    {
      done = true;
    }
  }
  
  return num;
  
}

void loop() {
  Serial.println("stopped");
while (serialReadBlocking() != 1) {} 
   Serial.println("starting");
   for (long i=0; i < NUM_LEDS; i++) {
     leds[i].r = serialReadBlocking();
     leds[i].g = serialReadBlocking();
     leds[i].b = serialReadBlocking();
   }
FastLED.show();
}
