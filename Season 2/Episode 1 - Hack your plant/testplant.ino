/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

int potPin = A0;    // select the input pin for the potentiometer
//int ledPin2 = 2 ;   // select the pin for the LED
int ledPin3 = 3;   // select the pin for the LED
//int ledPin4 = 4;   // select the pin for the LED
int ledPin5 = 5;   // select the pin for the LED
//int ledPin6 = 6;   // select the pin for the LED
int ledPin7 = 7;   // select the pin for the LED

int val = 0;       // variable to store the value coming from the sensor

void setup() {
 // pinMode(ledPin2, OUTPUT);  // declare the ledPin as an OUTPUT
   pinMode(ledPin3, OUTPUT);  // declare the ledPin as an OUTPUT
   // pinMode(ledPin4, OUTPUT);  // declare the ledPin as an OUTPUT
     pinMode(ledPin5, OUTPUT);  // declare the ledPin as an OUTPUT
  //    pinMode(ledPin6, OUTPUT);  // declare the ledPin as an OUTPUT
       pinMode(ledPin7, OUTPUT);  // declare the ledPin as an OUTPUT
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  Serial.println(val);

//red
  if(val > 900 && val < 1023) {
  digitalWrite(ledPin3, HIGH);  // turn the ledPin on
  }
  else {digitalWrite(ledPin3, LOW);}

//orange
  if(val > 501 && val < 899) {
  digitalWrite(ledPin5, HIGH);  // turn the ledPin on
  }
  else {digitalWrite(ledPin5, LOW);}

//green
  if(val > 0 && val < 500) {
  digitalWrite(ledPin7, HIGH);  // turn the ledPin on
  }
  else {digitalWrite(ledPin7, LOW);}                 
}
