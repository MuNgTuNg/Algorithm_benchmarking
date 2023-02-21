
#include <glad.c>
#include <sApp.hpp>
/*

 TODO LIST::
    1. Play with shader toy and see if i can use the screen coords from that to render to a quad
    2. Figure out instancing to see if i can get that to work 
    3. Tidy up when appropriate
*/



namespace shb{

    
void sApp::run()
{
    
   std::vector<int> vec;
   int numRandomNumbers = 10000;
   //generateRand(vec,numRandomNumbers,1000);
   vec = {12,3,23,214,23,43,534,5,54,3634,34,63452,52};


   // algo.setAlgo(new BubbleSort(vec));
   // algo.run();
   // print(vec);


   algo.setAlgo(new MergeSort(vec));
   algo.run();

   
   int value = 5;
   algo.setAlgo(new BinarySearch(vec,value));
   algo.run();


   
   



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

   checkError(vertShaderHandle,SHADER);
   checkError(fragShaderHandle,SHADER);



  //»»» CREATE SHADER PROGRAM «««
   GLuint squareShaderProgram = glCreateProgram();

   //attach shaders
   glAttachShader(squareShaderProgram, vertShaderHandle);
   glAttachShader(squareShaderProgram, fragShaderHandle);
   //link program
   glLinkProgram(squareShaderProgram);

   checkError(squareShaderProgram, SHADER_PROGRAM);

   //delete shaders
   glDetachShader(squareShaderProgram,vertShaderHandle);
   glDetachShader(squareShaderProgram,fragShaderHandle);
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



   /*
   »»»LOOP VARIABLES«««
   */
   float x = 0;
   float y = 0;
   float z= 0;
    
   float scaleY = 1.f;
   float scaleX = 1.f;

   /*
         MAIN LOOP
   */

  //for timing main loop
   using clock = std::chrono::steady_clock; 
   auto endTime = clock::now();
   auto startTime = clock::now();
   float delta = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();


   while (!glfwWindowShouldClose(window.handle()))
   { 
     startTime = clock::now();
     delta = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    //update window, keep viewport same size as screen
     window.update();
  
    //use these to render the square
     glUseProgram(squareShaderProgram);
     glBindBuffer(GL_ARRAY_BUFFER,VBO);
     glBindVertexArray(VAO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
  
  
     //initialise matrices for use
     glm::mat4 model{1.f};
     glm::mat4 location{1.f};
     glm::mat4 projection{1.f};
     glm::mat4 scale{1.f};
          
     //modify matrices each frame
     controls(window,
              x,
              y,
              z,
              scaleY,
              scaleX);

     
  
     int localModelUniform = glGetUniformLocation(squareShaderProgram,"model");
     glUniformMatrix4fv(localModelUniform,1,GL_FALSE,glm::value_ptr(model));
  
     scale = glm::scale( scale,glm::vec3(scaleX, scaleY,1.f));
     int scaleUniform = glGetUniformLocation(squareShaderProgram,"scale");
     glUniformMatrix4fv(scaleUniform,1,GL_FALSE,glm::value_ptr(scale));
  
     
     location = glm::translate( location,glm::vec3(x, y,-20.f));
     int localViewUniform = glGetUniformLocation(squareShaderProgram,"location");
     glUniformMatrix4fv(localViewUniform,1,GL_FALSE,glm::value_ptr(location));
  
     
     projection = glm::perspective(glm::radians(90.f), (float)1920/1080,0.1f,100.f);
     int projUniform = glGetUniformLocation(squareShaderProgram,"projection");
     glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(projection));
  
  
     //draw currently bound index buffer
     glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
  
     //glBindVertexArray(0);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
      
  
     //swap buffers
     glfwSwapBuffers(window.handle()); 
     //poll events
     glfwPollEvents();           //have any window events happened? 

      endTime = clock::now();
      //std::cout<< "Time taken: " << delta << "ms\n\n";
   

   }



   //delete vertex buffer
   glDeleteBuffers(1,&VBO);
   //delete index buffer
   glDeleteBuffers(1,&IBO);
   //delete vertex array object
   glDeleteVertexArrays(1,&VAO);


    
}

}