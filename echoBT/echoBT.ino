#include <SoftwareSerial.h>
#include "command.h"

SoftwareSerial mySerial(10, 11); // RX, TX
static const Command CMD_END(";");

String inputString = "";

void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Loading complete");
}

void loop()
{
  delay(10);

  while (mySerial.available() > 0)
  {
    char c = mySerial.read();
    inputString += c;
  }

  if (CMD_END.inString(inputString))
  {
    mySerial.println(inputString);
    inputString = "";
  }
}
