#pragma once

#include <algorithms/sAlgo.hpp>
template<typename T>
class sQuickSort : public sAlgorithm{
    public:
     sQuickSort(std::vector<T>& inVec) : vec(inVec) sAlgorithm("QuickSort"){}
    
    private:
     void runAlgo() override{
      quickSort();
     }

    void quickSort(){
        
    }

    std::vector<T>&  vec;
};
