/*
  Styling guide

  Describe what it does in layman's terms.  Refer to the components
  attached to the various pins.

  The circuit:
    list the components attached to each input
    list the components attached to each output

  Created 29th may 2017
  By William

  More info
  https://www.arduino.cc/en/Reference/StyleGuide
*/

// Always use ctrl + t (arduino IDE) before saving

// Include librarys first, then costum files
#include <SoftwareSerial.h>
#include "Command.h"

// When you use pins either define them or comment their use
SoftwareSerial mySerial(10, 11); // RX, TX

static const int PIN_RX = 10;
static const int PIN_TX = 11;
SoftwareSerial mySerialExample(PIN_RX, PIN_TX);

// No #define, instead use static const int/static const String/static const other...
// Static const all caps
// Each global is defined on a new line
// Either use clear abbreviations (cmd == command) or none to avoid confusion (srl == ?)
static const Command CMD_END(";");
static const int SERIAL_BAUD_RATE = 9600;

// Global variables starts with lower
// Initialize
String inputString = "";

// Always setup first
// Place braces on a separate line
void setup()
{
  // When using serial, define first and use static const for the baud rate
  mySerial.begin(SERIAL_BAUD_RATE);
  // During debugging show a complete on serial
  mySerial.println("Loading complete");
}

// Second function is loop
void loop()
{
  while (mySerial.available() > 0)
  {
    // local variables can be the first letter of the type (char c, String s, ...)
    // Except for int. Use n, or smth else, not i, j, k (these are for loops)
    // If the variable is significant in understanding the code, use clear names
    // If it can be written on one line but it is not clear enough, write multiple lines
    inputString += mySerial.read();

    char c = mySerial.read();
    inputString += c;
  }

  // Use bracces when multiple lines
  if (CMD_END.inString(inputString))
  {
    mySerial.println(inputString);
    inputString = "";
  }

  // No braces when single EXECUTION line
  if (inputString == "test")
    Serial.println(inputString);

  // Always use at least two lines so don't do this...
  if (inputString == "null") inputString = "";
  // Instead write
  if (inputString == "null")
    inputString = "";

  // When using delay of delayMicroseconds, static const's aren't mandatory
  // Use delay when possible
  delay(10);
  // Don't write delayMicroseconds with parameters over 1k
  delayMicroseconds(750);
}
