/*
    Digital Humidity & Temperature Sensor (DHT)
    that prints the values of the DHT on an
    LCD screen.

    (c) 2018 Karl, Josefine & David for Arduino

    based on code by ThothLoki (c) 2016

*/

#include <LiquidCrystal.h>
#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8

//define LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  //starts LCD
  lcd.begin(16, 2);
  //starts DHT
  dht.begin();
  
  lcd.print("Temp:    Humid:");
}

void loop() {
  delay(500);
  
  //set location of where text will begin
  lcd.setCursor(0, 1);
  
  // reads humidity
  float h = dht.readHumidity();
  
  //reads temperature (celsius)
  float c = dht.readTemperature();
  
  //reads temperature (fahrenheit)
  float f = dht.readTemperature(true);

  
  if (isnan(h) || isnan(c)) {
    lcd.print("ERROR");
    return;
  }
  //prints temperature. to display fahrenheit, replace 'c' with an 'f'
  lcd.print(c);
  lcd.setCursor(9,1);
  //prints humidity
  lcd.print(h);

  
}
