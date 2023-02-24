#pragma once
#include <vector>

//OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

namespace shb{


class sQuad{
  public:
    sQuad(){}

    std::vector<GLfloat> vertices = 
    { //     COORDINATES     /        COLORS      /   TexCoord  //
      x + -.5f, x + -.5f,  0.f,  .9f,1.f,2.f,
      x + -.5f, x + .5f,   0.f,  0.f,.5f,2.f,
      x + .5f,  x + .5f,    0.f,  2.f,1.f,.5f,
      x + .5f,  x + -.5f,   0.f,  2.f,.5f,2.f
    };
   
    std::vector<GLuint> indices = 
    {
      0,1,2,
      0,2,3
    };

    float x = 0, y = 0, z = 0;
    int value = 0;
};




}//namespace shb