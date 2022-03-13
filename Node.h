
#ifndef INC_1337PROJECT4_NODE_H
#define INC_1337PROJECT4_NODE_H
#include "iostream"

class Node {
private:
    double Coef;
    int Exp;
    Node* Next = nullptr;
public:
    Node();     //default constructor
    //overloaded constructor
    Node(double, int);
    
    //accessors-getters
    double getCoef() const {return Coef;}
    int getExp() const {return Exp;}
    Node* getNext() const {return Next;}
    
    //mutators-setters
    void setCoef(double num) {Coef = num;}
    void setExp(int num) {Exp = num;}
    void setNext(Node* ptr) {Next = ptr;}
    
    //overloading << 
    friend std::ostream& operator<<(std::ostream&, const Node*);
    
};//end of Node.h


#endif
