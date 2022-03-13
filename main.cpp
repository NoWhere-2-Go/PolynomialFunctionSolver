//Created by Brady Cash
//NetID: Bpc210000
#include <iostream>
#include "Node.h"
#include "LinkedList.h"
#include <fstream>
#include <string>
#include "cmath"
#include <iomanip>

using namespace std;
void populateList();
double calculate(LinkedList, double);
void combineLikeTerms(LinkedList&);
int main() 
{
    populateList();
    return 0;
}



//function that reads the file and creates the nodes and puts them into the list
void populateList(){
    string fileName;
    string line;

    //ask user for file name
    cout << "Enter the name of a file: ";
    cin >> fileName;
    ifstream readFile(fileName);

    if (!readFile){     //if file doesn't open properly
        cout << "\nError, file doesn't exist" << endl;
        return;
    }
    while (!readFile.eof())
    {
        LinkedList newList;
        getline(readFile, line);
        string coef, expo;
        int pos, pos2, x_counter = 0;
        double expVal, result;
        int holder1= -1 , holder2= -1, holder3= -1, holder4= -1, holder5 = -1;

        pos = (int)line.find('(')+1 ;    //find the position after the first parenthesis
        pos2 = (int)line.find(')');  //find where the 2nd parenthesis is
        expVal = stod(line.substr(pos, pos2-2));    //assign expVal to number between the parenthesis

        pos = (int)line.find('=')+2;     //find where the equal sign is
        pos2 = (int)line.find('\n');     //find the end of the line
        string tempLine = line.substr(pos, pos2);


        string term;
        int temp_lineLength = int(tempLine.length());
        for (int i = 0; i <= temp_lineLength; ++i)
        {
            Node* newNode;
            if ((isdigit(tempLine[i]) || tempLine[i] == '.') || tempLine[i] == 'x')
            {
                if (holder1 != -1)  //check if holder1 is holding a position
                    continue;
                else
                    holder1 = i;
            }
            if ((isspace(tempLine[i]) && holder1 != -1) || (holder1 != -1 && i == temp_lineLength))
            {
                if (holder2 != -1)  //check if holder2 is holding a position 
                    continue;
                else
                    holder2 = i;
            }
            if (holder1 != -1 && holder2 != -1){
                term = tempLine.substr(holder1, holder2-holder1);   //create a substring of each term

                //loop thru the term and parse it into coefficient and exponent
                for (int k = 0; k <= (int)term.length(); k++)
                {
                    //create a node. Which we will populate later
                    newNode = new Node();
                    //holder1 cannot be assigned after holder5
                    if (holder4 == -1 && (isdigit(term[k]) || term[k] == '.'))
                    {
                        if (holder3 != -1)  //check if holder3 is holding a position
                            continue;
                        else
                            holder3 = k;
                    }
                    if (term[k] == 'x')
                    {
                        holder4 = k;
                        x_counter++;
                    }
                    //parse the exponent
                    if (term[k] == '^')
                    {
                        holder5 = k+1;
                    }
                    //check if the coefficient has no exponent or x & cannot be assigned after holder5
                    if (k == (int)term.length() && (holder3 != -1 && holder5 == -1))
                    {
                        if (x_counter == 0){
                            holder4 = k;
                            newNode->setExp(0);
                        }
                    }
                    if ((holder3 != -1 && holder4 != -1))   //check if the positions for the coefficient are found
                    {
                        //parse the coefficient
                        coef = term.substr(holder3, holder4-holder3);
                        newNode->setCoef(stod(coef));

                        //check if the coefficient is negative or positive
                        if (tempLine[holder1-2] == '-' || tempLine[holder1-1] == '-')
                        {
                            newNode->setCoef(stod(coef) * -1);  //multiply by -1 to change to negative value
                        }
                    }
                    //assign the exponent to its new parsed value
                    if (holder5 != -1) {
                        expo = term.substr(holder5, term.length() - holder5);
                        newNode->setExp(stoi(expo));

                        //check if the exponent is negative
                        if (term[holder5-1] == '-')
                        {
                            newNode->setExp(stoi(expo) * -1);
                        }
                    }

                    //if at end of list put the nodes into the list
                    if (k == (int)term.length())
                    {
                        //check if list is empty
                        if (newList.getHead() == nullptr)
                        {
                            newList.setHead(newNode);      //make the newNode the head
                        }else
                        {
                            newList += newNode;     //append the newNode to end of list
                        }
                    }

                }//end of term for loop
                holder1 = -1, holder2 = -1, holder3 = -1, holder4 = -1, holder5 = -1;   //reset holder values
                x_counter = 0;
            }//end of if statement for finding the term

            if (i == (int)tempLine.length())
            {
                //calculate result of list 
                result = calculate(newList, expVal);
                newList.sortList();
                combineLikeTerms(newList);
                //print the list and the result
                cout << "\n" << fixed << setprecision(3) << newList << " = ";
                cout << result;
            }

        }//end of for loop for the line


    }//end of while loop for file
    if (readFile.eof()) //close file if at end 
    {
        readFile.close();
    }
}//end of function

//will calculate the result of the equation
double calculate(LinkedList source, double x_num)
{
    double result = 0;
    //check if the list is empty
    if (source.getHead() == nullptr)
        return 0;

    //traverse thru linked list and multiply all the coefficients by x_num raised to the power of exponent
    for (int i = 0; i < source.getLength(); ++i)
    {
        if(source[i]->getExp() != 1)
            result += source[i]->getCoef() * pow(x_num, source[i]->getExp());
        else if(source[i]->getExp() == 1 && source[i]->getCoef() == 1)
            result += x_num;
        else if(source[i]->getExp() == 1 && source[i]->getCoef() != 1)
            result += (x_num * source[i]->getCoef());
        else
            result += source[i]->getCoef();
    }
    return result;
}
//function that will combine like terms and change the list if it has like terms
//list must be sorted before using this function
void combineLikeTerms(LinkedList& source)
{
    Node* temp = nullptr;
    int tempExp;    //will hold the value of a nodes exponent while traversing list
    int len = source.getLength();
    for (int i = 0; i < source.getLength(); ++i) 
    {
        if (source[i]->getNext() != nullptr)   //check if next of the node is null
        {
            temp = source[i]->getNext();    //if not hold the next node
        }
        tempExp = source[i]->getExp();
        if (temp != nullptr) {  //check if temp is null
            while (temp != nullptr)  //traverse the list starting from the node after the i node
            {
                if (tempExp == temp->getExp()) {
                    double res = source[i]->getCoef() + temp->getCoef();    //add the 2 coefficients
                    source[i]->setCoef(res);    //make the nodes new coefficient the result 
                    source[i]->setNext(temp->getNext()); //set the i node next to the i+2 node
                    len--;
                    source.setLength(len);  //decrement the length since we have removed a node
                }
                temp = temp->getNext(); //move to the next node
            }
        }
    }
    
}
