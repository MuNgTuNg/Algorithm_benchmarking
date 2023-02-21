#pragma once

//std
#include <iostream>
#include <vector>

//algos
#include <algorithms/sAlgo.hpp>

namespace shb{

/* 
                 Binary Search
                    Space complexity = O(1)
                        Binary search does not take up any extra space, so works
                        in constant space

                    Time complexity = O(log n)
                        Best case time complexity is O(1) when the middle value exactly
                        matches the target number.

                        worst case is O(log n), where each search makes the necessary search
                        half as large by dividing by 2. A logarithm is the opposite of an exponential
                        function. 
                        e.g x = y² is the same as  x = log(y)2

Binary search is a divide and conquer algorithm, designed to optimise the search for a given value. 

*/


template<typename T >
class BinarySearch : public sAlgorithm{
   public:
    
    //takes params for search in constructor
    BinarySearch(std::vector<T> vecIn, T targetIn) : sAlgorithm("binarySearch"), vec(vecIn),target(targetIn) {}
    
   private:

    void runAlgo() override{
        foundIndex = binarySearch(vec,target);  //search for target value and return if found
        if(foundIndex != -1){
            std::cout << "value " << target << " found at index " << foundIndex << "\n";
        }else{
            std::cout << "value " << target << " not found\n";
        }
    }

    //implementation
    int binarySearch(std::vector<T>& vec, T target){
        int l = 0;                 //left is start of array
        int r = vec.size() - 1;    //right is end of array
        while(l <= r){             //while there is still array to search
            int m = l + ((r-l)/2); //find the middle
            if(vec[m] > target ){  //if the value is more than our target
                r = m - 1;         //shrink the search to just the left side, past the middle
            }
            else if(vec[m] < target){ //if the value is less than our target
                l = m + 1;            //shrink the search to just the right side, past the middle
            } 
            else{                       //indexed value matches target
                return m;               //return it's index
            }
        }
        return -1;  //if nothing is found, return a negative value
    }
    
    //vector to search, target to search for, and the index when found if found
    std::vector<T> vec{};
    T target;
    int foundIndex = -1;
};

}//namespace shb
