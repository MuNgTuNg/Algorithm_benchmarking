#include "linked_list.hpp"
namespace shb{

void printList(sNode* head){
    while(head!=nullptr){
        std::cout << head->value << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

void swapNodes(sNode** left, sNode** right){ //TODO:: swap nodes
    sNode* currL = (*left);
    sNode* currR = (*right);
    sNode* prevL = nullptr;
    sNode* prevR = nullptr;

   // while()
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


}//namespace shb