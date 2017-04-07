/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#include "RwArduino.h"

/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

using namespace remote_wiring::boards::arduino::uno;  // change to your board

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup(remote_wiring::RemoteDevice & board) {
    (void)board;
}

void loop(remote_wiring::RemoteDevice & board) {
  // read the analog in value:
  sensorValue = board.analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  board.analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  std::cout << "sensor = ";
  std::cout << sensorValue;
  std::cout << "\t output = ";
  std::cout << outputValue << std::endl;

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
