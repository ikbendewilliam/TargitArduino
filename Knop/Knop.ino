#include <SoftwareSerial.h>
#include "Command.h"

static const int PIN_LED = 12;
static const int PIN_BUTTON = 7;
static const Command CMD_END(";");
static const Command CMD_LED_ON("LedOn");
static const Command CMD_LED_OFF("LedOff");
static const Command CMD_LED_FLASH("LedFlash");
static const String STR_BUTTON_PRESSED = "BtnPressed";
static const String STR_BUTTON_RELEASED = "BtnReleased";

SoftwareSerial mySerial(2, 3); // RX, TX
String inputString = "";
bool previousButtonState;
bool buttonState;
bool ledFlash = false;
bool flashstate = false;
unsigned long previousMillis = 0; 
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
{
  buttonState = digitalRead(PIN_BUTTON);
  if (previousButtonState != buttonState) {
    if (!buttonState) {
      mySerial.println(STR_BUTTON_PRESSED);
    } else {
      mySerial.println(STR_BUTTON_RELEASED);
    }
    previousButtonState = buttonState;
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
      ledFlash = false;
      digitalWrite(PIN_LED, HIGH);
      //Serial.println("Aan");
    }
    else if (CMD_LED_OFF.inString(inputString))
    {
      ledFlash = false;
      digitalWrite(PIN_LED, LOW);
      //Serial.println("Uit");
    }
    else if (CMD_LED_FLASH.inString(inputString))
    {
      ledFlash = true;
      //Serial.println("Flash");
    }
    inputString = "";
  }

  if (ledFlash)
  {
     int interval = 250;
     unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          flashstate = !flashstate;
          digitalWrite(PIN_LED, flashstate);          
     }
  }
}
