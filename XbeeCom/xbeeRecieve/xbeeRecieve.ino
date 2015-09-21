/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of xbee)
 * TX is digital pin 3 (connect to RX of xbee)
*/
//  showing an LED breathing effect

int pin = 5;
int intensity = 0;
int meter = 3;
int brighter = true; // are we incrementing or decrementing 


int num;

#include <SoftwareSerial.h>

SoftwareSerial Xbee(2, 3); // RX, TX


void breathe() {
  if (brighter)
    intensity++;
  else
    intensity--;
    
  if (intensity > 255) { // check upper bound
    intensity = 255;
    brighter = !brighter; // change direction
  } 
  
  if (intensity < 0) { // check lower bound
    intensity = 0;
    brighter = !brighter; // change direction
  }
  
  analogWrite(pin, intensity);
  delay(meter); 
}

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Broadcasting your name.  See if others receive it.");

  // set the data rate for the SoftwareSerial port
  Xbee.begin(9600);
  Xbee.println("Hello, world? This is YOURNAMEHERE");
}

void loop() // run over and over
{
 // if (mySerial.available())
   // Serial.write(mySerial.read());
 // if (Serial.available())
    //mySerial.write(Serial.read()) = num;
    //Serial.println(num);
  if (Xbee.available())
  {
    num = Xbee.read();
    Serial.write(num);
    Serial.println(num);
}

breathe();

meter = num;
}
