cmake_minimum_required(VERSION 3.20)
project(learnopengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    SDL2::SDL2 SDL2::SDL2main
    OpenGL::GL
    GLEW::GLEW)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/lib/eventpp/include
    ${PROJECT_SOURCE_DIR}/lib/glm)