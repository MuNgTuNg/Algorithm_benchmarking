/*
                        Finds maximum Sum subarray
*/
#include <algorithms/sAlgo.hpp>
namespace shb{

class sKadanes : public sAlgorithm{
    public:
     sKadanes(std::vector<int>& vecIn) : vec(vecIn), sAlgorithm("Kadanes"){}
    
    public:
     void runAlgo() override{
      kadanes();
     }

    int kadanes()  {
       int n = vec.size();
       int maxSum = INT_MIN;
       //for all numbers in array
       for (int i = 0; i <= n - 1; i++) {
         //reset the current sum
         int currSum = 0;

         //for the entire array starting from previously iterated place
         for (int j = i; j <= n - 1; j++) {
           //add current value from vector
           currSum += vec[j];

           //update the maximum
           if (currSum > maxSum) {
             maxSum = currSum;
           }
         }
       }
       std::cout << "Maximum contiguous sum = " << maxSum << "\n";
       return maxSum;
    }

    std::vector<int>& vec;
};

}