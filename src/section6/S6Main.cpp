#include <iostream>
#include "section4/Integer.hpp"
#include "section6/S6Main.hpp"
#include <memory> 


// UNIQUE POINTERS
//   _    _         _                         _____   _         
//  | |  | |       (_)                       |  __ \ | |        
//  | |  | | _ __   _   __ _  _   _   ___    | |__) || |_  _ __ 
//  | |  | || '_ \ | | / _` || | | | / _ \   |  ___/ | __|| '__|
//  | |__| || | | || || (_| || |_| ||  __/   | |     | |_ | |   
//   \____/ |_| |_||_| \__, | \__,_| \___|   |_|      \__||_|   
//                        | |                                   
//                        |_|                             

// std::unique_ptr : used when you are not sharing your pointer with different parts of the code

void display(Integer *p){
     if (!p){
        return;
    }
    std::cout<< p->GetValue() << std::endl;
}

Integer * get_pointer(int value){
    Integer *p = new Integer{value};
    return p;
}

void store(std::unique_ptr<Integer> &p){
    std::cout << "Storing data to a file: " << p->GetValue() << std::endl;
}


void operate(int value){
    std::unique_ptr<Integer> p {get_pointer(value)};

    if (p==nullptr){
        // p = new Integer{value};
        p.reset(new Integer{value});
        // if smart pointer holds existing pointer, deletes pointer
        // Then it takes ownership of the new pointer in the ()
    }
    p->SetValue(value);

    display(p.get()); // .get gets the raw pointer
    p = nullptr;
    p.reset(new Integer{});
    *p = __LINE__;
    display(p.get()); 
    // Cannot create copy of unique_ptr object, Copy Costructor is delete

    // store(std::move(p)); // transfers ownership if void store(std::unique_ptr<Integer> &p)   
    store(p); // Can pass by reference will move in and back 
    *p = 1321;

}

//    _____  _                            _      _____   _         
//   / ____|| |                          | |    |  __ \ | |        
//  | (___  | |__    __ _  _ __  ___   __| |    | |__) || |_  _ __ 
//   \___ \ | '_ \  / _` || '__|/ _ \ / _` |    |  ___/ | __|| '__|
//   ____) || | | || (_| || |  |  __/| (_| |    | |     | |_ | |   
//  |_____/ |_| |_| \__,_||_|   \___| \__,_|    |_|      \__||_|   

// Reference counted pointer,
// Shared pointer is shared with other parts of the code.

class Project {
public:
    ~Project(){
        std::cout << "~Project()" << std::endl;
    }
};

class Employee{
// private:
    std::shared_ptr<Project> m_pProject;
public:
    void set_project(std::shared_ptr<Project> p){
        m_pProject=p;
    }
    std::shared_ptr<Project> get_project() const {
        return m_pProject;
    }
    ~Employee(){
        std::cout << "~Employee()" << std::endl;
    }

};


std::shared_ptr<Employee> AssignProject(){
    std::shared_ptr<Project> p {new Project{}};
    // Employee *e1 = new Employee{};
    std::shared_ptr<Employee> e1 {new Employee{}};
    e1->set_project(p);
    return e1;
    // return std::shared_ptr<Employee>{e1};
}

void shared_pointer_main(){
    std::shared_ptr<Employee> shared_ptr = AssignProject();
    if (shared_ptr == nullptr){
        std::cout<< "Employee pointer null";
    };
    shared_ptr.get();
    shared_ptr.reset(new Employee{}); 
    // Reset: first decr ref count by 1, if ref count becomes 0, deletes pointer
    //        then takes ownership of the new pointer

}

//  __          __           _         _____   _         
//  \ \        / /          | |       |  __ \ | |        
//   \ \  /\  / /___   __ _ | | __    | |__) || |_  _ __ 
//    \ \/  \/ // _ \ / _` || |/ /    |  ___/ | __|| '__|
//     \  /\  /|  __/| (_| ||   <     | |     | |_ | |   
//      \/  \/  \___| \__,_||_|\_\    |_|      \__||_|   
// used in conjunction with a shared pointer
// weak pointer points to control block of shared pointer,
//      If RC of shared pointer is 0, cant get anything out
//      If RC of shared pointer is non-zero, can get the underlying value


class Printer{
    private:
        std::weak_ptr<int> m_pValue{};
    public:
        void setvalue(std::weak_ptr<int> newval){
            m_pValue =  newval;
        }
        void print(){
            std::cout << "Ref Count: " << m_pValue.use_count() <<std::endl;
            if (m_pValue.expired()){
                std::cout << "Resource is no longer available" << std::endl;
                return;     
            }
            auto sp = m_pValue.lock();
            std::cout << "Value is " << *sp <<std::endl;
            std::cout << "Ref Count " << sp.use_count() <<std::endl;
        }
};


void weak_pointer_main(){

    Printer prn;
    int num {};
    std::cin >> num;
    std::shared_ptr<int> p {new int{num}};
    prn.setvalue(p);
    if (*p>10){
        p = nullptr;
    }
    prn.print();

}

/////////////////////////////////////////////////////////////////////////////
//   ______                                _            _____   _          //
//  |  ____|                              | |          |  __ \ | |         //
//  | |__   __  __ __ _  _ __ ___   _ __  | |  ___     | |__) || |_  _ __  //
//  |  __|  \ \/ // _` || '_ ` _ \ | '_ \ | | / _ \    |  ___/ | __|| '__| //
//  | |____  >  <| (_| || | | | | || |_) || ||  __/    | |     | |_ | |    //
//  |______|/_/\_\\__,_||_| |_| |_|| .__/ |_| \___|    |_|      \__||_|    // 
//                                 | |                                     // 
//                                 |_|                                     //
/////////////////////////////////////////////////////////////////////////////
// Circular Reference example 
//      Need to use shared_pointers for the pointers to the objects
//      Weak pointers for their internal pointers to the other objects
//      This avoids memory being leaked through not calling destructors 
//      if shared pointers are used everywhere 


class Employee_Ex; // the cpp compiler is stupid

class Project_Ex {
    public:
        std::weak_ptr<Employee_Ex> m_pEmployee;
        Project_Ex(){
            std::cout << "Project_Ex()" << std::endl;
        }
        ~Project_Ex(){
            std::cout << "~Project_Ex()" << std::endl;
        }
};

class Employee_Ex{
    public:
        std::weak_ptr<Project_Ex> m_pProject;
        Employee_Ex(){
            std::cout << "Employee_Ex()" << std::endl;
        }
        ~Employee_Ex(){
            std::cout << "~Employee_Ex()" << std::endl;
        }
};

void example_main(){
    std::shared_ptr<Employee_Ex> emp{new Employee_Ex{}};
    std::shared_ptr<Project_Ex>  prj{new Project_Ex{}};

    emp -> m_pProject = prj;
    prj -> m_pEmployee = emp;
}


// Main
void section6(){
    std::cout<<"=========\nsection6\n=========" << std::endl;
    // operate(10);
    // shared_pointer_main();
    // weak_pointer_main();
    example_main();
}
