#include <chrono>
#include <unistd.h>
#include <iostream>

#include <glad.c>


#include <sApp.hpp>
#include <sWindow.hpp>
#include <sShader.hpp>
#include <sDebugging.hpp>

#include <algorithms/merge_sort.hpp>
#include <algorithms/binary_search.hpp>


namespace shb{
void sApp::run(){
    
    sWindow window{1920,1080};
   
    srand(time(0));
    //std::vector<int> vec={50,38,3,99,82,54,18,9,9,50};
    std::vector<int> vec;

    int numRandomNumbers = 10;
 
    for(int i = 0; i < numRandomNumbers; ++i){
        vec.push_back(rand());
    }


    //performance benchmarking
    std::cout << "Merge sort on " << numRandomNumbers << " random numbers:\n";
    auto startTime = std::chrono::steady_clock::now();       


    mergeSort(vec);

   
    auto endTime = std::chrono::steady_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout<< "Time taken: " << difference << "ms\n";


    for(int i = numRandomNumbers -10; i < numRandomNumbers; ++i){
       std::cout<< vec[i] << "\n";
    }



 //»»» CREATE SHADERS «««
    GLuint vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertShaderSource = readFile("../shaders/vertShader.vert");
    std::string fragShaderSource = readFile("../shaders/fragShader.frag");
    const char* vertCode = vertShaderSource.c_str();
    const char* fragCode = fragShaderSource.c_str();

    glShaderSource(vertShaderHandle, 1, &vertCode,NULL);
    glShaderSource(fragShaderHandle, 1, &fragCode,NULL);
    glCompileShader(vertShaderHandle);
    glCompileShader(fragShaderHandle);


    //checkError(vertShaderHandle); TODO
    //checkError(fragShaderHandle);

    int  success;
    char infoLog1[512];
    glGetShaderiv(vertShaderHandle, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertShaderHandle, 512, NULL, infoLog1);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog1 << std::endl;
    }

    int  success2;
    char infoLog2[512];
    glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &success2);

    if(!success2)
    {
        glGetShaderInfoLog(fragShaderHandle, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }



    GLuint shaderProgram = glCreateProgram();
    //create shader program

    //attach shaders
    glAttachShader(shaderProgram, vertShaderHandle);
    glAttachShader(shaderProgram, fragShaderHandle);

    //link program
    glLinkProgram(shaderProgram);

    //checkError(shaderProgram); //TODO

    GLint successss;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successss);
    
    if(!successss) {
        char infoLog[512] ;
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << infoLog;
    }


    //delete shaders
    glDetachShader(shaderProgram,vertShaderHandle);
    glDetachShader(shaderProgram,fragShaderHandle);
    glDeleteShader(vertShaderHandle);
    glDeleteShader(fragShaderHandle);

    checkError(__FILE__,__LINE__);


//»»» CREATE BUFFERS «««

    std::vector<GLfloat> quadVertices = 
    { //     COORDINATES     /        COLORS      /   TexCoord  //
       -.5f,-.5f,0.f, .9f,1.f,2.f,
       -.5f,.5f,0.f,  0.f,.5f,2.f,
       .5f,.5f,0.f, 2.f,1.f,.5f,
       .5f,-.5f,0.f, 2.f,.5f,2.f
    };
    std::vector<GLuint> quadIndices = 
    {
       0,1,2,
       0,2,3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //create vertex buffer
    GLuint VBO;
    glGenBuffers(1,&VBO);
    GLuint IBO;
    glGenBuffers(1,&IBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,quadVertices.size()*sizeof(GLfloat), &quadVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);



  //»»»FORMAT ARRAY «««
    //xyz
    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 6* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //rgb
    glVertexAttribPointer(1,3, GL_FLOAT,GL_FALSE, 6* sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,quadIndices.size()*sizeof(GLuint),&quadIndices[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


    checkError(__FILE__,__LINE__);

   //unbind all buffers
    while (!glfwWindowShouldClose(window.handle()))
    { 
   
   //update window, keep viewport same size as screen
    window.update();

  //use these to render the square
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    

   //draw currently bound index buffer
    glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
    
    //glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    

   //swap buffers
    glfwSwapBuffers(window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 

    }

   //delete vertex buffer
   glDeleteBuffers(1,&VBO);
   //delete index buffer
   glDeleteBuffers(1,&IBO);
   //delete vertex array object
   glDeleteVertexArrays(1,&VAO);


    
}

}