#include "FastLED.h"
//#include <SPI.h>
#include <SD.h>

#define NUM_LEDS 51
#define NUM_COLS 68
#define NUM_COLORS 3
#define BRIGHTNESS 25
#define dataline 3
#define chipselect 10
CRGB leds[NUM_LEDS];

File myFile;

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port. 
  LEDS.addLeds<PL9823, dataline>(leds, NUM_LEDS);
//  LEDS.addLeds<WS2812B, dataline, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
//  for (int p=0;p< NUM_LEDS;p++){
//    leds[p] = CRGB::Black;  
//    FastLED.show();
  }

  if (!SD.begin(chipselect)) {
    Serial.println("initialization failed!");
    while (1);
  }
  // remove previous image and debug files
  SD.remove("LEDtest.txt");
  SD.remove("Debug.txt");
}

int serialReadBlocking() {
  while (!Serial.available()) {}
  int value = 0;
  value = Serial.read();
  return value;
}

void serialReadBlocking(int values[])
{
  for (int i = 0; i < 3; i++)
  {
    while (!Serial.available()) {}
    values[i] = Serial.read();
  }
}

void loop() {
  int values[NUM_COLORS] = {0, 0, 0};
  bool done = false;
  int num_inputs = 0;

  // open the file
  myFile = SD.open("LEDtest.txt", FILE_WRITE);
  
  // get the picture from the serial line.
  while (!done)
  {
    // block until a 1 is received.
//    while (serialReadBlocking() != 1) {}
     
    for (int i=0; i < NUM_LEDS; i++) 
    {
      serialReadBlocking(values);

      if (values[0] == 0 && values[1] == 1 && values[2] == 2) // receive a flag to end loop.
      {
        done = true;
        break;
      }

      // print the values read fromt the serial port to the SD card.
      if (myFile)
      {
        myFile.println(values[0]);
        myFile.println(values[1]);
        myFile.println(values[2]);
      }
      num_inputs++;
    }
  }

  int totalSize = NUM_LEDS * NUM_COLS;
  if (myFile)
  {
    // Fill in the rest of the file with 1's to fit the needed array size.
    while (num_inputs < (totalSize))
    {
      myFile.println(1);
      myFile.println(1);
      myFile.println(1);
      num_inputs++;
    }
    // close the file
    myFile.close();
  }


  myFile = SD.open("Debug.txt", FILE_WRITE);
  if (myFile)
  {
    myFile.println("Finished  writing");
    myFile.close();
  }


  myFile = SD.open("LEDtest.txt");
  // display the picture.
  while(1)
  {
    myFile.seek(0);
    if (myFile)
    {
      for(int j = 0; j < NUM_COLS; j++)
      {
        for(int i = 0; i < NUM_LEDS; i++)
        {
          int red = myFile.parseInt();
          int green = myFile.parseInt();
          int blue = myFile.parseInt();
          leds[i].setRGB(red, green, blue);
        }
        FastLED.show();
      }
    }
  }
  if (myFile)
  {
    myFile.close();
  }
}
