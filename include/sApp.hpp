#pragma once 


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <unistd.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

#include <sWindow.hpp>
#include <sShader.hpp>
#include <sDebugging.hpp>


namespace shb{
class sApp{
    public:
        void run();

    void generateRand(std::vector<int>& vec, int amount){
        for(int i = 0; i < amount; ++i){
            vec.push_back(rand());
        }
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

};
}