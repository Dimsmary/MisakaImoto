# add a library
add_library(
        Misaka_library
        src/fb-pusher.hpp src/fb-pusher.cpp
        src/video_player.cpp src/video_player.hpp
        src/gpio_status.hpp src/gpio_status.cpp
        src/frame_stacker.cpp src/frame_stacker.hpp
        src/voltage_detect.cpp src/voltage_detect.hpp)

# include library path
target_include_directories(Misaka_library PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")