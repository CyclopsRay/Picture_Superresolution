cmake_minimum_required(VERSION 3.1)
project(enhance CXX)

if(${CONFIG_MODE} MATCHES "debug")
    message(STATUS "DEBUG MODE ON")
    add_definitions(-DDEBUG)
else()
    message(STATUS "DEBUG MODE OFF")
endif()

if(${SELECT_MODEL} MATCHES "old")
    message(STATUS "USING THE OLD MODEL")
else()
    message(STATUS "USING THE NEW MODEL")
    add_definitions(-DNEW_MODEL)
endif()

set(CMAKE_CXX_FLAGS "-O3 ")
message(STATUS ${PROJECT_SOURCE_DIR})
set(TENSORFLOW_SOURCE_DIR 
    ${PROJECT_SOURCE_DIR}/include)
set(TFLITE_LIBS ${PROJECT_SOURCE_DIR}/lib)
include_directories(${TENSORFLOW_SOURCE_DIR}/)
include_directories(${TENSORFLOW_SOURCE_DIR}/tensorflow/lite/tools/make/downloads/flatbuffers/include)

link_directories(${TFLITE_LIBS})
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)

add_library(enhance STATIC include/pic_enhance.h src/pic_enhance.cpp)
set_target_properties(enhance PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(enhance
    -Wl,--whole-archive
    libtensorflow-lite.a
    -Wl,--no-whole-archive
    Threads::Threads
    dl)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(enhance_shared SHARED include/pic_enhance.h src/pic_enhance.cpp)
set_target_properties(enhance_shared PROPERTIES LINKER_LANGUAGE CXX)
# Link your application with OpenCV libraries
target_link_libraries(enhance_shared
    -Wl,--whole-archive
    libtensorflow-lite.a
    -Wl,--no-whole-archive
    Threads::Threads
    dl)
