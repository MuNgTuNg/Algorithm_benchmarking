#pragma once

//std
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>


namespace shb{
std::string readFile(const char *filePath);
void generateRand(std::vector<int>& vec, int amount, int modulus);

template<typename T>
void print(std::vector<T>& vec);
void print(std::vector<int>& vec);

}//namespace shb