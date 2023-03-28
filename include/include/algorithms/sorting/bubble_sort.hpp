#pragma once

//std
#include <vector>

#include <algorithms/sAlgo.hpp>

/*
                        Bubble Sort:
                            Space complexity = O(1)
                                Bubble sort takes up no extra space as it doesn't store anything or use any data structures

                            Time complexity = O(n²)
                                Outer loop performs N comparisons
                                Inner loop performs N comparisons
                                therefore N*N = n²
                                therefore worst case time complexity is O(n²)

*/

namespace shb{

template<typename T>
class sBubbleSort : public sAlgorithm{
   public:
    sBubbleSort(std::vector<T>& vecIn) : sAlgorithm("Bubble Sort"), vec(vecIn) {}
    
   private:
    void runAlgo() override{
        bubbleSort();
    }
     
    
    void bubbleSort(){
        
        if(vec.size() == 0){ //if the array is empty, it's already sorted
            return;
        }
      
      for(int j = 0; j < vec.size()-1; j++){    //iterate through array
        for(int i = j; i <vec.size(); i++){ //for every element in the array, iterate through it again after the current index in the first iteration
            if(vec[i] < vec[j]){          //if the next value is smaller then the previous, swap it
                T temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            
        }
      }

    }
    
    std::vector<T>& vec{};
};

}//namespace shb