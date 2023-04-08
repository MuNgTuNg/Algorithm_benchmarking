#include "linked_list.hpp"
namespace shb{

    //TODO:     quick sort linked list

void printList(sNode* head){
   std::cout << "Head <- ";
 
    while(head != NULL)
    {
        std::cout << head->value << " <-- ";
        head = head->next;
    }
    std::cout << "Tail" << std::endl;
 
    return;
}

sNode* getLast(sNode* head){
    sNode* prev = head;
    while(head){
        prev = head;
        head = head->next;
    }   
    return prev;
}


void swapNodes(sNode*& head,sNode*& left, sNode*& right){ 

    sNode* nodeL = head;
    sNode* prevNodeL = NULL;

    sNode* nodeR = head; 
    sNode* prevNodeR = NULL;

    if(!head) { return; }
    if(right == left) { return; }

    while(nodeL && nodeL != left){
        prevNodeL = nodeL;
        nodeL = nodeL->next;
    }

    while(nodeR && nodeR != right){
        prevNodeR = nodeR;
        nodeR = nodeR->next;
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
 

sNode* partition(sNode* first, sNode* last){
    // pivot is first node, front is also first node
    sNode* pivot = first;
    sNode* front = first;
    int temp = 0;

    //while we still have nodes to process
    while(front!=NULL && front != last){
        //if value is higher
        if(front->value < last->value){
            //pivot is the first value and is swapped with front
            //then iterated
            pivot = first;

            temp = first->value;
            first->value = front ->value;
            front->value = temp;

            first = first->next;
        }
        //iterate front 
        front = front->next;
    }
    //swap first and last
    temp = first->value;
    first->value = last->value;
    last->value = temp;

    //return pivot
    return pivot;
    
}

void quickSortLinkedList(sNode* first, sNode* last){
    //base case
    if(first == last){
        return;
    }
    
    //get the pivot value
    sNode* pivot = partition(first, last);
    
    //recursively partition and sort list until the last value
    if(pivot != NULL && pivot->next != NULL){
        quickSortLinkedList(pivot->next,last);
    }
    //
    if(pivot!=NULL && first!=pivot){
        quickSortLinkedList(first,pivot);
    }
}

//swap values not pointers //TODO
void quickSortLinkedList(sNode*head){
    //send the algorithm the first and last nodes
    quickSortLinkedList(head,getLast(head));
}

void reverseLinkedList(sNode*& head){

    if(!head){
        return;
    }

    std::stack<sNode*> stc;
    
    //push all nodes to stack
    while(head){
        stc.push(head);
        head = head->next;
    }
    
    //create traversal pointer
    sNode* curr = stc.top();
    head = curr;
    
    //while there are still nodes in the stack, assign them to 
    //next pointer
    while(!stc.empty()){
        curr->next = stc.top();
        curr = curr->next;
        stc.pop();
    }

    //when iteration is finished, add a NULL for the tail
    curr->next = NULL;
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
        return new sNode{value,NULL};
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

sNode* getMid(sNode* head){
    sNode* fast = head->next;
    sNode* slow = head;

    while(fast && fast->next){ 
      
            fast = fast->next->next;
            slow = slow->next;
        
    }
    return slow;

}
sNode* merge(sNode* h1,sNode* h2){

    //create current node
    sNode* current = NULL;
    
    //if either are null, return other 
    if(h1 == NULL){
        return (h2);
    }
    else if(h2 == NULL){
        return (h1);
    }
    

    //if the value of left is higher, the current pointer is the 
    //smaller value, and the next is the iterated, returned, recursed smaller value
    if(h1->value <= h2->value){
        current = h1;
        current->next = merge(h1->next,h2);
    }
    else{
        current = h2;
        current->next = merge(h1, h2->next);
    }
        
    //return the smaller value
    return (current);

    
}
 
void mergeSortLinkedList(sNode** headRef){

    //pointer makes head easier to refer to
    sNode* head = *headRef;

    //left right and mid pointer
    sNode* left, *right, *mid;
    
    //if passed in null, or next is null 
    //base case
    if(!head  || !head->next){
        return;
    }

    //fast and slow pointer method
    mid = getMid(head);
    
    //split the list in two at the mid point
    left = head;
    right = mid->next;
    mid->next = NULL;
    
    //recurse for left and right
    mergeSortLinkedList(&left);
    mergeSortLinkedList(&right);
    //recursively merge
    *headRef = merge(left,right);
}



void bubbleSortLinkedList(sNode*& head){

    sNode* end;
    sNode* right;
    sNode* left;
    sNode* prevRight;
    sNode* temp;
    
    //head next isnt null, increment it by assigning it to the right pointr
    for(end = NULL; end != head->next; end = right){
        
        //initialise prevRight and right to the head
        //while rights next pointer isnt null
        //prevRight becomes right and right gets incremented
        for(prevRight = right = head; right->next != end; prevRight = right, right = right->next){

            //left is the next one on from right
            left = right->next;
            
            //if the values need to be swapped
            if(right->value > left->value){
                std::cout << "swapped: " << right->value << " and " << left->value << "\n";

                //right takes left's next pointer
                right->next = left->next;
                //left next becomes right
                left->next = right;

                //check for head
                if(right!=head){
                    prevRight->next = left;
                }
                else{
                    head = left;
                }
                //swap nodes 
                temp = right;
                right = left; 
                left = temp;
                //swapNodes(head,left,right);
            }
        }
        
    }

     
        
    


    
    //if right pointer is larger than left pointer
    //swap right with left
    //left equals right
}


void listDriverProgram(){
  sNode* head = new sNode();
  sNode* currentHead  = head;
  head->value = 4;
  head->next = NULL;

  addListNodeEnd(head,3);
  addListNodeEnd(head,2);
  addListNodeEnd(head,1);
  addListNodeEnd(head,6);
  addListNodeEnd(head,5);

  printList(head);

  quickSortLinkedList(head);
  //swapNodes(head,head->next->next,head->next); 
  printList(head);

  reverseLinkedList(head);
  printList(head);

}


}//namespace shb