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

int led_yell = 10;
int led_blue = 9;
int led_redd = 4;
int led_whit = 5;
int led_gree = 6;

int counter = 0;
char text[32] = "";
char winner[32] = "NO WIN";

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

  pinMode(led_yell, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_redd, OUTPUT);
  pinMode(led_whit, OUTPUT);
  pinMode(led_gree, OUTPUT);      

  digitalWrite(led_yell, LOW);
  digitalWrite(led_blue, LOW);  
  digitalWrite(led_redd, LOW);
  digitalWrite(led_whit, LOW);
  digitalWrite(led_gree, LOW);
}

void loop() {
  delay(100);
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    Serial.println("Received");
    Serial.println(text);
    Serial.println(counter);
    if (!strcmp(winner, "NO WIN"))
      strcpy(winner, text);
    Serial.println("Winner is:");
    Serial.println(winner);              
    counter ++;
    
    if (!strcmp(winner, "BUTTON_BLUE"))
      digitalWrite(led_blue, HIGH);      
    if (!strcmp(winner, "BUTTON_YELL"))
      digitalWrite(led_yell, HIGH);   
    if (!strcmp(winner, "BUTTON_REDD"))
      digitalWrite(led_redd, HIGH);      
    if (!strcmp(winner, "BUTTON_WHIT"))
      digitalWrite(led_whit, HIGH);         
    if (!strcmp(winner, "BUTTON_GREE"))
      digitalWrite(led_gree, HIGH);  

  }
}
