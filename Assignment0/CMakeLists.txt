cmake_minimum_required (VERSION 3.3.0)
project (Transformation)
# import Eigen3
find_package(Eigen3 CONFIG REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)
# import OpenCV4
set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv4")
message(STATUS "VCPKG_INSTALLED_DIR: ${VCPKG_INSTALLED_DIR}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}") # print OpenCV_DIR
find_package(OpenCV REQUIRED)
add_executable (Transformation main.cpp)
target_link_libraries(Transformation PRIVATE Eigen3::Eigen)
target_link_libraries(Transformation PRIVATE ${OpenCV_LIBS})