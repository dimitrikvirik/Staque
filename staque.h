#pragma once
#ifndef __Staque__
#define __Staque__


#include <iostream>
#include <new>
#include <assert.h>

using namespace std;
typedef int StaqueElement;

class Staque
{
private:
   friend class Staque;
   unsigned int sizeStaque = 0; //Size of Staque
   unsigned int oddN = 0; //number of Odds
   unsigned int evenN = 0; //number of Even

    /*** Node class ***/
   class Node
   {
       friend class Staque;
       StaqueElement data;
       int rank;
       Node* next;
       Node* back;
       //--- Node constructor
       Node(StaqueElement value, int rank, Node* linkNext = 0, Node* linkBack = 0)
           : data(value), rank(rank), next(linkNext), back(linkBack)
       {}
       //Change Element Link
       void ChangeLink(Node* linkNext, Node* linkBack)
       {
           next = linkNext;
           back = linkBack;
       }
       friend ostream& operator<<(ostream& out, Node& node) {
           out << node.data;
       }
   };

   typedef Node* NodePointer;

   /***** Data Members *****/
   NodePointer FirstPtr;
   NodePointer LastPtr;
   //get Front Element
   NodePointer& Begin();
   //get Last Element
   NodePointer& End();

public:
    /***** Function Members *****/
    /***** Constructors *****/
    Staque();
    /***** Destructor *****/
     ~Staque();

    //Add New Element in Staque
    void push(const StaqueElement& value);

    //Check if Staque is Empty
    bool empty() const;
    //Print All Elements
    void display(ostream& out = cout) const;
    //Print by Reverse All Elements
    void rdisplay(ostream& out = cout) const;
    //Delete Elements even And Odd
    void pop(int evenN, int oddN);
    //Delete some elements
    void pop(const int& number);

    //Operator [] Reload
    int& operator[](const int& index);
    //Clear Staque
    void clear();
    //get Size of Staque
    int size() const;


}; // end of class declaration
//Implemation

