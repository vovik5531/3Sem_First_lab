#include <iostream>
#include <string>
#include <cassert>
#include <typeinfo>
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "test.hpp"
#include "profiler.hpp"
#include "timeTests.hpp"


class Base
{
public:
    Base(){
        std::cout << "Base Constructor Called\n";
    }
    virtual ~Base(){
        std::cout << "Base Destructor called\n";
    }
    virtual void Hi()
    {
        std::cout<<"Base is here" << std::endl; 
    }
}; 
class Derived : public Base
{
public:
    Derived(){
        std::cout << "Derived constructor called\n";
    }
    ~Derived(){
        std::cout << "Derived destructor called\n";
    }
    void Hi()
    {
        std::cout<<"Derived is here" << std::endl;
    }
};

int main()
{
    testAll();
    std::cout<< "Yeah" << std::endl; 
    // std::cout<<sizeof(Base) << std::endl;
    SharedPtr<Base> dp(new Derived());
    SharedPtr<Derived> bp(dp); 
    return 0;
}