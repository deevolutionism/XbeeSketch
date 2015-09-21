#include <avr/pgmspace.h>

// PROGMEM info: http://www.arduino.cc/en/Reference/PROGMEM

/*
Why do we use PROGMEM here? Well the text is ~1100 bytes.  This is more than half
the memory the Arduino Uno has!  So we go through the hassle of PROGMEM to keep 
strings in FLASH and only pull them out when we need to print them, thus freeing
up tonnes of RAM.
*/

const char string_0[] PROGMEM = "Gameplay:\n";   
const char string_1[] PROGMEM = "You want to steal, huh?  Good for you!\nWell you now have a boss and are ready to pillage.";
const char string_2[] PROGMEM = "After entering a name you will get startup cash and broadcast messages about other\nneighborhood players status and activities.";
const char string_3[] PROGMEM = "You can attack others by typing their names into the serial monitor then hitting send.";
const char string_4[] PROGMEM = "\nIf your money hits 0 you are sidelined by your distrustful boss until you reBank!";
const char string_5[] PROGMEM = "Bad news: If you steal anything, your cut is only $1.  Your boss takes the rest.";
const char string_6[] PROGMEM = "Good news: Your boss is none too bright.";
const char string_7[] PROGMEM = "This means that you are sidelined only for a short time before you get more money\nand even if you attack someone who is not in the game you will still get your $1.";
const char string_8[] PROGMEM = "\nNotes:";
const char string_9[] PROGMEM = "Richer players are protected in that you will see their stats update less frequently.";
const char string_10[] PROGMEM = "Richer players have more to lose each time they are attacked!";
const char string_11[] PROGMEM = "\nBefore you proceed make sure your line ending in the serial monitor is set for\nNewline\n";
const char string_12[] PROGMEM = "Press Send to Continue...";

// Then set up a table to refer to your strings.

const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10, string_11, string_12};

void rules() {
  
/*  Uncomment this if you want to see the program fail in weird ways...

  Serial.println("Gameplay:\n");

  Serial.println("So you want to steal, huh?  Well you now have a boss and are ready to pillage.");

  Serial.println("After entering a name you will get startup cash and broadcast messages about other\nneighborhood players status and activities.");
  Serial.println("You can attack others by typing their names into the serial monitor then hitting send.");

  Serial.println("\nIf your money hits 0 you are sidelined by your distrustful boss until you reBank!");
  Serial.println("Bad news: If you steal anything, your cut is only $1.  Your boss takes the rest.");
  Serial.println("Good news: Your boss is none too bright.");
  Serial.println("This means that you are sidelined only for a short time before you get more money\nand even if you attack someone who is not in the game you will still get your $1.");
  
  Serial.println("\nNotes:");
  Serial.println("Richer players are protected and you will see their stats update less frequently.");
  Serial.println("Richer players have more to lose each time they are attacked!");
    
  Serial.println("\nBefore you proceed make sure your line ending in the serial monitor is set for\nNewline\n");
  Serial.println("Press Send to Continue...");
*/
  char buffer[200];
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy.
    Serial.println(buffer);
  }
  while (true) {
    if (Serial.read() == '\n') {
      break;
    }
  }
}

void getName() {
  String buffer;

  Serial.println ("Please enter a unique 3-10 char name containing no spaces.");

  while (true) {
    if(Serial.available() > 0) {
      buffer = Serial.readStringUntil('\n'); // blocks here till we hit a newline
     
      if (buffer.length() < 3 || buffer.length() > 10 || buffer.indexOf(" ") != -1) {  
        Serial.println("\nFail.  Let's try that again...");
        Serial.println ("Please enter a unique <= 10 char name containing no spaces.");
        buffer = "";
      } 
      else {
        myName = buffer;
        Serial.println("\nCool.  Let's get some starting money!!!");
        break;
      }    
    }
  }
}

