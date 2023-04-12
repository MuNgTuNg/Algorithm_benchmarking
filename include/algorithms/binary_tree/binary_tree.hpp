#pragma once
#include <iostream>
#include <queue>
namespace shb{

struct sNodeBT{
  int data;
  sNodeBT* left;
  sNodeBT* right;
};

sNodeBT* addNode(int value);
void addNodeBT(sNodeBT** root, int value);
void binaryTreeDriverProgram();
void inorderTraversal(sNodeBT* root);
void preorderTraversal(sNodeBT* root);
void postorderTraversal(sNodeBT* root);
int maxDepthBT(sNodeBT* root);
void levelOrderTraversal(sNodeBT* root);
}//namespace shb