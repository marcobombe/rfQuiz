/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int counter = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Receiver started");
}

void loop() {
  delay(100);
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println("Received");
    Serial.println(text);
    Serial.println(counter);
    counter ++;
  }
}
