#include <SoftwareSerial.h>
#include "Command.h"

static const int PIN_LED = 13;
static const Command CMD_END(";");
static const Command CMD_LED_ON("LedOn");
static const Command CMD_LED_OFF("LedOff");

SoftwareSerial mySerial(2, 3); // RX, TX
String inputString = "";

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(PIN_LED, OUTPUT);
  inputString.reserve(50);

  Serial.println("Loading complete");
}

void loop()
{ // run over and over

  //  if (Serial.available()) {
  //    mySerial.write(Serial.read());
  //  }

  while (mySerial.available()) {
    // get the new byte
    char inChar = (char)mySerial.read();
    inputString += inChar;
  }

  if (CMD_END.inString(inputString)))
  {
    if (CMD_LED_ON(inputString)))
    {
      digitalWrite(ledPin, HIGH);
      Serial.println("Aan");
    }
    else if (CMD_LED_OFF.inString(inputString)))
    {
      digitalWrite(ledPin, LOW);
      Serial.println("Uit");
    }
    inputString = "";
  }
}
