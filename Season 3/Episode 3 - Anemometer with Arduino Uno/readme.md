# Episode 3 - Anemometer with Arduino
This example will show how to use an anemometer to measure windspeed using an Arduino UNO. 


## Ingredients
- Arduino UNO
- Breadboard
- 1x Anemometer
- 1x Potentiometer
- 1x LCD display
- 9V battery
- Jumper wires



## Wiring
 *Connect the wires and components according to the fritzing below.*
![alt text](https://github.com/arduino/livecast/raw/master/Season%203/Episode%203%20-%20Anemometer%20with%20Arduino%20Uno/S03E03_Fritzing.png "Logo Title Text 1")



## Code

```sh
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

```

## Start using

After wiring and uploading the code, we can now start using the Anemometer. If everything is wired accordingly, spinning it will start printing the current m/s on the LCD screen. You can now find a suitable spot for the anemometer outside (perhaps start with outside the window) and see what kind of winds are passing through. The anemometer itself is supposed to be air and water proofed, but make sure the Arduino and the circuit is in a dry location to not damage any components.


## Outcome

This is a part of our weather station series, where we use different components to see the weather conditions locally. This example shows how the voltage output from the anemometer is transformed into something that we can make sense out of, such as m/s, km/h or mph. The data we collect can also be used over a longer period of time through various extensions, where you can monitor how the wind has been for the past week for e.g. 


