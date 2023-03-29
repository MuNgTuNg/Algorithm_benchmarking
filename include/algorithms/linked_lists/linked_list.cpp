#include "linked_list.hpp"
namespace shb{

void printList(sNode* head){
    while(head!=nullptr){
        std::cout << head->value << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

void swapNodes(sNode*& head,int left, int right){ 

    sNode* nodeL = head;
    sNode* prevNodeL = NULL;

    sNode* nodeR = head; 
    sNode* prevNodeR = NULL;

    if(!head) { return; }
    if(right == left) { return; }

    while(nodeL && left != 0){
        prevNodeL = nodeL;
        nodeL = nodeL->next;
        --left;
    }

    while(nodeR && right != 0){
        prevNodeR = nodeR;
        nodeR = nodeR->next;
        --right;
    }

    if(nodeR && nodeL){
        if(prevNodeL){
            prevNodeL->next = nodeR;
        }else{
            head = nodeR;
        }
        if(prevNodeR){
            prevNodeR->next = nodeL;
        }else{
            head = nodeL;
        }

        sNode* temp = nodeR->next;
        nodeR->next = nodeL->next;
        nodeL->next = temp;
    }

  
}


  


sNode* addListNodeBegin(sNode** head, int value){
    if(!head){
        return new sNode{value,nullptr};
    }
    
    //create new node, where head is the next pointer
    sNode* newNode = new sNode{value,*head};
    //replace head with new node
    *head = newNode;
    //return new node
    return newNode;
}

sNode* addListNodeEnd(sNode* head, int value){
    while(head->next){
        head = head->next;
    }
    sNode* newNode = new sNode{value, nullptr};
    head->next = newNode;
    return newNode;
}

sNode* addListNodeAt(sNode* head, int Rindex, int value){
    
    //deal with negative values by just taking the absolute value
    Rindex = abs(Rindex);

    //if index is 0, insert at beginning
    if(Rindex == 0){
        return addListNodeBegin(&head,value);
    }
    //create new node
    sNode* newNode = new sNode();
    newNode->value = value;
    newNode->next = nullptr;

    sNode* curr = head;
    sNode* prev = curr;

    if(!curr){
        return newNode;
    }

    while(curr){

        //if we've reached the index we want
        if(Rindex == 0){
            prev->next = newNode;
            newNode->next = curr;
            //create node, change pointers, return node
            return newNode;
        }

        //move to next node, decrement reverse index 
        prev = curr;
        curr = curr->next;
        Rindex--;
    }

    //we've reached the end, so just add it to the end
    return addListNodeEnd(head,value);

}

void bubbleSortLinkedList(sNode*& head){

    sNode* left = head;
    sNode* right = head;

    int leftIndex = 0;
    int rightIndex = 0;
    
    //while left hasn't hit the end
    while(left){
        //search list for value higher than left
        rightIndex = 0;

        while(right->value < left->value){
            right = right->next;
            rightIndex++;
        }

        //swap values
        swapNodes(head,leftIndex,rightIndex);

        leftIndex = rightIndex;
       
        for(int i = 0; i <= leftIndex; ++i){
            left = left->next;
        }

        leftIndex++;
    }


    
    //if right pointer is larger than left pointer
    //swap right with left
    //left equals right
}


void listDriverProgram(){
  sNode* head = new sNode();
  head->value = 9;
  head->next = NULL;

  addListNodeEnd(head,32);
  addListNodeEnd(head,300);
  addListNodeEnd(head,6876);
  addListNodeEnd(head,6234);
  addListNodeEnd(head,622224);
  bubbleSortLinkedList(head);
  //swapNodes(head,0,2); //TODO sorting
  printList(head);
}

}//namespace shb