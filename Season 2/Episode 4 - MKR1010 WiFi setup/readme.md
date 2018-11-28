# Episode 4 - MKR1010 WiFi setup 
In this example we will host a webserver on the Arduino board which we can interact with over the phone or computer. With the help of this, we can turn an LED on/off, make an LED blink and turn a servo left and right from an interface that you can access on your phone or computer.

You can watch this project being done by David Cuartielles, the co-founder of Arduino, by clicking into this link: https://www.youtube.com/watch?v=H0p7GVPdlyU&t=1150s



## Ingredients
- Arduino MKR1010 board
- 2x LEDs
- 1x servo
- Jumper wires 


## Wiring
##### Connect the wires and components according to the fritzing below.
![alt text](https://github.com/arduino/livecast/raw/master/Season%202/Episode%204%20-%20MKR1010%20WiFi%20setup/MKR1010_config/episode4_fritzing.png "Logo Title Text 1")



## Code

```sh

/*
   MKR1010 WiFi setup.
   
   Control LEDs and a servo with your phone/computer
   over local WiFi.
   
   (c) 2018 Karl, Josefine and David for Arduino.
   
   based on code by (c) m.ehrndal, Arduino LLC.2013-2016
*/

//libraries
#include <SPI.h>
#include <WiFiNINA.h>
#include <Servo.h> 

char ssid[] = "";             //  your network SSID (name) between the " "
char pass[] = "";      // your network password between the " "
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;      //connection status
WiFiServer server(80);            //server socket

//special characters
char quote = '"';
char slash = '/';

Servo myservo;

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(6, OUTPUT);      // set the LED pin mode
  pinMode(7, OUTPUT);      
  myservo.attach(9);      
  myservo.write(45);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
}


void loop() {

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.println("<!DOCTYPE HTML>");
            client.print("<head>");
            client.print("<link rel=");
            client.print(quote);
            client.print("stylesheet");
            client.print(quote);
            client.print("href=");
            client.print(quote);
            client.print("https://ioio.mah.se/courses/IDK17/student_0007/mkrsheet.css");  //NOTE: link to your own css stylesheet here
            client.print(quote);
            client.print(slash);
            client.print (">");
            client.print("</head>");
            client.print("<body>");
            client.println("<center><br><br><div class='container'><h1>CONTROL YOUR ARDUINO<h1/></div></center>");
            client.println("<center><div class='container'><left><button class='on' type='submit' value='ON' onmousedown=location.href='/H\'>ON</button>");
            client.println("<button class='off' type='submit' value='OFF' onmousedown=location.href='/L\'>OFF</button></div><br>");
            client.println("<button class='blink' type='submit' value='BLINK' onmousedown=location.href='/X\'>BLINK</button></div>");
            client.println("<button class='left' type='submit' value='>' onmousedown=location.href='/Y\'>LEFT</button></div>");
            client.println("<button class='right' type='submit' value='<' onmousedown=location.href='/P\'>RIGHT</button></div>");  
            client.println("</body>");
            client.println("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L" or "GET /X":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(7, HIGH);               // GET /H turns the pin 6 LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(7, LOW);                // GET /L turns the pin 6 LED off
        }
         if (currentLine.endsWith("GET /P")) {
           myservo.write(40);           // GET /P turns the servo to 45
        }
         if (currentLine.endsWith("GET /Y")) {
          myservo.write(30);               // GET /Y turns servo to 90
        }
        if (currentLine.endsWith("GET /X")) {
          digitalWrite(6, HIGH);                // GET /L turns the pin 6 LED off
          delay(500);
          digitalWrite(6, LOW);
          delay(500);
          digitalWrite(6, HIGH);
          delay(500);
          digitalWrite(6, LOW);
          delay(500);
          digitalWrite(6, HIGH);
          delay(500);
          digitalWrite(6, LOW);
        }

        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}



```

## Start using

After wiring and uploading the code, we can now access the MKR1010. The board attempts to connect to the WiFi, which you can follow in the Serial Monitor. Once it is connected, it will provide an ip address. Copy this link and access it through your computer and phone. You will then get an interface with a few buttons that you can interact with. The stylesheet is not hosted on Arduino, it is grabbed from an external source. 


## Outcome

We have in this example managed to control an Arduino MKR1010 over the local WiFi, and from here we can try out different components that we can control remotely. The MKR1010 no longer has to be connected to the computer and can be accessed from anywhere, as long as it has power and is within reach of the local WiFi. 



