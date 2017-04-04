cmake_minimum_required(VERSION 2.8.2)
project(RW_ARDUINO)

# Compile settings
option(LOG "Enable debug log" OFF)
if (LOG)
  message(STATUS "Debug logging enabled...")
  add_definitions(-DLOG)
endif()

# Prerequisites
find_package(Git REQUIRED)

# Set the output folders
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Werror")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable Crascit's "DownloadProject" CMake Module (MIT)
# https://github.com/crascit/downloadproject.git
include(DownloadProject.cmake)

# Download Remote Wiring as source
download_project(
  PROJ remote_wiring
  PREFIX remote_wiring
  GIT_REPOSITORY https://github.com/remote-wiring/remote-wiring.git
  GIT_TAG master
  TIMEOUT 10
)
add_subdirectory(${remote_wiring_SOURCE_DIR} ${remote_wiring_BINARY_DIR})

include_directories(${remote_wiring_SOURCE_DIR}/include)
include_directories(${remote_wiring_SOURCE_DIR}/firmata)
include_directories(include)

add_subdirectory(samples)
