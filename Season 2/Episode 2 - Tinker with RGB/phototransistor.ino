
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
