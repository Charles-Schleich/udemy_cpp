#pragma once 

class Car{
    private:
        // With init values (inserts code into constructors)
        float fuel  {0}; 
        float speed {0};
        int passenger{0};
        static int totalCount; // Static, cannot belong to a class 

        int arr[5] = {1,2,3};   
        char* ptr{};    // null pointer
    public:
        // Constructors
        Car();  // Constructor
        Car(float fuel, int passengers); // parameterized constructor 
        Car(float fuel); // parameterized constructor 
        ~Car(); // Destructor
        // Methods
        void FillFuel(float amount);
        void Accelerate();
        void AddPassenger(int count);
        void Break();
        void Dashboard() const;
        // Static function, applies to the Class not an instance
        static void showCount();
};
