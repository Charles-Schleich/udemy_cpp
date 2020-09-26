#include "section4/Car.hpp"
#include <iostream>


// Static variable
int Car::totalCount=0;

// Default Constructor
Car::Car():Car(0.0f){
    std::cout << "Car()" << std::endl;
};

// parameterized constructor Delegated calls 
Car::Car(float fuel):Car(fuel,0){
    std::cout << "Car(float)" << std::endl;
};

// Parameterized constructor 
Car::Car(float fuel, int passenger){
    std::cout << "Creating Car(float,int)" << std::endl;
    this->fuel= fuel;
    this->speed = 0;
    this->passenger = passenger;
    ++totalCount;
};

// Destructor
Car::~Car(){
    --totalCount;
    std::cout << "Destructing Car" << std::endl;
}; 


// Methods on the class 
void Car::FillFuel(float amount){
    fuel = amount;
};

void Car::Accelerate(){
    speed ++;
    fuel -= 0.5f;

};

void Car::Break(){
    speed =0;
};


void Car::AddPassenger(int count){
    passenger +=count;
};
        float fuel;
        float speed;
        int passenger;

void Car::Dashboard()const {

    std::cout << "  Fuel     : " << this->fuel      <<std::endl;
    std::cout << "  Speed    : " << this->speed     <<std::endl;
    std::cout << "  Passenger: " << this->passenger <<std::endl;
    std::cout << "  TotalCars  : " << totalCount <<std::endl;
};


// Static member function 

void Car::showCount() {
    std::cout << "TotalCars  : " << totalCount <<std::endl;
}