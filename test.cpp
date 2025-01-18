#include<cassert>
#include<iostream>
#include"test.hpp"
#include"SharedPtr.hpp"
#include"UniquePtr.hpp"

namespace testCycleReference
{
    int entityCounter = 0; 
}

class DestructionChecker {
private:
    inline static int instances = 0;

public:
    static int getInstanceCount() { return instances; }
    
    DestructionChecker() { ++instances; }
    ~DestructionChecker() { --instances; }
};

// int DestructionChecker::instances = 0;

class Base
{
public:
    Base(){
        testCycleReference::entityCounter++; 
    }
    virtual ~Base(){
        testCycleReference::entityCounter--; 
    }
    virtual void hi()
    {
        std::cout<<"Base is here" << std::endl; 
    }
}; 

class Derived : public Base
{
public:
    Derived(){
        testCycleReference::entityCounter++; 
    }
    ~Derived(){
        testCycleReference::entityCounter--; 
    }
    void hi()
    {
        std::cout<<"Derived is here" << std::endl;
    }
    //think about return value in testss///
};

struct Boo; 
struct Foo {
    SharedPtr<Boo> booPtr;
    //DestructionChecker* p;
    Foo() //: p(checker) 
    {
        testCycleReference::entityCounter++; 
    }

    ~Foo() 
    {
        testCycleReference::entityCounter--;
    }
}; 

struct Boo {
    WeakPtr<Foo> fooPtr; // Use weak_ptr to avoid circular reference
    //DestructionChecker* p;
    Boo() //: p(checker) 
    { 
        testCycleReference::entityCounter++; 
    }
    ~Boo() 
    { 
        testCycleReference::entityCounter--;  
    }
};

// void testCyclicRef() {
//     assert(DestructionChecker::getInstanceCount() == 0);
//     {
//         DestructionChecker* destCheck = new DestructionChecker();
//         assert(DestructionChecker::getInstanceCount() == 1);

//         {
//             auto boo = makeShared<Boo>(new DestructionChecker());
//             std::cout<< DestructionChecker::getInstanceCount() << std::endl; 
//             assert(DestructionChecker::getInstanceCount() == 2);

//             auto foo = makeShared<Foo>(new DestructionChecker());
//             assert(DestructionChecker::getInstanceCount() == 3);
//             std::cout<< DestructionChecker::getInstanceCount() << std::endl; 

//             boo->foo_ptr = foo; 
//             foo->boo_ptr = boo; 
//         }
//         std::cout<< DestructionChecker::getInstanceCount() << std::endl; 
//         assert(DestructionChecker::getInstanceCount() == 1);
//     }
//     assert(DestructionChecker::getInstanceCount() == 0);
// }
void testPolymorphysm()
{
    assert(testCycleReference::entityCounter == 0);
    {
        SharedPtr<Base> dp(new Derived());
        assert(testCycleReference::entityCounter == 2);
        SharedPtr<Derived> bp(dp); 
        assert(testCycleReference::entityCounter == 2);
    }
    assert(testCycleReference::entityCounter == 0);
}
void testCycleRef()
{
    assert(testCycleReference::entityCounter == 0);
    {
        SharedPtr<Boo> boo{new Boo};
        assert(testCycleReference::entityCounter == 1);
        SharedPtr<Foo> foo{new Foo};
        assert(testCycleReference::entityCounter == 2);
        boo->foo_ptr = foo; 
        foo->boo_ptr = boo;
    }
    assert(testCycleReference::entityCounter == 0);
}
void testNullPointer() 
{
    SharedPtr<int> ptr;
    assert(!ptr);
    assert(ptr.getSmartCount() == 0);
    assert(ptr.getWeakCount() == 0);
}

void testNullPointerImplementation() 
{
    SharedPtr<int> shpt1 = (nullptr); 
    SharedPtr<int> shpt2 = (nullptr);
    shpt1 = move(shpt2); 
    assert(shpt1.getSmartCount() == shpt2.getSmartCount());
}
//add strong-complimentation test..
void testCopyConstruction()
{
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(ptr1);
    assert(ptr1.getSmartCount() == 2);
    assert(ptr2.getSmartCount() == 2);
    assert(*ptr1 == 42);
    assert(ptr1 == ptr2);
}

void testMoveConstruction()
{
    SharedPtr<int> ptr1(new int(100));
    SharedPtr<int> ptr2(move(ptr1));
    assert(!ptr1);
    assert(ptr2.getSmartCount() == 1);
    assert(*ptr2 == 100);
}

void testAssignmentCopy()
{
    SharedPtr<int> ptr1(new int(20));
    SharedPtr<int> ptr2;
    ptr2 = ptr1;
    assert(ptr1.getSmartCount() == 2);
    assert(ptr2.getSmartCount() == 2);
    assert(*ptr1 == 20);
    assert(ptr1 == ptr2);
}

void testAssignmentMove() 
{
    SharedPtr<int> ptr1(new int(30));
    SharedPtr<int> ptr2(new int(40));
    ptr2 = std::move(ptr1);
    assert(!ptr1);
    assert(ptr2.getSmartCount() == 1);
    assert(*ptr2 == 30);
}

