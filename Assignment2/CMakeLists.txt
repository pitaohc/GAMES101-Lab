cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(Rasterizer2)

# import Eigen3
find_package(Eigen3 CONFIG REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

# import OpenCV4
set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv4")
message(STATUS "VCPKG_INSTALLED_DIR: ${VCPKG_INSTALLED_DIR}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}") # print OpenCV_DIR
find_package(OpenCV REQUIRED)



include_directories(/usr/local/include)

add_executable(Rasterizer2 main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)

target_link_libraries(Rasterizer2 PRIVATE Eigen3::Eigen)
target_link_libraries(Rasterizer2 PRIVATE ${OpenCV_LIBS})