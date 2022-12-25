cmake_minimum_required(VERSION 3.0.0)
project(OpenGL VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(OpenGL src/main.cpp src/glad.cpp)

include_directories(include)

add_subdirectory(lib/GLFW)
target_link_libraries(OpenGL glfw)
find_package(OpenGL REQUIRED)
target_link_libraries( OpenGL OpenGL::GL)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
include(CPack)
