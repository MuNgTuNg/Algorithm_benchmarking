

include_directories(${PROJECT_NAME} 
PUBLIC ${PARENT_DIR}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(algorithms INTERFACE
            binary_search.hpp
            bubble_sort.hpp
            insertion_sort.hpp
            merge_sort.hpp
            sAlgo.hpp
            
            )