#pragma once

//std
#include <iostream>
#include <string>
#include <vector>


namespace shb{

class sAlgorithm{
  public:

    void run() {
      if(algo){
        //which algorithm is run is decided dynamically
        std::cout << algo->algoName << "\n";
        using clock = std::chrono::steady_clock;  
        auto startTime = clock::now();

        //runs dynamically chosen algorithm
        algo->runAlgo();

        auto endTime = clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout<< "Time taken: " << timeTaken << "ms\n\n";
      }
      else{
        std::cout << "No Algorithm set\n";
        return;
      }
    }
    
   
    //choose which algorithm to use by adding pointer here or in constructor
    void setAlgo(sAlgorithm* algoIn){
      if(algo){
        delete algo;
        algo = nullptr;
      }
      algo = algoIn;
    }
 
    sAlgorithm(sAlgorithm* algoIn) : algo(algoIn){}
    
    ~sAlgorithm(){
      if(algo){
        delete algo;
        algo = nullptr;
      }
    }
    sAlgorithm(){}

    

  protected: 

    //override this function with the algorithms implementation
    virtual void runAlgo(){
      std::cout << "Algorithm derived does not override base class yet\n";
    };

    sAlgorithm(const char* name) : algoName(name){}

    



  private:

    int64_t timeTaken = 0;
    std::string algoName = "No name";
    sAlgorithm* algo = nullptr;


};




}//namespace shb


/*   Template of how to create a new algorithm

#pragma once

#include <algorithms/sAlgo.hpp>
class Foo : public sAlgorithm{
    public:
     Foo() : sAlgorithm("Foo"){}
    
    private:
     void runAlgo() override{
      foo();
     }

    void foo(){}
};

*/

//includes so you only have to include sAlgo in any files
#include <algorithms/searching/binary_search.hpp>
#include <algorithms/sorting/bubble_sort.hpp>
#include <algorithms/sorting/merge_sort.hpp>
#include <algorithms/sliding_window/kadanes_algorithm.hpp>
#include <algorithms/sorting/bogo_sort.hpp>
#include <algorithms/graph/sGraph.hpp>
#include <algorithms/linked_lists/linked_list.hpp>

