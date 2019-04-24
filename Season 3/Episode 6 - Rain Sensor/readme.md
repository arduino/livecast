# Episode 3 - Rain Sensor + DHT11 with Arduino
This example will show how to use a rain sensor and a DHT11 humidity & temperature sensor with an Arduino UNO.

You can watch this project being done by David Cuartielles, the co-founder of Arduino on YouTube.

[![Weather Station Project with D. Cuartielles](https://img.youtube.com/vi/phW2BzEDfKY/0.jpg)](https://www.youtube.com/watch?v=phW2BzEDfKY)

## Ingredients
- Arduino Uno
- Breadboard
- Jumper Wires
- DHT11 Sensor
- Rain Sensor
- Water Source (wet towel for e.g.)



## Wiring
 *Connect the wires and components according to the fritzing below.*
![alt text](https://github.com/arduino/livecast/raw/master/Season%203/Episode%206%20-%20Rain%20Sensor/fritzing_e4.png "Logo Title Text 1")



## Code

```sh
/* 
 Basic weather condition example, using a DHT11 humidity/temperature
 sensor and a rain sensor. To see the data we are using the serial
 monitor for an easy setup.

 (c) 2019 Karl, Josefine & David for Arduino

 based on code by Circuit Basics (c) 2015

*/

//include the DHT library
#include <dht.h>
dht DHT;

#define DHT11_PIN 7

// lowest and highest sensor readings:
const int minValue = 0;     // sensor minimum
const int maxValue = 1024;  // sensor maximum

void setup() {
  Serial.begin(9600);  
}
void loop() {
  
  //read the rain sensor on A0
	int readSensor = analogRead(A0);

  //here we convert the analog value to a simple range of 0-2.
  int change = map(readSensor, minValue, maxValue, 0, 2);

  //here we check the DHT11 sensor for the current humidity and temperature
  int chk = DHT.read11(DHT11_PIN);

  //prints the values in the serial monitor and adding some text to describe the value
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
	
//Below we use the values we get from the "change" int to print if it's raining or not 
//water on the sensor prints a 0
  if(change == 0) {
    Serial.println("it is raining");
  }

//no water on the sensor prints a 1
  if(change == 1) {
    Serial.println("no rain");
  }

  delay(5000);  // delay between reads
}

```

## Start using

After wiring and uploading the code, we can now start using this example. The DHT11 sensor will continuously measure the humidity and temperature of the environment it is in, while the rain sensor will measure whether the component is wet or not. In the code, we have converted the range of values (0-1023) of the sensor to a simple 0-2 range, just indicating if it is wet or not using a simple set of if statements. All three values (humidity, temperature & rain) will then be printed in the serial monitor every 5 seconds (as can be seen in the bottom of the code). 


## Outcome

This is a part of our weather station series, where we use different components to see the weather conditions locally. This example takes three important weather conditions, to get an overall view on how your local weather is. This project is best suitable for outdoors measurements, but it is good to try out indoors at first. This is a good example on how we measure both digital (DHT11 sensor) and analog (rain sensor), to collect data on your local environment. Instead of using the serial monitor as a visualization method, you can now think of other ways you want the data to be displayed, perhaps through a set of LEDs, an LCD screen or another actuator such as sound.

