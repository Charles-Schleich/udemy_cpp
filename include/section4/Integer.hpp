#pragma once
#include <iostream>

class Integer{
        int *m_pInt;
    public:
        // Default constructor
        Integer();
        // Parameterized Constructor
        Integer(int value);
        // Copy Constructor 
        Integer(const Integer &obj);
        // Move constructor
        Integer(Integer &&obj);
        int GetValue()const;
        void SetValue(int value);
        ~Integer(); // NEED THIS to free memory allocated for integer pointer
                    // However ! this is dangerous with shallow copies because this can double free

        //  Operator overloading 
        Integer   operator +  (const Integer & a) const;
        Integer & operator ++ ();
        Integer   operator ++ (int);
        bool      operator == (const Integer & other) const;
        Integer & operator =  (const Integer & other); 
        // Move constructor 
        Integer & operator =  (Integer && other); 
        // Function Call operator
        void operator() ();
        
        // friend function - has access to all private+public methods and data of a class LAST RESORT 
        friend std::istream & operator >> (std::istream  &in, Integer &myint);

        // Type Conversion Type to int
        explicit operator int ();


};

