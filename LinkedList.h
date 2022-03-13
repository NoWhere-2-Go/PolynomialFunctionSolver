//
// Created by Brady Cash on 11/8/21.
// BPC210000

#ifndef INC_1337PROJECT4_LINKEDLIST_H
#define INC_1337PROJECT4_LINKEDLIST_H
#include "iostream"
#include "Node.h"

class LinkedList {
private:
    Node *Head;
    int Length;
    //sorting helper functions
    Node *merge(Node *node1, Node *node2);
    void sortHelper(Node *&);
public:
    LinkedList();   //default constructor
    LinkedList(const LinkedList &);    //copy constructor

    //recursive deconstructor helper function
    void deconstruct(Node* node);
    
    //deconstructor
    ~LinkedList();
    
    //accessors-getters
    int getLength() const { return Length; }

    Node *getHead() const { return Head; }

    //mutators-setters
    void setLength(int num) { Length = num; }

    void setHead(Node *node1) {
        Head = node1;
        Length = listLength(node1);
    }

    
    //overloaded += operator
    void operator+=(Node *); 

    int listLength(Node *);

    //csorting function
    void sortList();

    //overloaded [] operator
    Node *operator[](int pos);

    //overloaded << operator
    friend std::ostream &operator<<(std::ostream &stream, LinkedList source);

};

#endif //INC_1337PROJECT4_LINKEDLIST_H
