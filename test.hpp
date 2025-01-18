#ifndef TEST_H
#define TEST_H

void testNullPointer();
void testNullPointerImplementation(); 
void testCopyConstruction();
void testMoveConstruction();
void testAssignmentCopy();
void testAssignmentMove();
void testWeakPointerBasics();
void testWeakPointerSelfAssignment();
void testMultipleWeakPointers();
void testMultipleReferences();
void testAssignmentOfNull();
void testResetFunctionality();
void testDereferenceOperator();
void testComparisonOperators();
void testSelfAssignmentCopy();
void testSwapFunction(); 
void testMoveTwoShared(); 
void testWeakExpired(); 
void testWeakLock(); 
void testUniqueDestrucion();
void testCycleRef();
void testPolymorphysm();

void testAll();
//add test SharedPtr::exprired() False/True cases.. 
#endif /* TEST_H */