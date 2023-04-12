#pragma once 

//OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std lib
#include <chrono>
#include <unistd.h>
#include <iostream>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

//graphics
#include <sWindow.hpp>
#include <sUtils.hpp>
#include <sDebugging.hpp>

//algorithms
#include <algorithms/sAlgo.hpp>

//shapes
#include <shapes/sQuad.hpp>




namespace shb{
class sApp{
 public:
    void run();

    sApp() { 
         //setup
         srand(time(0));
    }

    
    
    void controls(sWindow& window, sQuad& quad){
        if(glfwGetKey(window.handle(),GLFW_KEY_W) == GLFW_PRESS){
            quad.y += 0.1f;
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_S) == GLFW_PRESS){
            quad.y -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_A) == GLFW_PRESS){
            quad.x -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_D) == GLFW_PRESS){
            quad.x += 0.1f; 
        }

        if(glfwGetKey(window.handle(),GLFW_KEY_UP) == GLFW_PRESS){
            quad.scaleY += 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_DOWN) == GLFW_PRESS){
            quad.scaleY -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_LEFT) == GLFW_PRESS){
            quad.scaleX += 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_RIGHT) == GLFW_PRESS){
            quad.scaleX -= 0.1f; 
        }
    }


 private:
    float windowW = 1920;
    float windowH = 1080;
    sWindow window{(int)windowW,(int)windowH};
    sAlgorithm algo{};

public:
    bool graphics = false;
    bool algorithms = false;
    bool graph = false;
    bool list = false;
    bool tree = false;
};
}