#include "section4/Integer.hpp"
#include <iostream>

// Default constructor
Integer::Integer(){
    m_pInt = new int(0);
    std::cout<<"Integer()"<< std::endl;
};

// Deep copy constructor  - pass by reference
// When are objects are passed by reference, always passed by const
Integer::Integer(const Integer &obj){
    std::cout<<"Integer(const)" << std::endl;
    m_pInt = new int(*obj.m_pInt);
};

// Parameterized constructor
Integer::Integer(int value){
    std::cout<<"Integer(int)" << std::endl;
    m_pInt = new int(value);
};

// Move Constructor
Integer::Integer(Integer &&obj){
    std::cout<<"Integer(Integer &&)" << std::endl;
    m_pInt = obj.m_pInt;
    obj.m_pInt = nullptr;
};

// Destructor
Integer::~Integer(){
    std::cout<<"~Integer()" << std::endl;
    delete m_pInt;
};



// METHODS

int Integer::GetValue() const{
    return *m_pInt; // return value at address 
};

void Integer::SetValue(int value){
    // This check is for if the value has moved out of this object
    // in which case the pointer will be null, so needs to be re-initialized 
    if (m_pInt==nullptr){
        m_pInt = new int{};
    }

    *m_pInt = value;
}

// Section 5 
//  Operator Overloading 
Integer Integer::operator+(const Integer & other) const {
    Integer temp;
    *temp.m_pInt = *m_pInt + *other.m_pInt;
    return temp;
}

// Pre:increment
// Returns an L value by reference, returns value at address this
Integer & Integer::operator ++ () {
     ++(*m_pInt ) ;
    return *this;
}

// Post increment operator
Integer Integer::operator ++ (int) {
    Integer temp;
    temp.SetValue(this->GetValue());
    ++(*m_pInt );
    return temp;
}

// Comparison operator
bool Integer::operator == (const Integer & other) const {
    return *m_pInt == *other.m_pInt;
}


Integer & Integer::operator = (const Integer & other) {
    if (this !=&other){     // if object is being assigned to itself
        delete m_pInt;      // Free memory of current object 
        m_pInt = new int(*other.m_pInt);
    }
    return *this;
}


// Move operation
Integer & Integer::operator = (Integer && other) {
    if (this !=&other){     // if object is being assigned to itself
        delete m_pInt;      // Free memory of current object 
        m_pInt = other.m_pInt;
        other.m_pInt = nullptr;
    }
    return *this;
}

// Function call operator 
        // void operator() ();
void Integer::operator () () {
    std::cout << *m_pInt<<std::endl;
}


// Type Conversion: Convert from Integer to Int
Integer::operator int (){
    return *m_pInt;
};




