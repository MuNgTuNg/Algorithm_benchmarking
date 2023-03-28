#pragma once
#include <iostream>
namespace shb{


struct sNode{
    int value;
    sNode* next;
};

void printList(sNode*);
sNode* addListNodeBegin(sNode**, int);
sNode* addListNodeAt(sNode*, int, int);
sNode* addListNodeEnd(sNode* , int);
void swapNodes(sNode**, sNode**);

}//namespace shb