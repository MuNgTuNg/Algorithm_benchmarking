#pragma once
#include <iostream>
#include <stack>
namespace shb{

struct sNode
{

	int value;
	sNode *next;
};
void printList(sNode*);
sNode* addListNodeBegin(sNode**, int);
sNode* addListNodeAt(sNode*, int, int);
sNode* addListNodeEnd(sNode* , int);
void swapNodes(sNode*&,int, int);
void swapNodes(sNode*& head,sNode*& left, sNode*& right);
sNode* getLast(sNode* head);
sNode* getMid(sNode* head);

//sorting
void bubbleSortLinkedList(sNode*& head);

void quickSortLinkedList(sNode*head);
void quickSortLinkedList(sNode* first, sNode* last);
sNode* partiion(sNode* first, sNode* last);

sNode* merge(sNode* left, sNode* right);
void mergeSortLinkedList(sNode** head);

void reverseLinkedList(sNode*& head);


void listDriverProgram();
}//namespace shb