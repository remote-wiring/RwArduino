# Base Image
FROM alpine:latest

# Add Required Packages [Layer 1]
RUN apk update && \
    apk add ca-certificates cmake g++ git make

# Download Sources [Layer 2]
RUN cd ~ && \
    git clone https://github.com/remote-wiring/rw-arduino.git && \
    cd rw-arduino/ && \
    mkdir build

# Verify Build and Install
CMD cd ~/rw-arduino/build/ && \
    cmake .. && \
    make
