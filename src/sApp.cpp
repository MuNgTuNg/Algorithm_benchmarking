#include <chrono>
#include <unistd.h>
#include <iostream>

#include <sApp.hpp>
#include <sWindow.hpp>

#include <algorithms/merge_sort.hpp>
#include <algorithms/binary_search.hpp>

#include <glad.c>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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


    while (!glfwWindowShouldClose(window.handle()))
  { 

   //update window, keep viewport same size as screen
    window.update();

       //swap buffers
    glfwSwapBuffers(window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 

  }

   


    
}

}