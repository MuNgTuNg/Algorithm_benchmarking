#include <chrono>
#include <unistd.h>
#include <iostream>
#include "algorithms/merge_sort.hpp"
#include "algorithms/binary_search.hpp"

int main(){
    
    srand(time(0));
    //std::vector<int> vec={50,38,3,99,82,54,18,9,9,50};
    std::vector<int> vec;

    int numRandomNumbers = 1000000;
 
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

   


    return 0;
}