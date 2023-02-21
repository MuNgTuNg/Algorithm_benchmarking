

include_directories(${PROJECT_NAME} 
                            PUBLIC ${PARENT_DIR}../include
                            PUBLIC ${PARENT_DIR}../include
                            PUBLIC ${PARENT_DIR}../include/external/glfw/include
                            PUBLIC ${PARENT_DIR}../include/external/stb
                            PUBLIC ${PARENT_DIR}../include/external/imgui
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                          )

add_library(src 
            glad.c
            sApp.cpp
            sWindow.cpp
            sDebugging.cpp
            sUtils.cpp
            )