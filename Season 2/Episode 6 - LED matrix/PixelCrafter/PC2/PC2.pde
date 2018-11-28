/*
  Pixel Crafter v0002
  
  (c) 2018 David Cuartielless for Arduino
 
 Uses ControlP5 for UI elements (but NOT color picker)
 Uses color picker code as found on the Processing forum: https://forum.processing.org/one/topic/processing-color-picker.html
 Uses AdvoCut font from Marc Andre Misman, (c) 2001
 Clipboard code from: https://forum.processing.org/one/topic/copy-and-paste.html#25080000001711515.html
 */

import controlP5.*;
import processing.serial.*;

boolean serialOn = false;

// UI elements that need to be declared here
UI ui;
ControlP5 cp5;
PFont font;

String ver = "v0001 alpha";

Serial myPort;

void setup() {
  size( 800, 730 );

  cp5 = new ControlP5(this);
  ui = new UI(30, 30);
  
  // font related code
  // Uncomment the following two lines to see the available fonts 
  //String[] fontList = PFont.list();
  //printArray(fontList);
  font = createFont("AdvoCut", 50);
  textFont(font);
  
  // include serial port
  if (serialOn) myPort = new Serial(this, "/dev/ttyACM0", 9600);
}

void draw() {
  background(200);
  ui.update();
}
