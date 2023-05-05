#pragma once 

//OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std lib
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <thread>

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

    enum{
        QUAD_RED,
        QUAD_GREEN,
        QUAD_BLUE,
        QUAD_PINK
    };

    
    
    void controls(sWindow& window, sQuad& quad){


        if(glfwGetKey(window.handle(),GLFW_KEY_R) == GLFW_PRESS){
            sortThread = std::thread(sApp::MTquickSort,0,quads.size()-1,std::ref(quads));
            sortThread.detach();
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_Y) == GLFW_PRESS){
            std::thread sortThread(MTbubbleSort, std::ref(quads));
            sortThread.detach();

            
        }
        if(glfwGetKey(window.handle(),GLFW_KEY_T) == GLFW_PRESS){ //TODO reset

            
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
               
               quads[i] = quad;
            }

          placeQuads();
        }
    }

    void generateRandQuads(int amount, int modulus){
        for(int i = 0; i < amount; ++i){
            quads.push_back(rand()%modulus);
        }
    }


    void placeQuads(){
     
        for(int i = 0; i < quads.size(); ++i){
              float offsetX = ((10.f/(float)quadAmount)*(i*0.1)) -5.5f;
      
              //puts all of the quads at an equal level at the bottom of the screen
              float offsetY = -5.f;
              offsetY += (quads[i].scaleY/2);
      
              quads[i].setXYZ((i*0.1f)+ offsetX, offsetY ,-10.f);
      
              //std::cout << quads[i].value << " ";
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

    int numRandomQuads = 20;
    int maxValueQuad = 1000;
    std::vector<sQuad> quads;
    int quadAmount = 100;
    GLuint quadShaderProgram;


    std::thread sortThread;


//SORTING ALGORITHMS NEED TO MOVE

    static void swap(sQuad* l, sQuad* r){
  
        sQuad temp = *r;
        
        *r = *l; 
        *l = temp;
        
    }

    

    static int partition(int start, int end,std::vector<sQuad>& vec){
        
        //choose start element as pivot
        sQuad pivot = vec[start];
        vec[start].changeQuadColor(QUAD_PINK);
        usleep(10000);
 
        //get pivot's sorted position
        int count = 0;
        for(int i = start+1; i <= end; ++i){
            vec[i].changeQuadColor(QUAD_GREEN);
            usleep(10000);
            if(vec[i] <= pivot){
                
                count++;
            }
            vec[i].changeQuadColor(QUAD_RED);
            
        }
        
        //assign index variable based on pivot's positon
        int pivotIndex = start+ count;
        
        //swap pivot element into it's sorted position
        vec[start].changeQuadColor(QUAD_BLUE);
        swap(&vec[pivotIndex], &vec[start]);
        
        
     
        //pointers to start of segment of array and end
        int i = start;
        int j = end;
 
        //sliding window from the start and end of array
        while(i <= pivotIndex && j > pivotIndex){
            vec[i].changeQuadColor(QUAD_GREEN);
            vec[j].changeQuadColor(QUAD_GREEN);
            
            //skip over all elements smaller or equal to pivot element from the left
            while(vec[i] <= pivot){
                vec[i].changeQuadColor(QUAD_RED);
                i++;
            }
            //skip over all elements larger than pivot element from the right
            while(vec[j] > pivot){
                vec[j].changeQuadColor(QUAD_RED);
                j--;
            }
            //if our indexes are in valid positions, swap elements and skip to the next value
            if(i < pivotIndex && j > pivotIndex){
                swap(&vec[i], &vec[j]);
                vec[i].changeQuadColor(QUAD_RED);
                vec[j].changeQuadColor(QUAD_RED);
                ++i;
                --j;
            }
        }
        //return index of pivot element to divide and conquer
        return pivotIndex;
    }
    

    static void MTquickSort(int start, int end, std::vector<sQuad>& vec){
        //if our start surpasses our end we've reached the base case
        if(start >= end){
            return;
        }
        
        //pivot element should be used to split the array into subarrays
        int pivot = partition(start, end,vec);
        
        //recursively call quicksort on either side of pivot element until array is sorted
        MTquickSort(start, pivot-1,vec);
        MTquickSort(pivot+1, end,vec);
        
    }


    static void MTbubbleSort(std::vector<sQuad>& vec){
        
        if(vec.size() == 0){ //if the array is empty, it's already sorted
          return;
        }
        bool sorted = false;
        while(!sorted){
          for(int j = 0; j < vec.size()-1; j++){    //iterate through array
            vec[j].changeQuadColor(QUAD_GREEN);
            for(int i = j; i <vec.size(); i++){ //for every element in the array, iterate through it again after the current index in the first iteration
              vec[i].changeQuadColor(QUAD_GREEN);
              if(vec[i] < vec[j]){          //if the next value is smaller then the previous, swap it
                
                sQuad temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
                vec[j].changeQuadColor(QUAD_RED);
                vec[i].changeQuadColor(QUAD_RED);
              }
              
              usleep(1000);
                  
            }
          }
          for(int i = 0; i < vec.size(); ++i){
            vec[i].changeQuadColor(QUAD_BLUE);
            usleep(10000);
            if(vec[i] < vec[i-1]){
              break;
            }
            sorted = true;
          }
        }
      

}



    
};
}