//Constructor
inline Staque::Staque()
    : LastPtr(0), FirstPtr(0)
{}
inline Staque::~Staque() {
    if (!empty()) {
        clear();
    }
}
//--- Definition of push()
inline void Staque::push(const StaqueElement& value)
{
    sizeStaque++;

    //If Empty
    if (empty()) {
        FirstPtr = new Staque::Node(value, sizeStaque, 0, 0);
        LastPtr = FirstPtr;
    }
    else if (sizeStaque == 2) {
        //If Even
        if (value % 2 == 0) {
            FirstPtr = new Staque::Node(value, sizeStaque, FirstPtr, 0);
            LastPtr->ChangeLink(0, FirstPtr);
        }
        //If Odd
        else {
            LastPtr = new Staque::Node(value, sizeStaque, 0, FirstPtr);
            FirstPtr->ChangeLink(LastPtr, 0);
        }
    }
    else {
        //If Even
        if (value % 2 == 0) {
            FirstPtr = new Staque::Node(value, sizeStaque, FirstPtr);
            FirstPtr->next->ChangeLink(FirstPtr->next->next, FirstPtr);
        }
        //If Odd
        else {
            LastPtr = new Staque::Node(value,  sizeStaque, 0, LastPtr);
            LastPtr->back->ChangeLink(LastPtr, LastPtr->back->back);
        }

    }

    //If Even
    if (value % 2 == 0) {
        evenN++;
    }
    //If Odd
    else {
        oddN++;
    }
}
//--- Definition of display()
inline void Staque::display(ostream& out) const
{
    for (NodePointer ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
        out << ptr->data << " ";
        //Debuging
        //out << ptr->rank << endl;
    }
    out << endl;
}
//--- Definition of rdisplay()
inline void Staque::rdisplay(ostream& out) const
{
    for (NodePointer ptr = LastPtr; ptr != 0; ptr = ptr->back) {
        out << ptr->data << " ";
    }
}
//--- Definition of empty()
inline bool Staque::empty() const
{
    return FirstPtr == 0;
}
//--- Definition of pop with two parametr()
inline void Staque::pop(int evenN, int oddN) {
    //If try delete all elements
    if (evenN + oddN == sizeStaque) {
        clear();
    }
    else {
        //Check Condition
        bool Condition = !empty() && evenN <= this->evenN && oddN <= this->oddN && evenN >= 0 && oddN >= 0 && evenN + oddN < sizeStaque;
        assert(Condition);
        //Main Function Code
        this->evenN -= evenN;
        this->oddN -= oddN;
        this->sizeStaque -= evenN + oddN;
        NodePointer ptr;
        if (evenN > 0 && oddN > 0)
            //LIFO
            while (true) {
          
                //If Front Element rank more than Back
                 if (FirstPtr->rank > LastPtr->rank && evenN > 0) {
                    //Delete First Element
                    evenN--;
                    ptr = FirstPtr->next;
                    ptr->ChangeLink(ptr->next, 0);
                    //Debuging
                    //clog << "Deleted FirstPtr with " << FirstPtr->data << endl;
                    delete FirstPtr;
                    FirstPtr = ptr;
                }
                //If Front Element rank more than Back
                else if (FirstPtr->rank < LastPtr->rank && oddN > 0) {
                    //Delete Last Element
                    oddN--;
                    ptr = LastPtr->back;
                    ptr->ChangeLink(0, ptr->back);
                    //Debuging
                    //clog << "Deleted LastPtr with " << LastPtr->data << endl;
                    delete LastPtr;
                    LastPtr = ptr;
                }

                else {
                    bool ConditionLIFO = evenN == 0 && oddN == 0; //If Function not End Success
                    assert(ConditionLIFO);
                    break;
                }
            }
    }
}
//--- Definition of pop with one parametr()
inline void Staque::pop(const int& number) {
    //If try delete all elements
    if (number == sizeStaque) {
        clear();
    }
    else {
        bool Condition = number > 0 && number <= sizeStaque;
        assert(Condition);
        this->sizeStaque = evenN + oddN;
        NodePointer ptr;
        for (int i = 0; i < number; i++) {
            //If Front Element rank more than Back
            if (FirstPtr->rank > LastPtr->rank && evenN > 0) {
                //Delete First Element
                evenN--;
                ptr = FirstPtr->next;
                ptr->ChangeLink(ptr->next, 0);
                //Debuging
                //clog << "Deleted FirstPtr with " << FirstPtr->data << endl;
                delete FirstPtr;
                FirstPtr = ptr;
            }
            //If Front Element rank more than Back
            else if (FirstPtr->rank < LastPtr->rank && oddN > 0) {
                //Delete Last Element
                oddN--;
                ptr = LastPtr->back;
                ptr->ChangeLink(0, ptr->back);
                //Debuging
                //clog << "Deleted LastPtr with " << LastPtr->data << endl;
                delete LastPtr;
                LastPtr = ptr;
            }
            else {
                bool ConditionLIFO = evenN == 0 && oddN == 0; //If Function not End Success
                assert(ConditionLIFO);
                break;
            }
        }
    }
}

//Index operator Reload
inline int& Staque::operator[](const int& index) {
    bool ConditionRange = !empty() && index >= 0 && index <= size();
    assert(ConditionRange);
    NodePointer ptr = FirstPtr;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr->data; 
}
//Delete All elements
inline void Staque::clear() {
    bool StaqueEmpty = !empty();
    assert(StaqueEmpty);
    NodePointer ptr = FirstPtr;
    while (ptr != 0) {
        ptr = FirstPtr->next;
        delete FirstPtr;
        FirstPtr = ptr;
    }
    LastPtr = 0;
    FirstPtr = 0;
    
}
inline int Staque::size() const{
    return sizeStaque;
}

#endif // !__Staque__