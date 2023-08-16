cmake_minimum_required(VERSION 3.10)
project(Rasterizer3)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# import Eigen3
find_package(Eigen3 CONFIG REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

# import OpenCV4
set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv4")
message(STATUS "VCPKG_INSTALLED_DIR: ${VCPKG_INSTALLED_DIR}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}") # print OpenCV_DIR
find_package(OpenCV REQUIRED)

include_directories(/usr/local/include ./include)

add_executable(Rasterizer3 main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp Texture.hpp Texture.cpp Shader.hpp OBJ_Loader.h)

target_link_libraries(Rasterizer3 PRIVATE Eigen3::Eigen)
target_link_libraries(Rasterizer3 PRIVATE ${OpenCV_LIBS})
#target_link_libraries(Rasterizer3 ${OpenCV_LIBRARIES})
#target_compile_options(Rasterizer3 PUBLIC -Wall -Wextra -pedantic)