add_subdirectory(algorithms)
add_subdirectory(external)


add_library(sLib INTERFACE
            sApp.hpp
            sWindow.hpp
            sShader.hpp)