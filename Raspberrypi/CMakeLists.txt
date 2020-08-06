cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

# Search OpenCV Library
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Search WiringPi Library
find_library(wiringPi_LIB wiringPi)

# Search Boot Library
FIND_PACKAGE(Boost COMPONENTS system filesystem)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


# add sub directory
add_subdirectory(module)
add_subdirectory(exe)
