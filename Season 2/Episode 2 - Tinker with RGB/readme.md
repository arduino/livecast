# Episode 2 - Tinker with RGB
This example will allow you to control an RGB LED with the help of a phototransistor. The phototransistor alters the current depending on how much light it receives, and gives out a value. With this we can map out what kind of colour the RGB led will have.


## Ingredients
- Arduino UNO
- 1x RGB LED
- 1x phototransistor
- 1x 220 ohm resistor
- Jumper wires 


## Wiring
 *Connect the wires and components according to the fritzing below.*
![alt text](https://github.com/arduino/livecast/raw/master/Season%202/Episode%202%20-%20Tinker%20with%20RGB/img/episode2_fritzing.png "Logo Title Text 1")



## Code

```sh

int photoPin = A0;
int photoValue = 0;
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;

void setup() {

  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  //stores the value of A0 in a variable
  photoValue = analogRead(photoPin);
  Serial.println(photoValue);

  //the following code will change the RGBs color depending on the value of the photoresistor
  
  //if we cover the photoresistor, the RGB will give a strange color
  if (photoValue >= 1 && photoValue <= 5) {
    analogWrite(redPin, (255, 255, 255));
    analogWrite(greenPin, (127, 127, 127));
    analogWrite(bluePin, (80 , 80, 80));
  }
  //if our hand gets close enough, the RGB will turn blue
  if (photoValue >= 6 && photoValue <= 12) {
    analogWrite(redPin, (0, 0, 0));
    analogWrite(greenPin, (0, 0, 0));
    analogWrite(bluePin, (255, 255, 255));
  }
  //if our hand is semi-far away, the RGB will turn green
  if (photoValue >= 13 && photoValue <= 20) {
    analogWrite(redPin, (0, 0, 0));
    analogWrite(greenPin, (255, 255, 255));
    analogWrite(bluePin, (0, 0, 0));
  }

  //if we do nothing, the RGB will stay red
  if (photoValue >= 21 && photoValue <= 50) {
    analogWrite(redPin, (255, 255, 255));
    analogWrite(greenPin, (0, 0, 0));
    analogWrite(bluePin, (0, 0, 0));
  }
  //if we use a flashlight on the photoresistor, the RGB will turn purple
  if (photoValue >= 50) {
    analogWrite(redPin, (255, 255, 255));
    analogWrite(greenPin, (0, 0, 0));
    analogWrite(bluePin, (255, 255, 255));
  }
  //we use a delay so the serial port doesn't get too busy
delay(100);
}

```

## Start using

After wiring and uploading the code, we can now start using this example. The thresholds set in the code, for e.g. **(photovalue >= 50)**, will trigger a function if the value is over 50. You can now make your own tresholds for the RGB to change accordingly.


## Outcome

This is a classic example of how an input and output works. What we have learned here is to grab a value from a specific sensor, create **if statements** to check if the value is within a certain parameter, and execute a function afterwards. We have also learned how RGB LEDs work and how we change its colour.



