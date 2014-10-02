set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library(
	Machine
	STATIC
	Machine.cpp Tape.cpp Header.cpp State.cpp TransitionTable.cpp)

target_link_libraries(
	Machine
	${JSON_SPIRIT_STATIC_LIB})

set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)