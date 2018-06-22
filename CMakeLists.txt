cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)


include_directories(
	${CMAKE_SOURCE_DIR}/include # TODO: УДАЛИТЬ!
)

add_subdirectory(src)