#pragma once
#include <iostream>
#include <stack>
namespace shb{

struct sNodeLL
{

	int value;
	sNodeLL *next;
};
void printList(sNodeLL*);
sNodeLL* addListNodeBegin(sNodeLL**, int);
sNodeLL* addListNodeAt(sNodeLL*, int, int);
sNodeLL* addListNodeEnd(sNodeLL* , int);
void swapNodes(sNodeLL*&,int, int);
void swapNodes(sNodeLL*& head,sNodeLL*& left, sNodeLL*& right);
sNodeLL* getLast(sNodeLL* head);
sNodeLL* getMid(sNodeLL* head);

//sorting
void bubbleSortLinkedList(sNodeLL*& head);

void quickSortLinkedList(sNodeLL*head);
void quickSortLinkedList(sNodeLL* first, sNodeLL* last);
sNodeLL* partiion(sNodeLL* first, sNodeLL* last);

sNodeLL* merge(sNodeLL* left, sNodeLL* right);
void mergeSortLinkedList(sNodeLL** head);

void reverseLinkedList(sNodeLL*& head);


void listDriverProgram();
}//namespace shb