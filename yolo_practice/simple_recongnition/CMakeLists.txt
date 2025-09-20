cmake_minimum_required(VERSION 3.10)
project(yolo_camera)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找OpenCV
find_package(OpenCV 4.5 REQUIRED)

# 输出找到的OpenCV版本信息
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# 包含头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加可执行文件
add_executable(yolo_camera simple_recognition.cpp)

# 链接OpenCV库
target_link_libraries(yolo_camera ${OpenCV_LIBS})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})