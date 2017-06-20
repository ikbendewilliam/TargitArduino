#include <SoftwareSerial.h>
#include "Command.h"

static const int PIN_LED = 12; // The pin where the led is connected on
static const int PIN_BUTTON = 7; // The pin where the button is connected on
// WARNING: The following commands need to be the same as the commands in the app
static const Command CMD_END(";"); // The end of a command
static const Command CMD_LED_ON("LedOn"); // The command when you need to turn on the led
static const Command CMD_LED_OFF("LedOff"); // The command when you need to turn off the led
static const Command CMD_LED_FLASH("LedFlash"); // The command when you need to start flashing the led
static const String STR_BUTTON_PRESSED = "BtnPressed"; // The command to send when a button is pressed
static const String STR_BUTTON_RELEASED = "BtnReleased"; // The command to send when a button is released

SoftwareSerial mySerial(2, 3); // Create a Serial connection on other pins. Format (RX, TX)
String inputString = ""; // The string that is received
bool previousButtonState; // The previous state of the button
bool buttonState; // The current state of the button
bool ledFlash = false; // Whether the led is currently flashing
bool flashState = false; // Whether the led is currently on (during flashing)
unsigned long previousMillis = 0; // The time of the previous flash state change
int interval = 500; // The time to flash on or off, this should be specified with the command

void setup()
{
  Serial.begin(9600); // Initialize the serial for debugging at a baudrate of 9600
  mySerial.begin(9600); // Initialize the serial for bt at a baudrate of 9600
  pinMode(PIN_BUTTON, INPUT); // Set the pinmode of the button to input
  pinMode(PIN_LED, OUTPUT); // Set the pinmode of the led to output
  inputString.reserve(50); // Reserve space for the incoming string
  previousButtonState = digitalRead(PIN_BUTTON); // read the current state and save it to previousButtonState
  Serial.println("Loading complete"); // Show that the setup is done
}

void loop()
{
  buttonState = digitalRead(PIN_BUTTON); // Get the current buttonstate
  if (previousButtonState != buttonState) { // If the state has changed
    if (!buttonState) { // If the button is pressed
      mySerial.println(STR_BUTTON_PRESSED); // Send over bt that the burron is pressed
    } else { // If the button is released
      mySerial.println(STR_BUTTON_RELEASED); // Send over bt that the burron is released
    }
    previousButtonState = buttonState; // Change the previous buttonState
  }

  while (mySerial.available()) { // If there is data coming in from bt
    char inChar = (char)mySerial.read(); // get the new byte
    inputString += inChar; // Save this byte to the inputString
  }

  if (CMD_END.inString(inputString)) // If the end of a command is found in the inputString
  {
    if (CMD_LED_ON.inString(inputString)) // If the command led on is found in the inputString
    {
      ledFlash = false; // The led is not flashing
      digitalWrite(PIN_LED, HIGH); // Turn the led on
      //Serial.println("Aan");
    }
    else if (CMD_LED_OFF.inString(inputString)) // If the command led off is found in the inputString
    {
      ledFlash = false; // The led is not flashing
      digitalWrite(PIN_LED, LOW); // Turn the led off
      //Serial.println("Uit");
    }
    else if (CMD_LED_FLASH.inString(inputString)) // If the command led flash is found in the inputString
    {
      ledFlash = true; // The led is flashing
      flashState = false; // Turn the flash state off, this means the led will be on at the start
      interval = CMD_LED_FLASH.getFirstParameter(inputString); // Get the interval from the command
      //Serial.println("Flash");
    }
    inputString = ""; // Reset the inputString
  }

  if (ledFlash) // If flashing
  {
    unsigned long currentMillis = millis(); // Get the time the program is busy
    if (currentMillis - previousMillis >= interval) { // Check if the intervaltime has passed
      previousMillis = currentMillis; // Save this time
      flashState = !flashState; // Change the flashState
      digitalWrite(PIN_LED, flashState ? HIGH : LOW); // Turn the led on/off depending on flashstate
    }
  }
}
