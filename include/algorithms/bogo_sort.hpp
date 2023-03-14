#pragma once
#include <vector>
#include <random>

#include <algorithms/sAlgo.hpp>
namespace shb{
class sBogoSort : public sAlgorithm{
    public:
     sBogoSort(std::vector<int>& vecIn) : vec(vecIn), sAlgorithm("sBogoSort"){}
    
    private:
     void runAlgo() override{
      bogoSort();
     }

    bool sorted(){
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i] < vec[i-1]){
                return false;
            }
        }
        return true;
    }

    void bogoSort(){
        
        while(!sorted()){
            for(int i = 0; i < vec.size(); ++i){
                int randM = rand() % vec.size();
                int temp = vec[i];
                vec[i] = vec[randM];
                vec[randM] = temp;
            }
        }
        if(sorted()){
            std::cout <<"SORTED\n";
            for(auto a : vec){
                std::cout << a << " ";
            } std::cout << "\n";
        }
    }

    std::vector<int>& vec;
};

}//namespace shb