
add_executable( Misaka_Imoto main.cpp)
target_link_libraries( Misaka_Imoto ${OpenCV_LIBS} ${wiringPi_LIB} ${Boost_LIBRARIES} Misaka_library)
#target_link_libraries( Misaka_Imoto PRIVATE fb-pusher)

