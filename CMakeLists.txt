cmake_minimum_required(VERSION 3.22)

project(MyRenderEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS engine/src/*.cpp)
add_library(engine STATIC ${ENGINE_SRC})
target_include_directories(engine PUBLIC engine/include)
target_link_libraries(engine
    PUBLIC
        glfw
        glad
        OpenGL::GL
)

add_subdirectory(sandbox)
