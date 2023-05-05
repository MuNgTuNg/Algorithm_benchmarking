
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
  if(tree){
    binaryTreeDriverProgram();
  }
  if(list){
    listDriverProgram();
  }
  if(graph){
    graphDriverProgram();
  } 
 
  if(algorithms){
    sAlgorithm algo{};
    std::vector<int> vec;
    int numRandomNumbers = 20;
    int modulus = 1000;
    for(int i = 0; i < numRandomNumbers; ++i){
        vec.push_back(rand()%modulus);
    }
    algo.setAlgo(new sQuickSort<int>(vec));
    algo.run();

    for(int i = 0; i < vec.size(); ++i){
      std::cout << vec[i] << " ";
    }
    std::cout << "\n";
    // algo.setAlgo(new sBogoSort(vec));
    // algo.run();
    // algo.setAlgo(new sBinarySearch(vec,value));
    // algo.run();
  } 


  if(graphics){

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
  quadShaderProgram = glCreateProgram();
  
  //attach shaders
  glAttachShader(quadShaderProgram, vertShaderHandle);
  glAttachShader(quadShaderProgram, fragShaderHandle);
  //link program
  glLinkProgram(quadShaderProgram);

  checkError(quadShaderProgram, SHADER_PROGRAM);

  //delete shaders
  glDetachShader(quadShaderProgram,vertShaderHandle);
  glDetachShader(quadShaderProgram,fragShaderHandle);
  glDeleteShader(vertShaderHandle);
  glDeleteShader(fragShaderHandle);

  checkError(__FILE__,__LINE__);


  //»»» CREATE SCENE «««
  //create quads
  
  for(int i = 0; i < quadAmount; ++i){

    //create quads
    sQuad quad{quadShaderProgram};

    //quad.scaleX = 5.f/quadAmount;
    //attempt at dividing the screen by the amount of quads being rendered TODO::
    quad.scaleX = 10.f/quadAmount;
    float offsetX = ((0.1f/(float)quadAmount)*i) -5.f;
    
    //puts all of the quads at an equal level at the bottom of the screen
    float offsetY = -5.f;
    offsetY += (quad.scaleY/2);
    
    //sets the quads in place in relation to the offsets calculated
    //TODO:: calculate proper offsetX
    quad.setXYZ((i*0.1f)+ offsetX, offsetY ,-10.f);
    
    quads.push_back(quad);
  }


  
  



   
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
    glUseProgram(quadShaderProgram);


    
    // modify matrices each frame
    controls(window, quads[0]);

   



    for( auto quad : quads){
     quad.update();
     quad.draw();
    }
  

    //swap buffers
    glfwSwapBuffers(window.handle()); 
    //poll events
    glfwPollEvents();           //have any window events happened? 

    endTime = clock::now();
    //std::cout<< "Time taken: " << delta << "ms\n\n";

    if(glfwGetKey(window.handle(),GLFW_KEY_Q) == GLFW_PRESS){
      break;
    }
  }
   
   

   //CLEANUP QUADS
  for( int i = 0; i< quads.size(); ++i){
    quads[i].cleanup();
  }

  } //if graphics
}

}//namespace shb