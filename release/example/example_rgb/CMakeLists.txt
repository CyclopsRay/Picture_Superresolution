cmake_minimum_required(VERSION 3.1)
project(ovision_enhance_exp1)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})


#set(TENSORFLOW_SOURCE_DIR 
#  "/mnt/g/linux/tensorflow_src"
#)
include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)

#set(TFLITE_LIBS ${TENSORFLOW_SOURCE_DIR}/tensorflow/lite/tools/make/gen/linux_x86_64/lib)
#include_directories(${TENSORFLOW_SOURCE_DIR}/)
#include_directories(${TENSORFLOW_SOURCE_DIR}/tensorflow/lite/tools/make/downloads/flatbuffers/include)
#include_directories(${TENSORFLOW_SOURCE_DIR}/tensorflow/lite/tools/make/downloads/absl)

add_executable(ovision_enhance_exp1 project_main.cpp ../../include/pic_enhance.h)
#add_executable(final testmain.cpp atest.h)
target_link_libraries(ovision_enhance_exp1 
    ${OpenCV_LIBS}

    libovision_enhance.so)