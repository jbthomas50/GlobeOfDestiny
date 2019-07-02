#include "FastLED.h"
#include <SPI.h>
#include <SD.h>

#define NUM_LEDS 51
const int dataline = 3;
const int chipselect = 10;
CRGB leds[NUM_LEDS];

File myFile;

//int colorArray[51][3] = {{177, 18, 18}, {177, 18, 18}, {177, 18, 18}, {177, 18, 18}, {177, 18, 18}, {177, 18, 18}, {138, 14, 14},{81, 8, 8},{44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},
//                         {44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},{92, 9, 9},{160,16,16},{176,18,18},{177, 18, 18},{177, 18, 18},{177, 18, 18},{177, 18, 18},{255, 255, 255},
//                         {177, 18, 18},{177, 18, 18},{177, 18, 18},{177, 18, 18},{177, 18, 18},{176, 18, 18},{160, 16, 16},{112, 11, 11},{64, 6, 6},{44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},{44, 5, 5},
//                         {44, 5, 5},{44, 5, 5},{66,7,7},{134,14,14},{172,18,18},{177,18,18},{177,18,18},{177,18,18},{177,18,18},{177,18,18},{255,255,255}};

void setup() {
  Serial.begin(115200); 
  LEDS.addLeds<WS2812B, dataline, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  for (int p=0;p< NUM_LEDS;p++){
    leds[p] = CRGB::Black;  
    FastLED.show();
  }

  if (!SD.begin(chipselect)) {
    Serial.println("initialization failed!");
    while (1);
  }
}

// Helper macro to merge 4 bytes
#define TO_INT32(a,b,c,d) (((d)<<24)|((c)<<16)|((b)<<8)|(a))
int32_t read_int()
{
  uint32_t result[4];
  for (int i = 0; i < 4; i++) {
    // Wait for data at the port
    while (!Serial.available());
    result[i] = Serial.read();
  }
  return TO_INT32(result[0], result[1], result[2], result[3]);
}

int serialReadBlocking() {
  while (!Serial.available()) {}
  int value = 0;
  do{
    value = Serial.read();
  }
  while (value == ' ');
  return value;
}

void serialReadBlocking(int32_t values[]) {
  while (!Serial.available()) {}
  for (int i = 0; i < 3; i++)
  {
    values[i] = read_int();
  }
}

void loop() {
  int32_t values[3] = {0, 0, 0};
  while (serialReadBlocking() != 1) {} 
  for (long i=0; i < NUM_LEDS; i++) {
//    leds[i].r = serialReadBlocking();
//    leds[i].g = serialReadBlocking();
//    leds[i].b = serialReadBlocking();
    serialReadBlocking(values);
//    colorArray[i][0] = values[0];
//    colorArray[i][1] = values[1];
//    colorArray[i][2] = values[2];
    myFile = SD.open("LEDtest.txt", FILE_WRITE);
    if (myFile)
    {
      myFile.print(values[0]);
      myFile.print(' ');
      myFile.print(values[1]);
      myFile.print(' ');
      myFile.println(values[2]);
      myFile.close();
    }
    leds[i].setRGB(values[0], values[1], values[2]);
   }
//  for(int i = 0; i < NUM_LEDS; i++)
//  {
//    leds[i].setRGB(colorArray[i][0], colorArray[i][1], colorArray[i][2]);
//  }
  FastLED.show();
}
