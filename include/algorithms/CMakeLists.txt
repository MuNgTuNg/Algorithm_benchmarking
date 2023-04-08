

include_directories(${PROJECT_NAME} 
PUBLIC ${PARENT_DIR}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(algorithms
            sAlgo.hpp
            
            
            graph/sGraph.hpp#
            graph/sGraph.cpp
            linked_lists/linked_list.hpp
            linked_lists/linked_list.cpp
            searching/binary_search.hpp
            sorting/bubble_sort.hpp
            sorting/insertion_sort.hpp
            sorting/quick_sort.hpp
            sorting/merge_sort.hpp
            sliding_window/kadanes_algorithm.hpp
            sorting/bogo_sort.hpp
            
            )