void testWeakPointerBasics()
{
    SharedPtr<int> ptr(new int(5));
    WeakPtr<int> weak(ptr);
    assert(weak.getSmartCount() == 1);
    assert(weak.getWeakCount() == 1);
    assert(!weak.expired());
}

void testWeakPointerSelfAssignment()
{
    SharedPtr<int> ptr(new int(60));
    WeakPtr<int> weak(ptr);
    weak = weak; // Self-assignment
    assert(weak.getWeakCount() == 1);
    assert(!weak.expired());
}

void testMultipleWeakPointers()
{
    SharedPtr<int> ptr(new int(70));
    WeakPtr<int> weak1(ptr);
    WeakPtr<int> weak2(ptr);
    assert(ptr.getWeakCount() == 2);
    assert(!weak1.expired());
    assert(!weak2.expired());
}

void testMultipleReferences() 
{
    SharedPtr<int> ptr1(new int(80));
    SharedPtr<int> ptr2 = ptr1;
    SharedPtr<int> ptr3 = ptr2;
    assert(ptr1.getSmartCount() == 3);
    assert(ptr2.getSmartCount() == 3);
    assert(ptr3.getSmartCount() == 3);
}

void testAssignmentOfNull() 
{
    SharedPtr<int> ptr1(new int(90));
    SharedPtr<int> ptr2;
    ptr1 = ptr2; // Assigning null
    assert(!ptr1);
    assert(ptr2.getSmartCount() == 0);
}

void testResetFunctionality() 
{
    SharedPtr<int> ptr(new int(100));
    ptr = nullptr;
    assert(!ptr);
    assert(ptr.getSmartCount() == 0);
}

void testDereferenceOperator()
{
    SharedPtr<int> ptr(new int(110));
    assert(*ptr == 110);
    *ptr = 120;
    assert(*ptr == 120);
}

void testComparisonOperators() 
{
    SharedPtr<int> ptr1(new int(130));
    SharedPtr<int> ptr2(ptr1);
    SharedPtr<int> ptr3(new int(130));
    assert(ptr1 == ptr2);
    assert(ptr1 != ptr3);
}

void testSelfAssignmentCopy() 
{
    SharedPtr<int> ptr(new int(140));
    ptr = ptr; // Self-assignment
    assert(ptr.getSmartCount() == 1);
    assert(*ptr == 140);
}

void testSwapFunction()
{
    UniquePtr<int> ptr1(new int(10));
    UniquePtr<int> ptr2(new int(20));

    //Before swap
    assert(*ptr1==10);
    assert(*ptr2==20);
    
    // Swap ptr1 and ptr2
    swap(ptr1, ptr2);

    //After swap
    assert(*ptr1==20);
    assert(*ptr2==10);
}
void testMoveTwoShared()
{
    SharedPtr<int> ptr1 = new int(52);
    SharedPtr<int> ptr2 = ptr1; //check counter value..
    assert(ptr2.getSmartCount() == ptr1.getSmartCount());
    assert(ptr2.getSmartCount()==2);
    ptr2 = move(ptr1); 
    assert(ptr2.getSmartCount()!=ptr1.getSmartCount());
}


void testUniqueDestrucion() {
    assert( DestructionChecker::getInstanceCount() == 0 );
    {
        DestructionChecker *c1 = new DestructionChecker();
        DestructionChecker *c2 = new DestructionChecker();
        assert( DestructionChecker::getInstanceCount() == 2 );
        UniquePtr<DestructionChecker> p( c1 );
        p.reset( c2 );
        assert( DestructionChecker::getInstanceCount() == 1 );
    }
    assert( DestructionChecker::getInstanceCount() == 0 );
}
void testWeakExpired()
{
    WeakPtr<int> ptr1; 
    {
        SharedPtr<int> shpt = new int(42); 
        ptr1 = shpt; 
        assert(ptr1.expired()==0);
    }
    assert(ptr1.expired()==1);
}
void testDefaultConstructor()
{
    SharedPtr<int> a; 
    SharedPtr<int> b = a; 
    assert(b.getSmartCount()==0); 
}

void testWeakLock()
{
    WeakPtr<int> weak;
    auto p = weak.lock(); 
    assert(!p);
    {
        SharedPtr<int> shpt = new int(42); 
        weak = shpt;
        SharedPtr<int> p2 = weak.lock(); 
        assert(*p2 == 42);
        assert(weak.getSmartCount()==2);
        assert(p2);
    }
    assert(!p);
}
void testAll()
{
    testNullPointer();
    testCopyConstruction();
    testMoveConstruction();
    testAssignmentCopy();
    testAssignmentMove();
    testWeakPointerBasics();
    testWeakPointerSelfAssignment();
    testMultipleWeakPointers();
    testMultipleReferences();
    testAssignmentOfNull();
    testResetFunctionality();
    testDereferenceOperator();
    testComparisonOperators();
    testSelfAssignmentCopy();
    testSwapFunction();
    testMoveTwoShared(); 
    testDefaultConstructor(); 
    testWeakExpired(); 
    testWeakLock();
    testUniqueDestrucion();
    testPolymorphysm();
    // testCyclicRef();
    testCycleRef();
    std::cout << "All testes passed successfully" << std::endl; 
}

