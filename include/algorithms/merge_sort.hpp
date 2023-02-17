#pragma once



// Merge sort in C++

#include <iostream>
#include <vector>


// Merge two subarrays L and M into arr
void merge(std::vector<int>& arr, int left, int mid, int right) {  
  

  //split passed array in half
  
  int sizeOfFirstArray = mid - left + 1;  
  int sizeOfSecondArray = right - mid;    

  //create two arrays
  int firstArray[sizeOfFirstArray], secondArray[sizeOfSecondArray];


  
  //copy both halves of the array into new arrays
  for (int i = 0; i < sizeOfFirstArray; i++)
    firstArray[i] = arr[left + i]; 

  for (int j = 0; j < sizeOfSecondArray; j++)
    secondArray[j] = arr[mid + 1 + j]; 


  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0; //sub array 1
  j = 0; //sub array 2
  k = left; //main array

  //while our indexes haven't reached the end
  while (i < sizeOfFirstArray && j < sizeOfSecondArray) {

    
    //compare for smallest
    if (firstArray[i] <= secondArray[j]) { 
      //if first is smaller, assign to indexed spot in passed array
      arr[k] = firstArray[i];
      i++;               //increment index
    }                  
    else {        //if reaches this control, second is bigger, do same for second        
      arr[k] = secondArray[j];
      j++;            
    }
    k++;                //move on to the next contested spot in the passed in array
  }

  //copy remaining elements, usually one, already sorted
  while (i < sizeOfFirstArray) {
    arr[k] = firstArray[i];
    i++;
    k++;
  }

  while (j < sizeOfSecondArray) {
    arr[k] = secondArray[j];
    j++;
    k++;
  }
}


//implementation from memory
void mergeSort(std::vector<int>& vec, int left, int right){


    if(left< right){

        //gets middle of vector
        int mid = left + (right - left)/2;

        // recursively subdivides left side
        mergeSort(vec,left, mid);

        //recursively subdivides right side
        mergeSort(vec,mid+1,right);

        //merge them back together
        merge(vec,left, mid, right);

    }

}

void mergeSort(std::vector<int>& vec){
    mergeSort(vec,0,vec.size()-1);
}






// int depth = 0;
// //Divide the array into two subarrays, sort them and merge them
// void mergeSort(std::vector<int>& arr, int l, int r) {
//     std::cout <<"----------------------------------\n";
//     std::cout << "Depth = " << depth << "\n";
//     std::cout <<"----------------------------------\n\n";

//     ++depth;

//     std::cout << "Vector size = " << r - l << "\n\n";

//     std::cout << "Index Left = " << l << "\n";
//     std::cout << "Index Right = " << r << "\n\n";

//     std::cout<<"Value L =  " << arr[l] << "\n";
//     std::cout<<"Value R = " << arr[r] << "\n\n";
    


//   if (l < r) {
//     // m is the point where the array is divided into two subarrays
//     std::cout<<"l < r = true" << "\n\n";

//     std::cout << l << " + (" << r << " - " << l << ")/2 =" << l+(r-l)/2 << "\n\n"; 
//     int m = l + (r - l) / 2;
//     std::cout<<"M = " << m << "\n\n";

//     std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
//     std::cout << "Subdivide left side\n";
//     std::cout <<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
//     mergeSort(arr, l, m);

//     std::cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
//     std::cout << "Subdivide right side\n";
//     std::cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
//     mergeSort(arr, m + 1, r);

//     // Merge the sorted subarrays
//     std::cout <<">>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<\n";
//     std::cout << "\n" << "MERGING" << "\n";
//     std::cout << ">>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<\n\n";
//     merge(arr, l, m, r);
//   }
//   depth--;
//   std::cout <<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
//   std::cout <<"leaving mergeSort\n";
//   std::cout <<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
// }
