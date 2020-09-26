#include <iostream>
#include "section4/Car.hpp"
#include "section4/Integer.hpp"
#include "section4/S4Main.hpp"

// Default access to members is public 
struct Point{
    int x;
    int y;
};

void car_ex(){
    Car::showCount();

    // user defined Consturctor
    Car car2(200, 3);
    car2.Accelerate();
    car2.Dashboard();
    std::cout<< std::endl;

    // const
    const Car car; // Const qulifier, meaning can only call methods/functions that are consts, i.e. Do not mutate
    car.Dashboard();
    std::cout<< std::endl;

    // Struct 
    Point pt = Point{x:19, y:10};
    std::cout << "Point{ x" << pt.x << " y: "<< pt.y << "}"<< std::endl;
}


void copy_constructor_ex(){
    int *p1 = new int(5);
    // Shallow copy
    int *p2 = p1;
    // Deep copy 
    int *p3 = new int(*p1);
    

    Integer i(5);
    Integer i2(i); // Causes a Deep copy of the object i
    i.SetValue(9);

    std::cout << i.GetValue() << std::endl;
    std::cout << i2.GetValue() << std::endl;
};


//// L value and R value references
int Add(int x, int y){
    return x + y;
}
// Accepts an L-value reference
void Print(int &x){ 
    std::cout<< "Print(int&)" << std::endl;
}
// Accepts a const L-value reference
void Print(const int &x){ 
    std::cout<< "Print(const int&)" << std::endl;
}
// Accepts an R-value reference
void Print(int &&x){ 
    std::cout<< "Print(int &&x)" << std::endl;
}

void l_r_values(){
    // int &&r1 = 10 ;       // R-Value Reference
    // int &&r2 = Add(5,8) ; // Add Returns by value
    // int &&r3 = 2+7 ;      // Expression return a temporary
    // int x = 10; 
    // int &&r4 = x ;  // Cannot bind an R value reference to an L-value
    int x =10;
    Print(x);
    Print(3); // Temporary binds to function that accepts R-value Reference 
};



// Move Semantics examples
Integer Add(const Integer &a, const Integer &b){
    Integer temp;
    temp.SetValue(a.GetValue() + b.GetValue());
    return temp;
}

void move_semantics_example(){
    Integer a(1), b(3);
    a.SetValue(Add(a,b).GetValue());

    // Move Semantics 
    Integer c(1);
    auto d{std::move(c)}; // c is in an unspecified state 
    c.SetValue(5);
    // state moved out of c into d, therefore c.GetValue() will cause segfault
    // however we have reinitialized inside SetValue()
    std::cout << c.GetValue()<< std::endl;    


}



// Main 
void section4(){
    std::cout << "Section4\n================" << std::endl;    
    // car_ex();
    // copy_constructor_ex();
    // l_r_values();
    move_semantics_example();

    std::cout << "================" << std::endl;
};
