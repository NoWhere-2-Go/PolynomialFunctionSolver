//
// Created by Brady Cash on 11/8/21.
// BPC210000

#include "LinkedList.h"
#include "iostream"
using namespace std;

LinkedList::LinkedList() {
    Head = nullptr;
    Length = 0;
}

LinkedList::LinkedList(const LinkedList& sourceList) {
    
    if (sourceList.Head == nullptr) {   //if source list is empty
        return;
    }
    
    Node* sourceHead = sourceList.Head;     //A copy of the source list head used for traversal
    Head = new Node;                        //allocate a new node in memory
    Head->setCoef(sourceHead->getCoef());   //assign head Coeficient to sourceHeads
    Head->setExp(sourceHead->getExp());     //Basically same, but this time with exponents
    Head->setNext(nullptr);                 //Set next to nullptr as we will fill this inside the loop
    Node* curr = Head;                      //create a node named curr to use when making a copy
    
    //move sourceHead to it's next node since we just copied the first
    sourceHead = sourceHead->getNext();
    
    while (sourceHead)
    {
        //allocate new memory for curr next
        curr->setNext(new Node);
        //point to this node^
        curr = curr->getNext();
        //copy 
        curr->setExp(sourceHead->getExp());
        curr->setCoef(sourceHead->getCoef());
        //set next to nullptr just as a default
        curr->setNext(nullptr);
        sourceHead = sourceHead->getNext();
    }
    setLength(sourceList.getLength());
}

void LinkedList::operator+=(Node *node1) {
    //LinkedList tempList;
    Node *tempNode = getHead();

    //traverse to the last node of the list
    while (tempNode != nullptr)
    {
        if (tempNode->getNext() == nullptr) {   
            tempNode->setNext(node1);       //point next of last node to the new node
            setLength(Length + 1);          //increment the length since we just added a new node
            break;
        }
        tempNode = tempNode->getNext();
    }
    
}



Node *LinkedList::merge(Node *node1, Node *node2) {
    Node* newNode;
    //Base case: return the other half if  one of them is nullptr
    if(node1 == nullptr)
        return node2;
    else if(node2 == nullptr)
        return node1;

    //compare the value
    if (node1->getExp() > node2->getExp())
    {
        newNode = node1;                                    //assign the newnode to the Node that contains a greater value
        newNode->setNext(merge(node1->getNext(), node2));   //recursive call to get next node
    } else
    {
        newNode = node2;
        newNode->setNext(merge(node1, node2->getNext()));
    }

    return newNode;
}

void LinkedList::sortHelper(Node *&head) {
    if(head->getNext() != nullptr)		//check if at last node
    {
        Node* head1;
        Node* head2 = head;             //assign head to head 2. Head 2 will point to second half of the linked list
        int len = listLength(head);
        //list2->setHead(head2);
        for(int i=0; i<len/2;i++)	    //use for loop to increment the pointer 2 to the mid-position
        {
            head1 = head2;			    //assign head1 to any node head2 points to
            head2 = head2->getNext();	//in order to put NULL terminate for the first half of the linked list
        }

        head1->setNext(nullptr);		//end first half of the linked list
        head1 = head;
        sortHelper(head1);            //recursive call 
        sortHelper(head2);            //recursive call
        head = merge(head1, head2);   //head's the sorted list 
    }
}

//function to get length of list. Created solely for the sort function & setHead
//previously used the Length field, but it never changes so that led to issues
int LinkedList::listLength(Node *head) {
    Node* temp = head;
    int count = 0;
    while (temp != nullptr){
        count++;
        temp = temp->getNext();
    }
    return count;
}

void LinkedList::sortList() {
    sortHelper(Head);
}

Node *LinkedList::operator[](int pos) {
    //if position you are searching for is greater than length
    if (pos > Length-1) {
        return nullptr;
    } 
    else if (pos < 0){  //check if user entered a negative position
        return nullptr;
    }else {
        int counter = 0;
        Node *tempNode = Head;
        //traverse list until a counter is equal to the pos
        while (tempNode != nullptr) {
            if (counter == pos) {
                return tempNode;
            } else {
                counter++;
                tempNode = tempNode->getNext();
            }
        }//end of traversal loop
    }
    return nullptr;     //return nullptr if we reach the end of the end of list and haven't found the position
}

std::ostream &operator<<(std::ostream &stream, LinkedList source) {
    for (int i = 0; i < source.getLength(); ++i) 
    {
        if (source[i]->getCoef() < 0 && i == 0) //check if the first number is negative
            stream << '-';                      //if it is print a negative sign before it
        stream << source[i];
        if (source[i]->getNext() != nullptr && source[i+1]->getCoef() < 0)  //check if the next number is negative
        {
            stream << " - ";                    //input a minus sign into stream before it
        } 
        else if (source[i]->getNext() != nullptr && source[i+1]->getCoef() > 0) //check if the next number is positive
            stream << " + ";                    //input a plus sign before it into stream
    }
    return stream;
}

void LinkedList::deconstruct(Node* node) 
{
    if (node == nullptr)
        return;
    Node* curr = node;              //hold the first node of the linked list
    Node* temp = curr->getNext();;  //hold node after first node of list
    curr->setNext(nullptr);
    deconstruct(temp);
}

LinkedList::~LinkedList() {         //deconstructor, calls recursvie deconstructor helper function
    deconstruct(Head);
}

