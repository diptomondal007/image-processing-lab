cmake_minimum_required(VERSION 3.17)
project(SutherlandHodgman)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# Execute compilation command
set(SOURCE_FILES main.cpp)

add_executable(SutherlandHodgman main.cpp)

if (APPLE)
    target_link_libraries(SutherlandHodgman "-framework OpenGL")
    target_link_libraries(SutherlandHodgman "-framework GLUT")
endif()