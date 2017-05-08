/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#include "RwArduino.h"

/*
  State change detection (edge detection)

 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.

 This example shows how to detect when a button or button changes from off to on
 and on to off.

 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)

 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/ButtonStateChange

 */

using namespace remote_wiring::boards::arduino::uno;  // change to your board

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup(remote_wiring::RemoteDevice & board) {
  // initialize the button pin as a input:
  board.pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  board.pinMode(ledPin, OUTPUT);
}


void loop(remote_wiring::RemoteDevice & board) {
  // read the pushbutton input pin:
  buttonState = board.digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      std::cout << "on" << std::endl;
      std::cout << "number of button pushes: ";
      std::cout << buttonPushCounter << std::endl;
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      std::cout << "off" << std::endl;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 4 == 0) {
    board.digitalWrite(ledPin, HIGH);
  } else {
    board.digitalWrite(ledPin, LOW);
  }

}

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
