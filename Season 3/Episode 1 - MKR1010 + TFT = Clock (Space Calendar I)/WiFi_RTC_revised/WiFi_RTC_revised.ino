/*
  MKR 1010 / 1000 RTC over WiFi

  This sketch asks NTP for the Linux epoch and sets the internal Arduino MKR1000's RTC accordingly.

  created 08 Jan 2016
  by Arturo Guadalupi <a.guadalupi@arduino.cc>

  modified 26 Sept 2018

  revised 07 Jan 2019
  by D. Cuartielles

  based on:
  http://arduino.cc/en/Tutorial/WiFiRTC
  This code is in the public domain.
*/

#include <SPI.h>
//#include <WiFi101.h>
#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <RTCZero.h>

RTCZero rtc;

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

const int GMT = 2; //change this to adapt it to your time zone

void setup() {
  Serial.begin(115200);

  configNetwork();

  configRTC();
}

void loop() {
  printDate();
  printTime();
  Serial.println();
  delay(1000);
}


