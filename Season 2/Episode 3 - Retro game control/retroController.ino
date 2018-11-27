#include "Keyboard.h"

//declaring button pins
const int buttonPin = 2;          
const int buttonPin1 = 3;
const int buttonPin2 = 4;   
const int buttonPin3 = 5;
const int buttonPin4 = 6;


int previousButtonState = HIGH; 
int previousButtonState1 = HIGH;
int previousButtonState2 = HIGH;
int previousButtonState3 = HIGH;
int previousButtonState4 = HIGH;



void setup() {
  //declare the buttons as input_pullup
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  

  Keyboard.begin();
}

void loop() {
  //checking the state of the button
  int buttonState = digitalRead(buttonPin);
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);
  
  
 //replaces button press with UP arrow
  if (buttonState == LOW && previousButtonState == HIGH) {
      // and it's currently pressed:
    Keyboard.press(218);
  }

  if (buttonState == HIGH && previousButtonState == LOW) {
      // and it's currently released:
    Keyboard.release(218);
  }
  
  //replaces button press with DOWN arrow
if (buttonState1 == LOW && previousButtonState1 == HIGH) {
      // and it's currently pressed:
    Keyboard.press(217);
  }

  if (buttonState1 == HIGH && previousButtonState1 == LOW) {
      // and it's currently released:
    Keyboard.release(217);
  }
  
  //replaces button press with RIGHT arrow
  if (buttonState2 == LOW && previousButtonState2 == HIGH) {
      // and it's currently pressed:
    Keyboard.press(215);
  }

  if (buttonState2 == HIGH && previousButtonState2 == LOW) {
      // and it's currently released:
    Keyboard.release(215);
  }
  
  //replaces button press with LEFT arrow
   if (buttonState3 == LOW && previousButtonState3 == HIGH) {
      // and it's currently pressed:
    Keyboard.press(216);
  }

  if (buttonState3 == HIGH && previousButtonState3 == LOW) {
      // and it's currently released:
    Keyboard.release(216);
  }
  
//replaces button press with SPACE BAR
if (buttonState4 == LOW && previousButtonState4 == HIGH) {
      // and it's currently pressed:
    Keyboard.press(32);
  }

  if (buttonState4 == HIGH && previousButtonState4 == LOW) {
      // and it's currently released:
    Keyboard.release(32);
  }

  //checking the previous state of the button
  
  previousButtonState = buttonState;
  previousButtonState1 = buttonState1;
  previousButtonState2 = buttonState2;
  previousButtonState3 = buttonState3;
  previousButtonState4 = buttonState4;

  
 
}

