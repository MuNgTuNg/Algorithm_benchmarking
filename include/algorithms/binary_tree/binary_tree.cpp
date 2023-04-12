#include "binary_tree.hpp"

namespace shb{

sNodeBT* addNodeBT(int value){
  sNodeBT* temp = new sNodeBT();
  temp->data = value;
  temp->left = nullptr;
  temp->right = nullptr;
  return temp;
}

void addNodeBT(sNodeBT** root, int value){
  if(!(*root)){
    *root = addNodeBT(value);
    return;
  }

  sNodeBT* currNode = *root;
  sNodeBT* parentNode;

  while(true){
    parentNode = currNode;

    if(currNode->data < value){
      currNode = currNode->left;
      if(!currNode){
        parentNode->left = addNodeBT(value);
        return;
      }
    }
    else{
      currNode = currNode->right;
      if(!currNode){
        parentNode->right = addNodeBT(value);
        return;
      }
    }
  }
}

void inorderTraversal(sNodeBT* root){
  if(!root){
    return;
  }
  inorderTraversal(root->left);
  std::cout << root->data << " ";
  inorderTraversal(root->right);
}
void preorderTraversal(sNodeBT* root){
  if(!root){
    return;
  }
  std::cout << root->data << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}
void postorderTraversal(sNodeBT* root){
  if(!root){
    return;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  std::cout << root->data << " ";
}

int maxDepthBT(sNodeBT* root){
  if(!root){
    return 0;
  }
  int left = maxDepthBT(root->left);
  int right = maxDepthBT(root->right);
  return std::max(left, right ) +1;
}



void levelOrderTraversal(sNodeBT* root){
  std::queue<sNodeBT*> que;
  que.push(root);

  while(!que.empty()){

    sNodeBT* curr = que.front();
    que.pop();
    std::cout << curr->data << " ";

    if(curr->left){
      que.push(curr->left);
    }
    if(curr->right){
      que.push(curr->right);
    }
  }
}

void binaryTreeDriverProgram() {
  sNodeBT* root = addNodeBT(1);
  root->left = addNodeBT(2);
  root->right = addNodeBT(3);
  root->left->left = addNodeBT(4);
  root->left->right = addNodeBT(5);

  // sNodeBT* root = nullptr;

  // addNodeBT(&root,50);
  // addNodeBT(&root,25);
  // addNodeBT(&root,75);
  // addNodeBT(&root,12);
  // addNodeBT(&root,37);
  // addNodeBT(&root,43);
  // addNodeBT(&root,30);   

  std::cout << "Preorder traversal: ";
  preorderTraversal(root);
  std::cout << "\n";

  std::cout << "Postorder traversal: ";
  postorderTraversal(root);
  std::cout << "\n";

  std::cout << "Inorder traversal: ";
  inorderTraversal(root);
  std::cout << "\n";

  std::cout << "Level order traversal: ";
  levelOrderTraversal(root);
  std::cout << "\n";

  std::cout << "Max depth: " << maxDepthBT(root) << "\n";

  
}
}//namespace shb