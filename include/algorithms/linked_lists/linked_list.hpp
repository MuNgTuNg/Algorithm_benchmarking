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
void swapNodes(sNode*&,int, int);
void swapNodes(sNode*& head,sNode*& left, sNode*& right);
void bubbleSortLinkedList(sNode*& head);

void listDriverProgram();
}//namespace shb