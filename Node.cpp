//
// Created by Brady Cash on 11/8/21.
// BPC210000

#include "Node.h"
#include <iostream>
using namespace std;
Node::Node() {
    Coef = 1;
    Exp = 1;
    Next = nullptr;
}

Node::Node(double num1, int num2) {
    Coef = num1;
    Exp = num2;
}

std::ostream& operator<<(std::ostream& stream, const Node* nodeX){
    if(nodeX != nullptr && nodeX->getCoef() != 0){   //check if node exists before anything
        if (nodeX->getCoef() != 1 && nodeX->getExp() != 0)
            stream << std::abs(nodeX->Coef);
        //check if exponent isn't zero and isn't 1
        if (nodeX->getExp() != 0 && nodeX->getExp() != 1) 
            stream << "x^" << nodeX->Exp;
        else if (nodeX->getExp() == 1)  //if exponent is 1 just input x into the stream
            stream << "x";
        if (nodeX->getExp() == 0 && nodeX->getCoef() != 0)
            stream << std::abs(nodeX->getCoef());
    }
    return stream;
}

