#include <SoftwareSerial.h>


/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of xbee)
 * TX is digital pin 3 (connect to RX of xbee)
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1,0); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Broadcasting your name.  See if others receive it.");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world? This is Zanzie");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
    mySerial.write("sup bitch");
}
