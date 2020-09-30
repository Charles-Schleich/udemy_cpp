#include <iostream>
#include "section4/Integer.hpp"
#include "section5/S5Main.hpp"
#include <memory> 


// Operator overloading
// <return type> operator <#> (Arguments)

// Global function  first operand is int, second is Integer
Integer operator+(int x, const Integer &y) {
    Integer temp;
    temp.SetValue(x+y.GetValue());
    return temp;
}

// Overloading ostream object for cin to print an integer directly 
// return ostream reference, overloading <<, takes ostream and Integer
std::ostream & operator << (std::ostream &out, const Integer &myint){
    out << myint.GetValue();
    return out;
};


std::istream & operator >> (std::istream  &in, Integer &myint){
    int temp;
    in >> temp;
    // myint.SetValue(temp);
    *myint.m_pInt= temp;
    return in;
};

///////////////////////////////////////////////////////////////////////

void operator_overloading(){

    // PART 1
    // Implemented addition, incr, post incr and equality
    std::cout << "hello dope World" << std::endl;
    Integer myint(5);
    Integer myint2(7);
    Integer sum = myint2 +myint;
    std::cout << sum.GetValue() << std::endl;
    std::cout << sum++.GetValue() << std::endl;
    std::cout << sum.GetValue() << std::endl;
    std::cout << "==========" << std::endl;
    std::cout << (myint==myint) << std::endl;


    // PART 2
    // Implemented assignment and move operators 
    myint = myint;
    std::cout << myint.GetValue() << std::endl;
    Integer myint3(45);
    myint = std::move(myint3); // move 45 value out of myint3;
    std::cout << myint.GetValue() << std::endl;
    // std::cout << myint3.GetValue() << std::endl; // this causes a seg fault because memory of myint3 is invalid after move


    // PART 3 + 4
    // Global Overload of addition operator 
    Integer sum2 = myint + 3; // type conversion, i dont like it 
    std::cout << sum2.GetValue() << std::endl;
    Integer sum3 = 32 + myint;
    std::cout << sum3 << std::endl;

    // Input 
    Integer input; // type conversion, i dont like it
    std::cout << "Enter input : ";
    std::cin >> input;
    std::cout << "input it: "<< input << std::endl;
    // std::cout << myint.GetValue() << std::endl;

    // Function call operator overload (function objects) 
    // Overloaded to print the value of the class
    input();

}

///////////////////////////////////////////////////////////////////////
// Smart Pointer From scratch for Integer Class
class IntPtr{
        Integer *m_p;
    public:
    // Constuctor 
        IntPtr(Integer*p): m_p(p){

        }
    // Destructor
        ~IntPtr(){
            delete m_p;
        }
    // Overloads
        Integer * operator -> (){
            return m_p;
        };

        Integer & operator * (){
            return *m_p;
        };
};

void Process_unique(std::unique_ptr<Integer> ptr){
    std::cout << ptr->GetValue() << std::endl;
}


void Process_shared(std::shared_ptr<Integer> ptr){
    std::cout << ptr->GetValue() << std::endl;
}


void CreateInteger(){
    std::cout << "Smart Pointers" << std::endl;
    // Our smart pointer Implementation
    // IntPtr p = new Integer;

    // Box<T> in Rust
    std::unique_ptr<Integer> p (new Integer);
    // Only one refenece to unique pointer
    // Can move it though, does not support copy semantics
    auto p2 = std::move(p);
    p2->SetValue(3);
    std::cout << p2->GetValue() << std::endl;
    Process_unique(std::move(p2));
    std::cout << "p2 moved into Process" << std::endl;
    // p2 will have transfered its ownership of the resource

    std::cout << "=====================" << std::endl;

    // Shared pointer Rc<T> in rust
    std::shared_ptr<Integer> sh_ptr (new Integer);
    sh_ptr->SetValue(20);
    Process_shared(sh_ptr);
}


// Operator Overloading Rules 
// 1 : Associativity, Presedence & arity does not change.
// 2 : Overloaded operator functions should be non-static
//      Except for New and Delete
// 3: One Argument should be a user defined type
// 4: If binary operator (+-/*) accepts first Argument as primitive 
//      type, it has to be overloaded as Global function 
// 5: not all operators can be overloaded, 
// 6: Cannot define new operators 
// 7: overload with conventional behaviour to avoid confusion



// Main
void section5(){
    // operator_overloading();
    CreateInteger();
}
