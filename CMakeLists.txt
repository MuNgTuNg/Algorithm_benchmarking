cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_BUILD_TYPE Debug)

project(Algorithms LANGUAGES CXX C ) #Algorithms = ${PROJECT_NAME}
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(include)
add_subdirectory(src)

target_link_directories(${PROJECT_NAME} PRIVATE src)

target_link_directories(${PROJECT_NAME} 
                        PRIVATE include/algorithms
                        PRIVATE include/shapes
                        PRIVATE include/external
                        PRIVATE src
                        )


target_include_directories(${PROJECT_NAME} 
                            PUBLIC include
                            PUBLIC include/external/glfw/include
                            PUBLIC external/stb
                            PUBLIC external/imgui
                          )

target_link_libraries( ${PROJECT_NAME}
                        algorithms
                        src
                        imgui
                        glfw
                        stb
                        shapes
                        
                        )