void configNetwork (int mode) {
  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    if (mode == SCREEN || BOTH) tft.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    if (mode == SCREEN || BOTH) tft.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    if (mode == SCREEN || BOTH) tft.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the status:
  printWiFiStatus(mode);
}

void configRTC (int mode) {
  rtc.begin();

  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries > maxTries) {
    Serial.print("NTP unreachable!!");
    if (mode == SCREEN || BOTH) tft.print("NTP unreachable!!");
    while (1);
  }
  else {
    Serial.print("Epoch received: ");
    if (mode == SCREEN || BOTH) tft.print("Epoch received: ");
    Serial.println(epoch);
    if (mode == SCREEN || BOTH) tft.println(epoch);
    rtc.setEpoch(epoch);

    Serial.println();
  }
}

void configDisplay () {
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

  tft.setRotation(3);  // to place the screen image in the expected direction
}

void printTime(int mode, boolean current = true)
{
  if (current) print2digits(currTime[0] + GMT, mode);
  else print2digits(prevTime[0] + GMT, mode);

  if (mode == SERIAL || mode == BOTH) Serial.print(":");
  if (mode == SCREEN || mode == BOTH) tft.print(":");

  if (current) print2digits(currTime[1], mode);
  else print2digits(prevTime[1], mode);

  if (mode == SERIAL || mode == BOTH) Serial.print(":");
  if (mode == SCREEN || mode == BOTH) tft.print(":");

  if (current) print2digits(currTime[2], mode);
  else print2digits(prevTime[2], mode);

  if (mode == SERIAL || mode == BOTH) Serial.println();
  if (mode == SCREEN || mode == BOTH) tft.println();
}

void deleteTime(int mode, boolean current = true, int howDiff = -1)
{
  if (current) print2digits(currTime[0] + GMT, mode);
  else if (howDiff == 0)
    print2digits(prevTime[0] + GMT, mode);
  else tft.print("  ");

  if (mode == SERIAL || mode == BOTH) Serial.print(":");
  if (mode == SCREEN || mode == BOTH) tft.print(":");

  if (current) print2digits(currTime[1], mode);
  else if (howDiff == 0 || howDiff == 1)
    print2digits(prevTime[1], mode);
  else tft.print("  ");

  if (mode == SERIAL || mode == BOTH) Serial.print(":");
  if (mode == SCREEN || mode == BOTH) tft.print(":");

  if (current) print2digits(currTime[2], mode);
  else if (howDiff != -1)
    print2digits(prevTime[2], mode);

  if (mode == SERIAL || mode == BOTH) Serial.println();
  if (mode == SCREEN || mode == BOTH) tft.println();
}

void printDate(int mode)
{
  if (mode == SERIAL || mode == BOTH) {
    Serial.print(rtc.getDay());
    Serial.print("/");
    Serial.print(rtc.getMonth());
    Serial.print("/");
    Serial.print(rtc.getYear());

    Serial.print(" ");
  }

  if (mode == SCREEN || mode == BOTH) {
    tft.print(rtc.getDay());
    tft.print("/");
    tft.print(rtc.getMonth());
    tft.print("/");
    tft.println(rtc.getYear());
  }
}


void printWiFiStatus(int mode) {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  if (mode == SCREEN || mode == BOTH) tft.print("SSID: ");
  Serial.println(WiFi.SSID());
  if (mode == SCREEN || mode == BOTH) tft.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  if (mode == SCREEN || mode == BOTH) tft.print("IP Address: ");
  Serial.println(ip);
  if (mode == SCREEN || mode == BOTH) tft.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  if (mode == SCREEN || mode == BOTH) tft.print("signal strength (RSSI):");
  Serial.print(rssi);
  if (mode == SCREEN || mode == BOTH) tft.print(rssi);
  Serial.println(" dBm");
  if (mode == SCREEN || mode == BOTH) tft.println(" dBm");
}

void print2digits(int number, int mode) {
  if (number < 10) {
    if (mode == SERIAL || mode == BOTH) {
      Serial.print("0");
    }
    if (mode == SCREEN || mode == BOTH) {
      tft.print("0");
    }
  }
  if (mode == SERIAL || mode == BOTH) {
    Serial.print(number);
  }
  if (mode == SCREEN || mode == BOTH) {
    tft.print(number);
  }
}

unsigned long timeToDisplay(int mode) {
  unsigned long start = micros();
  //tft.fillRect(0, 24, 6 * 8 * 2, 7 * 2, ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  printDate(mode);
  tft.setCursor(0, 24);
  tft.setTextColor(ILI9341_BLACK); tft.setTextSize(2);
  deleteTime(mode, false, howDifferentTime());
  tft.setCursor(0, 24);
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  printTime(mode);
}

void getCurrentTime() {
  currTime[0] = rtc.getHours();
  currTime[1] = rtc.getMinutes();
  currTime[2] = rtc.getSeconds();
}

void copyTime() {
  prevTime[0] = currTime[0];
  prevTime[1] = currTime[1];
  prevTime[2] = currTime[2];
}

boolean isDifferentTime() {
  boolean itIs = false;
  for (int i = 0; i < 3; i++)
    if (prevTime[i] != currTime[i])
      itIs = true;
  return itIs;
}

int howDifferentTime() {
  int is = -1;
  // go backwards, biggest time is most significant
  for (int i = 2; i >= 0; i--)
    if (prevTime[i] != currTime[i])
      is = i;
  return is;
}

// this method makes a HTTP connection to the server:
void httpRequest(int mode) {
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /arduinoSpace/test.html HTTP/1.1");
    client.println("Host: cuartielles.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    if (mode == SCREEN || mode == BOTH)
      tft.println("connection failed");
    if (mode == SERIAL || mode == BOTH)
      Serial.println("connection failed");
  }
}

