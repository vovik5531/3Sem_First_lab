#include<cassert>
#include<iostream>
#include"test.hpp"
#include"SharedPtr.hpp"
#include"UniquePtr.hpp"
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
    shpt1 = std::move(shpt2); 
    assert(shpt1.getSmartCount() == shpt2.getSmartCount());
}

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
    SharedPtr<int> ptr2(std::move(ptr1));
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
    std::cout << "All testes passed successfully" << std::endl; 
}

