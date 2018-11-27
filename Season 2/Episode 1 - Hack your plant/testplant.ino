/* Analog Read to LED
   ------------------

   turns on and off a light emitting diode(LED) connected to digital
   pin 13. The amount of time the LED will be on and off depends on
   the value obtained by analogRead(). In the easiest case we connect
   a potentiometer to analog pin 2.

   Created 1 December 2005
   copyleft 2005 DojoDave <http://www.0j0.org>
   http://arduino.berlios.de

*/

int potPin = A0;    // select the input pin for the potentiometer
int redLed = 2;   // select the pin for the LED
int yellowLed = 3;   // select the pin for the LED
int greenLed = 4;   // select the pin for the LED

int val = 0;       // variable to store the value coming from the sensor

void setup() {
  pinMode(redLed, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(yellowLed, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(greenLed, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  Serial.println(val); // print the value to set thresholds

  //red
  if (val >= 900 && val <= 1023) { //set your own thresholds dependent on values
    digitalWrite(redLed, HIGH);  // turn the ledPin on
  }
  else {
    digitalWrite(redLed, LOW);
  }

  //orange
  if (val >= 501 && val <= 899) { //set your own thresholds dependent on values
    digitalWrite(yellowLed, HIGH);  // turn the ledPin on
  }
  else {
    digitalWrite(yellowLed, LOW);
  }

  //green
  if (val > 0 && val <= 500) { //set your own thresholds dependent on values
    digitalWrite(greenLed, HIGH);  // turn the ledPin on
  }
  else {
    digitalWrite(greenLed, LOW);
  }
}
