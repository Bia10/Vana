#project(common)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE COMMON_SRC **/*.cpp)
file(GLOB_RECURSE COMMON_HDR **/*.hpp)
source_group("common" FILES ${COMMON_SRC} ${COMMON_HDR})

include_directories(../)

add_library(common STATIC
	${COMMON_SRC} ${COMMON_HDR}
)
