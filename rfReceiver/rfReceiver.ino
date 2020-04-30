/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include <SPI.h>
#include "RF24.h"

#define button 4

RF24 NRF24L01 (7, 8);//create object called NRF24L01. specifying the CE and CSN pins to be used on the Arduino

byte address[] [6] = {"pipe1", "pipe2"};//set addresses of the 2 pipes for read and write
boolean buttonState = false;//used for both transmission and receive

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println("Debug Serial setup OK");

  NRF24L01.begin();
  //open the pipes to read and write from board 1
  //NRF24L01.openWritingPipe(address[0]);//open writing pipe to address pipe 1
  //NRF24L01.openReadingPipe(1, address[1]);//open reading pipe from address pipe 2

  NRF24L01.openReadingPipe(1, address[0]);//open reading pipe from address pipe 1
  NRF24L01.openWritingPipe(address[1]);//open writing pipe to address pipe 2

  NRF24L01.setPALevel(RF24_PA_MAX);//set RF power output to minimum, RF24_PA_MIN (change to RF24_PA_MAX if required)
  NRF24L01.setDataRate(RF24_250KBPS);//set data rate to 250kbps
  NRF24L01.setChannel(110);//set frequency to channel 110  
  Serial.println("NRF24L01 setup OK");
  
}

void loop() {
  //Transmit button change to the other Arduino
  delay(10);
  NRF24L01.stopListening();
//  buttonState = digitalRead(button);//test for button press on this board
//  if (buttonState == LOW)//button is pulled up so test for LOW
//  {
//    NRF24L01.write(&buttonState, sizeof(buttonState));//send LOW state to other Arduino board
//    //flash the yellow LED to show progress
//    //Serial.println("confirmLed HIGH");
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(100);
//    digitalWrite(LED_BUILTIN, LOW);
//    //Serial.println("LED_BUILTIN LOW");
//  }

  buttonState = HIGH;//reset the button state variable

  //Receive button change from the other Arduino
  delay(10);
  NRF24L01.startListening();
  if (NRF24L01.available())//do we have transmission from other Arduino board
  {
    NRF24L01.read(&buttonState, sizeof(buttonState));//update the variable with new state
    NRF24L01.stopListening();
  }
  if (buttonState == HIGH)//test the other Arduino's button state
  {
    //digitalWrite(led, LOW);
    Serial.println("waiting");
  }
  else
  {
    flashLed();//indicate that the button was pressed on the other board
  }
  buttonState = HIGH;//reset the button state variable
}

//flash the red LED five times
void flashLed()
{
  for (int i = 0; i < 5; i++)
  {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("LED ON");
  delay(50);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("LED OFF");
  delay(1000);  
  }
}
