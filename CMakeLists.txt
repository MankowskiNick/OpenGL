cmake_minimum_required(VERSION 3.0.0)
project(CrossPlatformOpenGL VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CrossPlatformOpenGL src/main.cpp src/glad.cpp)

include_directories(include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/GLFW)
target_link_libraries(CrossPlatformOpenGL glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(CrossPlatformOpenGL OpenGL::GL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
