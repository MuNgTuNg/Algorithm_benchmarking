#pragma once
#include <vector>

//OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

//mine

#include <sWindow.hpp>
#include <sDebugging.hpp>

namespace shb{


class sQuad{
  public:
    

    std::vector<GLfloat> vertices = 
    { //     COORDINATES     /        COLORS      /   TexCoord  //
      -100.f, -100.f,  0.f,  .9f,1.f,2.f,
      -100.f, 100.f,   0.f,  0.f,.5f,2.f,
      100.f,  100.f,    0.f,  2.f,1.f,.5f,
      100.f,  -100.f,   0.f,  2.f,.5f,2.f
    };
   
    std::vector<GLuint> indices = 
    {
      0,1,2,
      0,2,3
    };

    void draw(){
      glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER,VBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);

     //draw currently bound index buffer
     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
  
     glBindVertexArray(0);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void update(){
        //initialise matrices for use
      
     glm::mat4 model{1.f};
     int modelUniform = glGetUniformLocation(shaderProgram,"model");
     glUniformMatrix4fv(modelUniform,1,GL_FALSE,glm::value_ptr(model));
  
     glm::mat4 scale{1.f};
     scale = glm::scale( scale,glm::vec3(scaleX, scaleY,1.f));
     int scaleUniform = glGetUniformLocation(shaderProgram,"scale");
     glUniformMatrix4fv(scaleUniform,1,GL_FALSE,glm::value_ptr(scale));
  
     glm::mat4 view{1.f};
     view = glm::translate( view,glm::vec3(x, y,z));
     int viewUniform = glGetUniformLocation(shaderProgram,"location");
     glUniformMatrix4fv(viewUniform,1,GL_FALSE,glm::value_ptr(view));
     
     //CAMERA UNIFORMS
     //glm::mat4 projection{1.f};
     //projection = glm::perspective(45.f,(float)(WINDOW_WIDTH/WINDOW_HEIGHT),0.1f,1000.f);
     //int projUniform = glGetUniformLocation(shaderProgram,"projection");
     //glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(projection));
  
      glm::mat4 projection{1.f};
      projection = glm::ortho(0.f,1920.f,0.f,1080.f,-1.f,1.f);
      int projUniform = glGetUniformLocation(shaderProgram,"projection");
      glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(projection));

     int colUniform = glGetUniformLocation(shaderProgram,"colorIN");
     glUniform3fv(colUniform,1,glm::value_ptr(color)); 
     
     

    }

    enum{
        QUAD_RED,
        QUAD_GREEN,
        QUAD_BLUE,
        QUAD_PINK
    };

    void changeQuadColor(int colorEnum){
        switch(colorEnum){
            case QUAD_RED:
                color = glm::vec3{255,0,0};
                break;
            case QUAD_GREEN:
                color = glm::vec3{0,255,0};
                break;
            case QUAD_BLUE:
                color = glm::vec3{0,0,255};
                break;
            case QUAD_PINK:
                color = glm::vec3{255,0,255};
                break;
            default:
                color = glm::vec3{0,255,255};
        }
    }
   

    sQuad(GLuint shaderProg, float xI = 0, float yI = 0, float zI = 0) : x(xI), y(yI), z(zI), shaderProgram(shaderProg){
        value = rand() % modulus;
        //ensure it is non zero
        ++value;
        scaleY = value;
        
        //create buffers
        glGenVertexArrays(1, &VAO); 
        glBindVertexArray(VAO);

       
        glGenBuffers(1,&VBO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

      
        glGenBuffers(1,&IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

     
        //format arrays
        //xyz
        glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 6* sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        //rgb
        glVertexAttribPointer(1,3, GL_FLOAT,GL_FALSE, 6* sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
     
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(GLuint),&indices[0],GL_STATIC_DRAW);
     
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
     
        checkError(__FILE__,__LINE__);


    }

    void setXYZ(float xI, float yI, float zI){
      x = xI;
      y = yI;
      z = zI;
    }

    void setShaderProg(GLuint shaderProg){
        shaderProgram = shaderProg;
    }

    void cleanup(){

         //delete vertex buffer
        glDeleteBuffers(1,&VBO);
        //delete index buffer
        glDeleteBuffers(1,&IBO);
        //delete vertex array object
        glDeleteVertexArrays(1,&VAO);

        cleaned = true;
    }

    ~sQuad(){
        // if(!cleaned){
        //    cleanup();
        // }
    }

    float x = 0.f, y = 0.f, z = 0.f;
    int value = 0;
    int modulus = 10;
    
    bool cleaned = false;

    GLuint VBO;
    GLuint IBO;
    GLuint VAO;
    int quadVertSize = vertices.size();

    glm::vec3 color{255,0,0};
     

    

    float scaleY = 1.f; //member
    float scaleX = 0.1f; //member

    GLuint shaderProgram;

    friend bool operator<(const sQuad& lhs,const sQuad& rhs){
      return lhs.value < rhs.value;
    }
    sQuad(const sQuad& rhs){
      *this = rhs;
    }
    friend bool operator>(const sQuad& lhs,const sQuad& rhs){
      return lhs.value > rhs.value;
    }
    friend bool operator<=(const sQuad& lhs,const sQuad& rhs){
      return lhs.value <= rhs.value;
    }

    

};



}//namespace shb