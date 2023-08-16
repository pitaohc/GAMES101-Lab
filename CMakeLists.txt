cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
# 设置项目名为GAMES101-Lab
project(GAMES101-Lab)
# 输出根目录
message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})

# 获得根目录中前缀为Assignment的目录
file(GLOB ASSIGNMENT_DIRS RELATIVE ${PROJECT_SOURCE_DIR} Assignment*)
message(STATUS "This is ASSIGNMENT_DIRS " ${ASSIGNMENT_DIRS})

# 遍历ASSIGNMENT_DIRS，判断是否包含CMakeLists.txt
foreach(ASSIGNMENT_DIR ${ASSIGNMENT_DIRS})
	if(EXISTS ${PROJECT_SOURCE_DIR}/${ASSIGNMENT_DIR}/CMakeLists.txt)
		# 如果包含CMakeLists.txt，则进入该目录
		message(STATUS "This is ASSIGNMENT_DIR " ${ASSIGNMENT_DIR})
		add_subdirectory(${PROJECT_SOURCE_DIR}/${ASSIGNMENT_DIR})
	endif()
endforeach()
