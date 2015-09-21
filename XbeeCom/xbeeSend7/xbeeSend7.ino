/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of xbee)
 * TX is digital pin 3 (connect to RX of xbee)
*/

#include <SoftwareSerial.h>
#define XB_PAN_ID              "ATID3000\r"
#define XB_DESTINATION_ADDRESS "13A200, 40C90EAA\r"

char Name[] = "Gentry";
int potentiometer;
int incomingPotValue;
int fadeValue;

int buttonPin = 8;
int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
bool buttonOn;


int redLed;
int redLedState;
int greenLed;
int brightness;

int incomingByte;

String myName = "ZANZIE";

SoftwareSerial Xbee(3,2); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //Serial.println("Broadcasting your name.  See if others receive it.");
  // set the data rate for the SoftwareSerial port
  Xbee.begin(9600);
  
  //Xbee.println("Yo this is g dawg on the radio");
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonPin, INPUT);
  //Serial.println("This is " + myName);
  //Xbee.println("This is " + myName);
}

void loop() // run over and over
{
  //Serial.println(myName);
  potentiometer = analogRead(A0);
  potentiometer = map(potentiometer, 0,1023,2,31);

  int reading = digitalRead(buttonPin); // read the state of the switch into a local variable:
         // check to see if you just pressed the button
         // (i.e. the input went from LOW to HIGH),  and you've waited
         // long enough since the last press to ignore any noise:
         // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
         // reset the debouncing timer
      lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
              // whatever the reading is at, it's been there for longer
              // than the debounce delay, so take it as the actual current state:
              // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
          
                 // If data comes in from XBee, send it out to serial monitor
              //mySerial.listen();
              //if (mySerial.isListening()) {
               // incomingByte = Xbee.read();   
              //  Serial.println(incomingByte);     //This gives us Serial.read(Analog)
                Serial.println(potentiometer);
                Xbee.write(potentiometer);
                }
               // 
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                
            }
      }
     
    
    lastButtonState = reading;
}
