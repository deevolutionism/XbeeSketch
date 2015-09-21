void serialCheck() {
  String buffer;

  if(Serial.available() > 0) {
    buffer = Serial.readStringUntil('\n'); // blocks here till we hit a newline
    if ((buffer.length() < 3) || buffer.length() > 10 || buffer.indexOf(" ") != -1) {  
      Serial.println("Badly formed name.  Try that again...");
    } else {
      connectXbee = true;
    }    
  }
}

 /* if(Xbee.available() > 0) {
    buffer = Xbee.readStringUntil('\n'); // blocks here till we hit a newline

    //Serial.print("NEW MESSAGE: "); // uncomment this line to see all raw network messages
    //Serial.println(buffer);

    // parse the messages

    // Ex: "bcast_msg John has joined the game!"
    if (buffer.startsWith(bcastMsgHdr, 0)) {  // found a broadcast message
      Serial.println(buffer.substring(bcastMsgHdr.length())); // just print the broadcast
    }


        } 
      }
    }
  }
}
*/
