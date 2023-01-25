#pragma once



// Merge sort in C++

#include <iostream>
#include <vector>
using namespace std;

// Merge two subarrays L and M into arr
void merge(std::vector<int>& arr, int p, int q, int r) {  //TODO comb through this
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
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







//int depth = 0;
// Divide the array into two subarrays, sort them and merge them
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
