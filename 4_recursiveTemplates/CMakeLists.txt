cmake_minimum_required(VERSION 3.1)

set(LIBRARY_NAME rectemplatesLib)

set(MODULE_HEADERS fibonacci.h primes.h)

set(MODULE_SOURCES main.cpp)

# build the module library
add_library(${LIBRARY_NAME} ${MODULE_HEADERS} ${MODULE_SOURCES})
add_library(lib::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# require C++17
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)

set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable(recursivetemplates main.cpp)
target_link_libraries(recursivetemplates lib::rectemplatesLib)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options( ${LIBRARY_NAME} PUBLIC -Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
    target_compile_options( recursivetemplates PUBLIC -Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options( ${LIBRARY_NAME} PUBLIC /W3 /WX )
    target_compile_options( recursivetemplates PUBLIC /W3 /WX )
endif()