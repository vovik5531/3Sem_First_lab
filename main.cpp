#include<iostream>
#include<string>
#include<cassert>
#include"UniquePtr.hpp"
#include"SharedPtr.hpp"
#include"test.hpp"
struct Foo
{
    Foo(){ std::cout<< "Foo created" << std::endl;}
    ~Foo(){std::cout<< "Foo destroyed" << std::endl;}
}; 
int main()
{
    UniquePtr<Foo> res{new Foo};
    testAll();
	return 0;
    
}