/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define button 4
#define led 5

#define BUTTON_BLUE
//#define BUTTON_GREEN
//#define BUTTON_RED
//#define BUTTON_YELLOW

#ifdef BUTTON_BLUE
const byte address[6] = "00001";
const char text[] = "BUTTON_BLUE";
#endif

#ifdef BUTTON_GREEN
const byte address[6] = "00002";
const char text[] = "BUTTON_GREEN";
#endif

#ifdef BUTTON_RED
const byte address[6] = "00003";
const char text[] = "BUTTON_RED";
#endif

#ifdef BUTTON_YELLOW
const byte address[6] = "00004";
const char text[] = "BUTTON_YELLOW";
#endif

RF24 radio(7, 8); // CE, CSN

int counter = 0;
boolean buttonState = false;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  digitalWrite(led, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  #ifdef BUTTON_BLUE
  Serial.println("Blue Button started");
  #endif
  #ifdef BUTTON_GREEN
  Serial.println("Green Button started");
  #endif  
  #ifdef BUTTON_RED
  Serial.println("Red Button started");
  #endif 
  #ifdef BUTTON_YELLOW
  Serial.println("Yellow Button started");
  #endif
}

void loop() {
  buttonState = digitalRead(button);//test for button press on this board
  if (buttonState == LOW)//button is pulled up so test for LOW
  {
    radio.write(&text, sizeof(text));
    delay(10);
    Serial.println("Trasmission");
    Serial.println(text);
    Serial.println(counter);
    counter ++;
    digitalWrite(led, HIGH);
  }  
}
