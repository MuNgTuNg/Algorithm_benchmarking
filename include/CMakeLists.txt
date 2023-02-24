add_subdirectory(algorithms)
add_subdirectory(external)
add_subdirectory(shapes)


add_library(sLib INTERFACE
            sApp.hpp
            sWindow.hpp
            sUtils.hpp)