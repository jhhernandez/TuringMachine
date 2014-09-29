set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library(
	Machine
	SHARED
	Machine.cpp Tape.cpp Header.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)