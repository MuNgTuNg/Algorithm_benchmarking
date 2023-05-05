


#include <sUtils.hpp>
#include <shapes/sQuad.hpp>

namespace shb{

//read a file into a string
std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


//generate an amount of random numbers into a vector, and chose the range of numbers
void generateRandNumbers(std::vector<int>& vec, int amount, int modulus){
    for(int i = 0; i < amount; ++i){
        vec.push_back(rand()%modulus);
    }
}



//print any vector of anything
template<typename T>
void print(std::vector<T>& vec){
    for(auto x : vec){
        std::cout<< x <<" ";
    }
    std::cout << "\n\n";
}

void print(std::vector<int>& vec){
    for(auto x : vec){
        std::cout<< x <<" ";
    }
    std::cout << "\n\n";
}




}//namespace shb
