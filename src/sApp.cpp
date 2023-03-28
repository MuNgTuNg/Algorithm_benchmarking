
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
  if(list){
  sNode* head = new sNode();
  head->value = 1;
  head->next = NULL;

  addListNodeEnd(head,2);
  addListNodeEnd(head,3);
  addListNodeEnd(head,4);
 
  //swapNodes(&head, &head->next->next); //TODO swapping and sorting
  printList(head);
  }//enmd of list code


  if(graph){

  
  sGraph graph;

  graph.addvertex("London");
  graph.addvertex("Manchester");
  graph.addvertex("Liverpool");
  graph.addvertex("China");
  graph.addvertex("Brazil");
  
  graph.addedge("London","Liverpool",20);
  graph.addedge("Manchester","Liverpool",30);
  graph.addedge("Liverpool","Manchester",30);
  graph.addedge("Liverpool","London",50);
  graph.addedge("London","Brazil",50);
  graph.addedge("Brazil","London",50);
  graph.addedge("London","China",770);
  graph.addedge("China","London",770);
   
  graph.dfs("China");

  // std::cout << "Route: " << graph.vertices["London"]->name
  // << " to " <<graph.vertices["London"]->edges[0].destination->name
  // << " to " <<graph.vertices["London"]->edges[1].destination->name << "\n";
  // std::cout <<  "Cost: " << graph.vertices["London"]->edges[0].cost + graph.vertices["London"]->edges[1].cost << "\n" ;

  } //if graph
 
  if(algorithms){
    
    std::vector<int> vec;
    int numRandomNumbers = 20;
    generateRand(vec,numRandomNumbers,1000);
    //vec = {7,6,-1,4,3,-7,1};
    //algo.setAlgo(new sBubbleSort(vec));
    //algo.run();

    // algo.setAlgo(new sBogoSort(vec));
    // algo.run();

    // algo.setAlgo(new sMergeSort(vec));
    // algo.run();
    
    // int value = 5;
    // algo.setAlgo(new sBinarySearch(vec,value));
    // algo.run();

  } //if algorithms


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
  GLuint quadShaderProgram = glCreateProgram();
  
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
  std::vector<sQuad> quads;
  int quadAmount = 100;

  for(int i = 0; i < quadAmount; ++i){

    //create quads
    sQuad quad{quadShaderProgram};

    //quad.scaleX = 5.f/quadAmount;
    //attempt at dividing the screen by the amount of quads beind rendered TODO::
    quad.scaleX = 10.f/quadAmount;
    float offsetX = ((10.f/(float)quadAmount)*i) -5.f;
    
    //puts all of the quads at an equal level at the bottom of the screen
    float offsetY = -5.f;
    offsetY += (quad.scaleY/2);
    
    //sets the quads in place in relation to the offsets calculated
    //TODO:: calculate proper offsetX
    quad.setXYZ((i*0.1f)+ offsetX, offsetY ,-10.f);
    
    quads.push_back(quad);
  }


  algo.setAlgo(new sBubbleSort(quads));
  



   
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

    if(glfwGetKey(window.handle(),GLFW_KEY_R) == GLFW_PRESS){
      algo.run();
   
      for(int i = 0; i < quads.size(); ++i){
        float offsetX = ((10.f/(float)quadAmount)*(i*0.1)) -5.f;

        //puts all of the quads at an equal level at the bottom of the screen
        float offsetY = -5.f;
        offsetY += (quads[i].scaleY/2);

        quads[i].setXYZ((i*0.1f)+ offsetX, offsetY ,-10.f);

        std::cout << quads[i].value << " ";
      }
    }



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