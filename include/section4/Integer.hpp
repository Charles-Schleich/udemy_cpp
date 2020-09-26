#pragma once

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
};

