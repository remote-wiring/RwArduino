# Remote Wiring - Arduino Sketch Environment

RwArduino allows you to emulate the Arduino sketch environment from a Linux or MacOS machine. In RwArduino, all logic is executing locally and infacing with generic firmware \(StandardFirmata\) capable of translating those instructions on an [Arduino](https://www.arduino.cc/) clone\*.

RwArduino is an example use case and comprehensive test case for the Remote Wiring library. RwArduino provides a case study that explores the limitations of the underlying protocol \(Firmata\) used by Remote Wiring, as well as remote execution compared to firmware executing directly on the MCU.

Finally, RwArduino provides examples to illustrate how a user could incorporate Remote Wiring into their own projects, and provides several concise and simple examples to accomplish basic tasks \(i.e. analog input, reading button presses, switching electricity, etc...\).

_\*The target device must be capable of running a firmata host program \(i.e. _[_StandardFirmata.ino_](https://github.com/firmata/arduino/tree/master/examples/StandardFirmata)_\) and reachable via a _[_supported serial connection_](https://github.com/remote-wiring/serial-wiring)_._

> See also: [Arduino Language Reference](https://www.arduino.cc/en/Reference/HomePage)

## Quick Start Guide

### Prerequisites:

* **CMake ** `v2.8.2` \(_minimum version_\)
* **Git ** `v1.9.1` \(_minimum version_\)
* **Firmata ** \[device firmware\]  `v2.5.6` \(_minimum version_\)

### Install Instructions:

```bash
$ git clone https://github.com/remote-wiring/RwArduino.git --recursive
$ cd RwArduino/
$ mkdir build
$ cd build/
$ cmake ..
$ make
```

### Run the sample:

1. Run `Blink` with no parameters to print out usage instructions.

   ```bash
   $ ./samples/basics/Blink

   ************************************************
   ** The "Examples > Firmata > StandardFirmata" **
   ** sketch must be deployed to the Arduino in  **
   ** order for the sample to work correctly.    **
   ************************************************
   Usage: ./samples/basics/Blink <serial device descriptor>
   ```

2. Install StandardFirmata.ino \(v2.5.6\) on an Arduino clone.

3. Take note of the _**Tools &gt; Port**_ setting, because this is the `<serial device descriptor>` required by `Blink`.

4. Run `Blink` \(_linux example shown below_\).

   ```bash
   ./samples/basics/Blink /dev/ttyACM0/
   ```

###### Expected Behavior

1. StandardFirmata will blink its major and minor version using a series of quick blinks.
2. The onboard LED will slowly blink until `Enter` is pressed on the keyboard.

### Example Code:

#### Blink the onboard LED

```c++
/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

#include "RwArduino.h"

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi

  modified 8 Sep 2016
  by Colby Newman
*/

using namespace remote_wiring::boards::arduino::uno;  // change to your board

// the setup function runs once when you press reset or power the board
void setup(remote_wiring::RemoteDevice & board) {
  // initialize digital pin LED_BUILTIN as an output.
  board.pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop(remote_wiring::RemoteDevice & board) {
  board.digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                           // wait for a second
  board.digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                           // wait for a second
}

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
```

### Code Breakdown:

```c++
#include "RwArduino.h"
```

This line incorporates the Remote Wiring Arduino sketch environment.

```c++
using namespace remote_wiring::boards::arduino::uno;  // change to your board
```

The `remote_wiring::boards` namespace defines several keywords with board specific values that are available in an Arduino sketch \(i.e. `LED_BUILTIN`, `A0`, `A1`, ..., `An`, etc...\).

```c++
// the setup function runs once when you press reset or power the board
void setup(remote_wiring::RemoteDevice & board) {
```

The `setup` function executes only one time and allows you configure any state before the main loop begins execution. The parameter `board` is the object representing the remote device and it adheres to the [Wiring interface](https://www.arduino.cc/en/Reference/HomePage).

```c++
  // initialize digital pin LED_BUILTIN as an output.
  board.pinMode(LED_BUILTIN, OUTPUT);
}
```

The call to `RemoteDevice::pinMode` tells the specfied pin whether it should be in input or output mode. Here it is set to `OUTPUT` in order to be able to drive power and ground to the pin.

```c++
// the loop function runs over and over again forever
void loop(remote_wiring::RemoteDevice & board) {
```

The `loop` function executes continuously until `<Enter>` is pressed on the keyboard to halt the program execution. The parameter `board` is the same object passed to the setup and will retain any state it was configured with during the execution of the `setup` function.

```c++
  board.digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                           // wait for a second
  board.digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                           // wait for a second
}
```

The `RemoteDevice::digitalWrite` calls drive power \(`HIGH`\) or ground \(`LOW`\) to the GPIO \(general purpose input/output\) pins, which turns on or off the LED. The calls to `delay` leave the state of the LED in place long enough for us to observe the light blinking on and off.

### References:

* [Wiring API - Wiring.org.co](http://wiring.org.co/reference/)
* [Wiring API - Arduino.cc](https://www.arduino.cc/en/Reference/HomePage)
* [Wiring API - Particle.io](https://docs.particle.io/reference/firmware/photon/#input-output)

### Project Organization:

Technical documentation, requirements and diagrams will be stored in the `docs/` folder. Sample programs are located in the `samples/` folder. Google Mock unit-tests are located in the `tests/` folder.

### Software License:

This project uses the _**MIT license**_, please consult the license file for details.

