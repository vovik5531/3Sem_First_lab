#include<iostream>
#include<string>
#include<cassert>
#include"UniquePtr.hpp"
#include"SharedPtr.hpp"
//#include"test.hpp"
struct Foo
{
    Foo(){ std::cout<< "Foo created" << std::endl;}
    ~Foo(){std::cout<< "Foo destroyed" << std::endl;}
};
void legacy_api(Foo* owning_foo)
{
    std::cout << __func__ << '\n';
    // [legacy code that no one understands or dares touch anymore]
    // [...]
    delete owning_foo;
    std::cout << "it's done" << std::endl; 
}
 
int main()
{
    UniquePtr<Foo> res{new Foo};
    double name = 14444.004;
    UniquePtr<double> ss{new double(1234.65)};
    std::cout<< *ss << std::endl;
    int* rawPtr = new int(31); 
    UniquePtr<int> up(rawPtr); 
    std::cout<< *up << std::endl;
    UniquePtr<int> ptr1(new int(10));
    UniquePtr<int> ptr2(new int(20));

    std::cout << "Before swap:\n";
    std::cout << "ptr1 points to: " << *ptr1 << "\n";
    std::cout << "ptr2 points to: " << *ptr2 << "\n";

    // Swap ptr1 and ptr2
    swap(ptr1, ptr2);

    std::cout << "After swap:\n";
    std::cout << "ptr1 points to: " << *ptr1 << "\n";
    std::cout << "ptr2 points to: " << *ptr2 << "\n";


    SharedPtr<int> shpt1 = (nullptr); 
    SharedPtr<int> shpt2 = (nullptr);
    shpt1 = std::move(shpt2); 
    assert(shpt1.getSmartCount() == shpt2.getSmartCount());
    
    SharedPtr<int> ptr(new int(140));
    ptr = ptr; // Self-assignment
    assert(ptr.getSmartCount() == 1);
    assert(*ptr == 140);
	return 0;
}