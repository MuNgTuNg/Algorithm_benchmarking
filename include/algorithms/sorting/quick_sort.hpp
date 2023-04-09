#pragma once

namespace shb{

#include <algorithms/sAlgo.hpp>
template<typename T>
class sQuickSort : public sAlgorithm{
    public:
     sQuickSort(std::vector<T>& inVec) : vec(inVec), sAlgorithm("QuickSort"){}
    
    private:
    void runAlgo() override{
        quickSort(0, vec.size()-1);
    }

    void swap(int* l, int* r){
        int temp = *r;
        *r = *l; 
        *l = temp;
    }

    int partition(int start, int end){

        //choose start element as pivot
        int pivot = vec[start];
 
        //get pivot's sorted position
        int count = 0;
        for(int i = start+1; i <= end; ++i){
            if(vec[i] <= pivot){
                count++;
            }
        }
        
        //assign index variable based on pivot's positon
        int pivotIndex = start+ count;
        
        //swap pivot element into it's sorted position
        swap(&vec[pivotIndex], &vec[start]);
     
        //pointers to start of segment of array and end
        int i = start;
        int j = end;
 
        //sliding window from the start and end of array
        while(i <= pivotIndex && j > pivotIndex){
            //skip over all elements smaller or equal to pivot element from the left
            while(vec[i] <= pivot){
                i++;
            }
            //skip over all elements larger than pivot element from the right
            while(vec[j] > pivot){
                j--;
            }
            //if our indexes are in valid positions, swap elements and skip to the next value
            if(i < pivotIndex && j > pivotIndex){
                swap(&vec[i], &vec[j]);
                ++i;
                --j;
            }
        }
        //return index of pivot element to divide and conquer
        return pivotIndex;
    }
    

    void quickSort(int start, int end){
        //if our start surpasses our end we've reached the base case
        if(start >= end){
            return;
        }
        
        //pivot element should be used to split the array into subarrays
        int pivot = partition(start, end);
        
        //recursively call quicksort on either side of pivot element until array is sorted
        quickSort(start, pivot-1);
        quickSort(pivot+1, end);
    }

    std::vector<T>&  vec;
};

}//namespace shb