#include <SoftwareSerial.h>
#include "Command.h"

static const int PIN_LED = 12;
static const int PIN_BUTTON = 7;
static const Command CMD_END(";");
static const Command CMD_LED_ON("LedOn");
static const Command CMD_LED_OFF("LedOff");

SoftwareSerial mySerial(2, 3); // RX, TX
String inputString = "";
bool previousButtonState;
bool ButtonState;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
  inputString.reserve(50);
  previousButtonState = digitalRead(PIN_BUTTON);
  Serial.println("Loading complete");
}

void loop()
{ // run over and over

  //  if (Serial.available()) {
  //    mySerial.write(Serial.read());
  //  }
  ButtonState = digitalRead(PIN_BUTTON);
  if(previousButtonState != ButtonState){
      if(!ButtonState){
         mySerial.println("in");
      }else{
        mySerial.println("uit");
      }  
      previousButtonState = ButtonState;
  }
  

  while (mySerial.available()) {
    // get the new byte
    char inChar = (char)mySerial.read();
    inputString += inChar;
  }

  if (CMD_END.inString(inputString))
  {
    if (CMD_LED_ON.inString(inputString))
    {
      digitalWrite(PIN_LED, HIGH);
      Serial.println("Aan");
    }
    else if (CMD_LED_OFF.inString(inputString))
    {
      digitalWrite(PIN_LED, LOW);
      Serial.println("Uit");
    }
    inputString = "";
  }
}
