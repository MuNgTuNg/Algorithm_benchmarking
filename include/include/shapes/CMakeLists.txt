include_directories(${PROJECT_NAME} 
PUBLIC ${PARENT_DIR}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(shapes INTERFACE
            sQuad.hpp
            
            )