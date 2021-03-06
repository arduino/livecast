# Episode 8 - Bluetooth Matrix Special
This example will show how we can control a LED matrix remotely through Bluetooth. With the help of PixelCrafter we can also draw whatever picture we want and have it appear on the LED matrix.


## Ingredients
- Arduino UNO
- 1x HC-06 Bluetooth module
- 1x LED Matrix
- Jumper wires
- Bluetooth serial application


## Wiring
 *Connect the wires and components according to the fritzing below.*
![alt text](https://github.com/arduino/livecast/raw/master/Season%202/Episode%208%20-%20Bluetooth%20Matrix%20Special/img/fritzing_episode8.png "Logo Title Text 1")



## Code

```sh

/*
    LED Matrix controlled through Bluetooth

    Control a NeoPixel LED matrix using a HC-06 
    Bluetooth module.

    Using arrays generated by PixelCrafter, made by
    (c) David Cuartielles, 2018 we create different screens
    that can be triggered through Bluetooth.

    (c) 2018 Karl, Josefine, and David for Arduino
    this code is GPLv3

    based on code by Mayoogh Girish (c) 2016

*/
#include <Adafruit_NeoPixel.h>

//includes the file we store the arrays in
#include "ledData.h"


#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6
#define NUMPIXELS      256



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//stores data
char data = 0;

void setup() {

  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  //check if we receive any data
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read incoming value and stores into data
    Serial.print(data);          //Prints value to serial monitor
    Serial.print("\n");
    
    //if data equals 1 the 'showImage()' function will execute every 1 second
    if (data == '1') {
      showImage();
      delay(1000);
      clearImage();
      delay(1000);
      showImage();
      delay(1000);
      clearImage();
      delay(1000);
      showImage();
      delay(1000);
      clearImage();
      delay(1000);
    }

    //if data equals 2 the 'showImage2()' function will execute every 1 second
    else if (data == '2')  {
      showImage2();
      delay(1000);
      clearImage();
      delay(1000);
      showImage2();
      delay(1000);
      clearImage();
      delay(1000);
      showImage2();
      delay(1000);
      clearImage();
      delay(1000);
    }

    //if data equals 3 the 'showImage3()' function will execute every 1 second
    else if (data == '3')  {
      showImage3();
      delay(1000);
      clearImage();
      delay(1000);
      showImage3();
      delay(1000);
      clearImage();
      delay(1000);
      showImage3();
      delay(1000);
      clearImage();
    }
  }
}


void showImage() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // since we are working with no external battery power,
    // we need to map the maximum values of the light intensity
    // to 100, to avoid taking too much current from the USB port
    byte red = map(palette[3 * ledPixels[i]], 0, 255, 0, 100);
    byte green = map(palette[3 * ledPixels[i] + 1], 0, 255, 0, 100);
    byte blue = map(palette[3 * ledPixels[i] + 2], 0, 255, 0, 100);
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }

  pixels.show();
}

void showImage2() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // since we are working with no external battery power,
    // we need to map the maximum values of the light intensity
    // to 100, to avoid taking too much current from the USB port
    byte red = map(palette2[3 * ledPixels2[i]], 0, 255, 0, 100);
    byte green = map(palette2[3 * ledPixels2[i] + 1], 0, 255, 0, 100);
    byte blue = map(palette2[3 * ledPixels2[i] + 2], 0, 255, 0, 100);
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }

  pixels.show();
}

void showImage3() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // since we are working with no external battery power,
    // we need to map the maximum values of the light intensity
    // to 100, to avoid taking too much current from the USB port
    byte red = map(palette3[3 * ledPixels3[i]], 0, 255, 0, 100);
    byte green = map(palette3[3 * ledPixels3[i] + 1], 0, 255, 0, 100);
    byte blue = map(palette3[3 * ledPixels3[i] + 2], 0, 255, 0, 100);
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }

  pixels.show();
}



//Clears the LED matrix
void clearImage() {
  for (int i = 0; i < NUMPIXELS; i++)
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  pixels.show();
}



```
## (!) Make sure to include the ledData.h file where we have stored the arrays
## Start using

After wiring and uploading the code, we now need to connect to the HC-06 module. Using a Bluetooth Serial Terminal app such as [this one](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en), we can now send commands to the Arduino through Bluetooth using our phone. In the code we have if statements that will trigger a certain picture on the LED matrix, depending on what number comes into the Arduino. If it receives for e.g. a "1" it will trigger showImage(), "2" will trigger showImage2() and so on. 


## Outcome

This is a very good example on how both use a LED matrix innovatively and how we can make a remote Arduino project. By making it wireless, the Arduino can be used anywhere within range of the Bluetooth. 


