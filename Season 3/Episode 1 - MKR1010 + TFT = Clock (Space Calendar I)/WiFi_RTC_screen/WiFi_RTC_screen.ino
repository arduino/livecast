/*
  MKR 1010 / 1000 RTC over WiFi

  This sketch asks NTP for the Linux epoch and sets the internal Arduino MKR1000's RTC accordingly.
  It then displays it on a TFT screen minimizing the flickering

  created 07 Jan 2019
  by D. Cuartielles

  based on:
    http://arduino.cc/en/Tutorial/WiFiRTC
    2016 by A. Guadalupi for Arduino
    graphicstest for the ILI9341
    by Limor Fried/Ladyada for Adafruit Industries

  This code is in the public domain.

*/

#include <SPI.h>
//#include <WiFi101.h>
#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <RTCZero.h>

// includes for screen
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// includes for local info
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
#include "arduino_secrets.h"

// screen pins (to display data)
#define TFT_DC 7
#define TFT_CS 5
#define TFT_MOSI 8
#define TFT_CLK 9
#define TFT_RST 6
#define TFT_MISO 10

// data modes
#define BOTH 1
#define SERIAL 2
#define SCREEN 3

RTCZero rtc;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

long timer = 0;
byte prevTime[] = {0, 0, 0};
byte currTime[] = {0, 0, 0};

const int GMT = 1; //change this to adapt it to your time zone

// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "cuartielles.com";

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 60L * 1000L; // delay between updates, in milliseconds

void setup() {
  Serial.begin(115200);

  configDisplay();

  tft.fillScreen(ILI9341_BLACK);

  configNetwork(BOTH);

  configRTC(BOTH);

  delay(5000);

  tft.fillScreen(ILI9341_BLACK);

  timer = millis(); // init time ticker
}

void loop() {
  getCurrentTime();

  if (isDifferentTime())
    timeToDisplay(BOTH);

  // if there is data coming in from the server, print it
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    tft.print(c);
  }

  // if XX seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(BOTH);
  }

  copyTime();
}


