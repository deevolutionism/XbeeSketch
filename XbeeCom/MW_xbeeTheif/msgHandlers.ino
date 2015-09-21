
/*
  Deal with the serial ports
  If I get a proper name from hardware serial I try to attack them by broadcasting an xbee steal message.
  If I receive a broadcast I print it.
  If it was an attack against me I calculate the reprecussions and print/broadcast the result.
  */

void serialCheck() {
  String buffer;

  if(Serial.available() > 0) {
    buffer = Serial.readStringUntil('\n'); // blocks here till we hit a newline
    if ((buffer.length() < 3) || buffer.length() > 10 || buffer.indexOf(" ") != -1) {  
      Serial.println("Badly formed name.  Try that again...");
    } else {
      xbeeSerial.println(stealMsgHdr + myName + " attacks " + buffer);
      myMoney++;  // harsh boss... your cut is only $1
    }    
  }

  if(xbeeSerial.available() > 0) {
    buffer = xbeeSerial.readStringUntil('\n'); // blocks here till we hit a newline

    //Serial.print("NEW MESSAGE: "); // uncomment this line to see all raw network messages
    //Serial.println(buffer);

    // parse the messages

    // Ex: "bcast_msg John has joined the game!"
    if (buffer.startsWith(bcastMsgHdr, 0)) {  // found a broadcast message
      Serial.println(buffer.substring(bcastMsgHdr.length())); // just print the broadcast
    }

    // Ex: "steal_msg Jane steals from Joe"
    if (buffer.startsWith(stealMsgHdr, 0)) {
      Serial.println(buffer.substring(stealMsgHdr.length())); // someone got hit!

      // .println adds a \r\n we read till just before the \n so when comparing we have to manually add the \r
      if (buffer.endsWith(" " + myName + "\r")) {  // stealing from me! 
        int stolen = (myMoney/2) + 1;
        myMoney -= stolen;  // you always lose around half your money
        String stat = String(" got ") + verbs[random(10)]  + " for $" + stolen;
        Serial.println("You" + stat);
        xbeeSerial.println(bcastMsgHdr + myName + stat); // bcast your pain!!!
        if (myMoney <= 0) {
          xbeeSerial.println(bcastMsgHdr + myName + " bankrupted!"); // bcast your failure!!!
          Serial.print("\n\n\n\n\nBankrupt!!!\n\n\n\n\n");
          reBank();
        } 
      }
    }
  }
}

