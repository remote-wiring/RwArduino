/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#include "RwArduino.h"

/*
 Input Pullup Serial

 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
 digital input on pin 2 and prints the results to the serial monitor.

 The circuit:
 * Momentary switch attached from pin 2 to ground
 * Built-in LED on pin 13

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.

 created 14 March 2012
 by Scott Fitzgerald

 http://www.arduino.cc/en/Tutorial/InputPullupSerial

 This example code is in the public domain

 */

/* Blink without Delay

 Turns on and off a light emitting diode (LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 The circuit:
 * Use the onboard LED.
 * Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 modified 11 Nov 2013
 by Scott Fitzgerald
 modified 9 Jan 2017
 by Arturo Guadalupi


 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

using namespace remote_wiring::boards::arduino::uno;  // change to your board

void setup(remote_wiring::RemoteDevice & board) {
  //configure pin2 as an input and enable the internal pull-up resistor
  board.pinMode(2, INPUT_PULLUP);
  board.pinMode(13, OUTPUT);

}

void loop(remote_wiring::RemoteDevice & board) {
  //read the pushbutton value into a variable
  int sensorVal = board.digitalRead(2);
  //print out the value of the pushbutton
  std::cout << sensorVal << std::endl;

  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    board.digitalWrite(13, LOW);
  } else {
    board.digitalWrite(13, HIGH);
  }
}

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
