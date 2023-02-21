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




namespace shb{
class sApp{
 public:
    void run();

    sApp() { 
         //setup
         srand(time(0));
    }

    
    
    void controls(sWindow& window, float& x, float& y, float& z, float& scaleY, float& scaleX){
        if(glfwGetKey(window.handle(),GLFW_KEY_W) == GLFW_PRESS){
            y += 0.1f;
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_S) == GLFW_PRESS){
            y -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_A) == GLFW_PRESS){
            x -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_D) == GLFW_PRESS){
            x += 0.1f; 
        }

        if(glfwGetKey(window.handle(),GLFW_KEY_UP) == GLFW_PRESS){
            scaleY += 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_DOWN) == GLFW_PRESS){
            scaleY -= 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_LEFT) == GLFW_PRESS){
            scaleX += 0.1f; 
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_RIGHT) == GLFW_PRESS){
            scaleX -= 0.1f; 
        }
    }


 private:
    sWindow window{1920,1080};
    sAlgorithm algo{};
};
}