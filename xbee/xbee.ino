#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(2,3); //RX, TX

//PAN ID
//http://wiblocks.luciani.org/docs/app-notes/zb1-lcd2-txrx.html
#define XB_PAN_ID              "ATID1111\r" //defined new PAN ID

String myName = "Gentry";
int potentiometer; //my potentiometer
int incomingPotValue; //for storing the recieved potentiometer value
int fadeValue; //LED PWM
boolean button; 
int RedLED; //
int GreenLED; //
int brightness; //
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  brightness = 0;
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(button, INPUT);
  
}



void loop() {
  // put your main code here, to run repeatedly:
  potentiometer = analogRead(A0);
  button = digitalRead(7);
  
  Serial.println(potentiometer);

  if(Serial.available() > 0){
    incomingPotValue = Serial.read();
    analogWrite(GreenLED, incomingPotValue/4);
  }

  if(button) {
    xbeeSerial.println(myName);
    xbeeSerial.println(potentiometer + "/n");
  }
  }
  

