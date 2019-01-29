# Episode 1 / Season 3 - MKR1010 + TFT = Clock 
This time we demo how to make a simple clock showing time, date, and the content from a website all at once. These TFT screens are not super speedy, therefore we made a system that cleans up just the area of the image that is going to be refreshed with new numbers.

In this episode we present three programs showing the process to include a way to get the time from the internet (an NTP server), keep the time ticking inside the MKR1010 thanks to the RTCzero library, displaying the time on a TFT screen, and downloading the content from a website as a first step to later build a calendar that will be getting events from the net.

You can watch this project being done by David Cuartielles, the co-founder of Arduino, by clicking into this link: https://youtu.be/bp7cSDMLxDk



## Ingredients
- Arduino MKR1010 board
- 2x buttons (not used in this episode, yet)
- 1x TFT screen
- Jumper wires 


## Wiring
##### Connect the wires and components according to the fritzing below.
![alt text](https://github.com/arduino/livecast/raw/master/Season%203/Episode%201%20-%20MKR1010%20+%20TFT%20=%20Clock%20(Space%20Calendar%20I)/img/s03e01_fritzing.png "Fritzing image of the design")

## Code

This week we present three programs:

* WiFi_RTC: this program will get the time from an NTP server and use it as a reference to count the time using the RTCzero library

* WiFi_RTC_revised: it does the same as the previous program, but in a slightly cleaner way, preparing the way to add the other functions to the calendar

* WiFi_RTC_screen: uses a couple of constants named BOTH / SERIAL / SCREEN to determine whether the data will sent through the serial port, or be shown on the TFT screen ... or both! 

## Outcome

This project is just the first step towards building a calendar that will count time left until the next relevant event. Build it and let us know how it went on the official Arduino Discord channel or on the Arduino Forum. 

## Next steps

We will be adding a JSON decoder to extract the relevant information from an online calendar made in PHP, and maybe even download an image from a server and display it on the screen together with the rest of the information.
