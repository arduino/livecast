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
