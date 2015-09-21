#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(2, 3); // RX, TX

int statsBegin = 0;
int updSeconds = 10; // seconds between status updates

String myName;
int    myMoney;

// we have different message types to send or receive on the network
String stealMsgHdr  = "steal_msg ";   // a steal message
String bcastMsgHdr = "bcast_msg ";  // a broadcast message

char *verbs [] = {
  "nailed",
  "trashed",
  "humiliated",
  "taken",
  "played",
  "dishonored",
  "chagrined",
  "ripped",
  "punked",
  "crushed"
};

// When you enter the game or die you start here
void reBank () {

  Serial.print("Getting money in... ");
  for (int idx = 10; idx > 0; idx--) {
    Serial.print(idx);
    Serial.print(" ");
    delay(1000);
  }

  Serial.println("GO!!!");
  myMoney = 10;

  // clear the xbee buffer here if you don't want to store up hits while you reBank
}

// determine the next second boundary
unsigned long getNextSec() {
  unsigned long curSecond = millis()/(1000 * updSeconds); // seconds the Arduino has been on
  return ((curSecond + 1) * (1000 * updSeconds));
}

unsigned long nextSec = 0; // when the next second will be

void setup () {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  randomSeed(analogRead(0));

  rules();   // print the rules
  getName(); // get player name
  reBank();  // get starting ca$h

  xbeeSerial.println(bcastMsgHdr + myName + " has joined the game!"); // announce your presence
}

void loop () {
  if (millis() >= nextSec) { // If we cross the second boundary

    Serial.print("\nMy money: $");
    Serial.println(myMoney);
    Serial.println("");
    xbeeSerial.println(bcastMsgHdr + myName + " has $" + myMoney);  // update people on your fat stacks 

    updSeconds = constrain(myMoney, 2, 30); // the more money you have the less frequent you will update
    nextSec = getNextSec();  // Update timer for next second boundary
  } 
  else {
    serialCheck ();          // check for serial activity
  }
}


