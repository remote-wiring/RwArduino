/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //%% Aduino Sketch Environment %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <cerrno>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

#include <remote_wiring>
#include <serial_wiring>

void loop(remote_wiring::RemoteDevice & board_);
void setup(remote_wiring::RemoteDevice & board_);

std::atomic_bool run;
std::chrono::steady_clock::time_point sketch_start;

namespace wiring {

typedef uint8_t byte;

static inline
int
constrain (
    int value_,
    int floor_,
    int ceiling_
) {
    int result;

    if ( value_ <= floor_ ) {
        result = floor_;
    } else if ( value_ >= ceiling_ ) {
        result = ceiling_;
    } else {
        result = value_;
    }

    return result;
}

static inline
void
delay (
    size_t ms_
) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_));
}

static inline
void
delayMicroseconds (
    size_t us_
) {
    std::this_thread::sleep_for(std::chrono::microseconds(us_));
}

static inline
size_t
digitalPinToInterrupt (
    size_t pin_
) {
    return pin_;
}

static inline
int
map (
    int value_,
    int from_low_,
    int from_high_,
    int to_low_,
    int to_high_
) {
    const int from_range = (from_high_ - from_low_);
    const int to_range = (to_high_ - to_low_);
    const int value_offset = (value_ - from_low_);

    int result;

    if ( value_ < from_low_ ) {
        errno = EDOM;
        ::perror("Invalid \"value\" parameter supplied to map function!");
        result = to_low_;
    } else if ( value_ > from_high_) {
        errno = EDOM;
        ::perror("Invalid \"value\" parameter supplied to map function!");
        result = to_high_;
    } else if ( 0 == from_range ) {
        errno = ERANGE;
        ::perror("Invalid \"from range\", cannot be zero!");
        result = from_low_;
    } else if ( value_ == from_low_) {
        result = to_low_;
    } else if ( value_ == from_high_) {
        result = to_high_;
    } else {
        result = (((value_offset * to_range) / from_range) + to_low_);
    }

    return result;
}

static inline
size_t
micros (
    void
) {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - sketch_start).count();
}

static inline
size_t
millis (
    void
) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - sketch_start).count();
}

}  // namespace wiring

using namespace remote_wiring::wiring;
using namespace wiring;

namespace {
    void sketch_thread(remote_wiring::RemoteDevice & board_) {
      setup(board_);
      for (run = true ; run ; ) { loop(board_); }
    }
}

int main (int argc, char * argv []) {
    std::cout << "************************************************" << std::endl;
    std::cout << "** The \"Examples > Firmata > StandardFirmata\" **" << std::endl;
    std::cout << "** sketch must be deployed to the Arduino in  **" << std::endl;
    std::cout << "** order for the sample to work correctly.    **" << std::endl;
    std::cout << "************************************************" << std::endl;

    if ( argc < 2 ) { std::cout << "Usage: " << argv[0] << " <serial device descriptor>" << std::endl; return -1; }

    serial_wiring::UartSerial usb(argv[1]);
    remote_wiring::FirmataDevice board(usb);

    // Establish a communication channel
    usb.begin(57600);

    // Attach to the remote device
    board.attach();

    // Increase the sampling interval
    board.samplingInterval(1);

    // Survey the board's capabilities
    board.survey();

    // Launch Arduino sketch environment
    sketch_start = std::chrono::steady_clock::now();
    std::thread sketch(sketch_thread, std::ref(board));

    // Prompt for exit
    std::cout << std::endl << "Processing sketch on remote device." << std::endl;
    if ( board.firmware() ) {
        std::cout << "(detected firmware as: " << board.firmware() << " - v" << board.version().sv_major << "." << board.version().sv_minor << ")" << std::endl;
    } else {
        std::cout << "(unable to detect firmware)" << std::endl;
    }

    // Await user input
    std::cout << std::endl << "Press <Enter> to exit sketch..." << std::endl;
    ::getchar();
    run = false;
    sketch.join();
    std::cout << "Sketch environment has exited." << std::endl;

    // Clean-up and exit
    board.detach();
    usb.end();
    return 0;
}

/* Created and copyrighted by Zachary J. Fields. Offered as open source under the MIT License (MIT). */
