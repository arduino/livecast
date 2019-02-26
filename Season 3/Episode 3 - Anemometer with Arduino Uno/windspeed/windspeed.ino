/*
    Wind speed + LCD example
  
    Using an anemometer to measure wind speed in m/s.
    The wind speed is then displayed on a LCD

    (c) 2019 Karl, Josefine & David for Arduino

    based on code by Joe Burg (c) 2014

*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double x = 0;
double y = 0;
double a = 0;
double b = 0;

int windSensor = A1;
float voltageMax = 2.0;
float voltageMin = .4;
float voltageConversionConstant = .004882814;
float sensorVoltage = 0;

float windSpeedMin = 0;
float windSpeedMax = 32;

int windSpeed = 0;
int prevWindSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(windSensor);

  float voltage = sensorValue * (5.0 / 1023.0);

  sensorVoltage = sensorValue * voltageConversionConstant;



  if (sensorVoltage <= voltageMin) {
    windSpeed = 0; //Check if voltage is below minimum value. If so, set wind speed to zero.
  } else {
    windSpeed = ((sensorVoltage - voltageMin) * windSpeedMax / (voltageMax - voltageMin)) * 2.232694; //For voltages above minimum value, use the linear relationship to calculate wind speed.
  }

  x = windSpeed;
  if (x >= y) {
    y = x;
  } else {
    y = y;
  }

  //Max voltage calculation

  a = sensorVoltage;
  if (a >= b) {
    b = a;
  } else {
    b = b;
  }
  if (windSpeed != prevWindSpeed) {
    Serial.println(windSpeed);
    Serial.println(sensorVoltage);
    prevWindSpeed = windSpeed;
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Wind Speed ");
  lcd.setCursor(12, 0);
  lcd.print(windSpeed);
  lcd.print(" ");
  lcd.setCursor(11, 2);
  lcd.print("m/s");
  delay(100);
}
