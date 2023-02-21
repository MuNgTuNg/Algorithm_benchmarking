#pragma once

#include <algorithms/sAlgo.hpp>

template<typename T>
class InsertionSort : public sAlgorithm{
    public:
     InsertionSort(std::vector<T>& vecIn) : vec(vecIn), sAlgorithm("Insertion Sort"){}
    
    private:
     void runAlgo() override{
      insertionSort();
     }

    void insertionSort(){
        
    }

    std::vector<T>& vec;
};