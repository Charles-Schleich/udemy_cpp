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