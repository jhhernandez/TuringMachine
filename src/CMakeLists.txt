set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library(
	Machine
	SHARED
	Machine.cpp Tape.cpp Header.cpp State.cpp TransitionTable.cpp)

target_link_libraries(
	Machine
	${JSON_SPIRIT_SHARED_LIB})

set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)