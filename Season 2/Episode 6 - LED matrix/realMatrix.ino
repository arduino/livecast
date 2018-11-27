// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      256

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int buttonPin = 2;
int buttonPin2 = 3;
int buttonState = 0;
int buttonState2 = 0;

int red[] = { 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,
    0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,40,0,0,0,0,0,100,100,100,0,0,0,0,0,0,
    0,0,40,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,0,0,40,0,0,0,0,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,100,0,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,100,0,0,0,100,0,0,0,0,0,
    0,0,0,0,100,0,0,0,0,0,100,0,0,0,0,0,
    0,0,0,0,0,100,0,0,0,0,0,100,0,0,0,0,
    0,0,0,100,0,0,0,0,0,0,0,100,0,0,0,0,
    0,0,0,0,100,0,0,0,0,0,0,0,100,0,0,0,
    0,0,100,0,0,0,0,0,0,0,0,0,100,0,0,0,
    0,0,0,100,0,0,0,0,0,0,0,0,0,100,0,0,
    0,0,0,0,0,100,0,0,0,100,0,0,0,0,0,0,
    0,0,0,0,0,0,100,0,0,0,100,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

int green[] = { 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,
    0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,40,0,0,0,0,0,100,100,100,0,0,0,0,0,0,
    0,0,40,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,100,100,100,0,0,0,0,0,0,
    0,0,0,0,0,100,100,100,100,100,0,0,0,0,0,0,
    0,0,0,0,0,0,100,100,100,100,100,0,0,0,0,0,
    0,0,0,0,100,100,100,100,100,100,100,0,0,0,0,0,
    0,0,0,0,0,100,100,100,100,100,100,100,0,0,0,0,
    0,0,0,100,100,100,100,100,100,100,100,100,0,0,0,0,
    0,0,0,0,100,100,100,100,100,100,100,100,100,0,0,0,
    0,0,0,0,0,0,100,100,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,100,100,100,0,0,0,0,0,0,
    0,0,0,0,0,100,100,100,100,100,0,0,0,0,0,0,
    };


int blue[] = { 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,100,100,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,100,100,100,0,0,0,0,0,0,
    0,0,0,0,0,100,100,100,100,100,0,0,0,0,0,0,
    0,0,0,0,0,0,100,100,100,100,100,0,0,0,0,0,
    0,0,0,0,100,100,100,100,100,100,100,0,0,0,0,0,
    0,0,0,0,0,100,100,100,100,100,100,100,0,0,0,0,
    0,0,0,100,100,100,100,100,100,100,100,100,0,0,0,0,
    0,0,0,0,100,100,100,100,100,100,100,100,100,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };



void setup() {
  
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(buttonPin, INPUT);
}

void loop() {
  
 buttonState = digitalRead(buttonPin);
 buttonState2 = digitalRead(buttonPin2);

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one
 
  for(int i=0;i<NUMPIXELS;i++){

  if(buttonState == HIGH) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(red[i],green[i], 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}

if(buttonState2 == HIGH){
  pixels.setPixelColor(i, pixels.Color(0,0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}
   
  }

 
}
