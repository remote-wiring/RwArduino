add_executable(AnalogReadSerial AnalogReadSerial.cpp)
target_link_libraries(AnalogReadSerial LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(AnalogReadSerial remote_wiring firmata serial_wiring)

add_executable(BareMinimum BareMinimum.cpp)
target_link_libraries(BareMinimum LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(BareMinimum remote_wiring firmata serial_wiring)

add_executable(Blink Blink.cpp)
target_link_libraries(Blink LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(Blink remote_wiring firmata serial_wiring)

add_executable(DigitalReadSerial DigitalReadSerial.cpp)
target_link_libraries(DigitalReadSerial LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(DigitalReadSerial remote_wiring firmata serial_wiring)

add_executable(Fade Fade.cpp)
target_link_libraries(Fade LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(Fade remote_wiring firmata serial_wiring)

add_executable(Interrupt Interrupt.cpp)
target_link_libraries(Interrupt LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(Interrupt remote_wiring firmata serial_wiring)

add_executable(ReadAnalogVoltage ReadAnalogVoltage.cpp)
target_link_libraries(ReadAnalogVoltage LINK_PUBLIC remote_wiring firmata serial_wiring pthread)
add_dependencies(ReadAnalogVoltage remote_wiring firmata serial_wiring)
