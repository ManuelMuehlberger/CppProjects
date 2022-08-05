cmake_minimum_required(VERSION 3.1)

set(LIBRARY_NAME libThreadedLogger)

# list all the headers of the module
set(MODULE_HEADERS monitor.h logger.h)

# list all the code files of the module
set(MODULE_SOURCES monitor.cpp logger.cpp)

# build the libraries
add_library(${LIBRARY_NAME} ${MODULE_HEADERS} ${MODULE_SOURCES})
add_library(lib::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# require C++17
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable(threadedLogger main.cpp)
target_link_libraries(threadedLogger lib::libThreadedLogger pthread)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options( ${LIBRARY_NAME} PUBLIC -Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
    target_compile_options( threadedLogger PUBLIC -Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options( ${LIBRARY_NAME} PUBLIC /W3 /WX )
    target_compile_options( threadedLogger PUBLIC /W3 /WX )
endif()
