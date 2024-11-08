#include "timeTests.hpp"

void makePlentyOfSharedPtr()
{
    SharedPtr<int> a = (new int(52));
    for(int i=0; i<20'000'000; i++)
    {
        SharedPtr<int> b(a);
    }
}
void makePlentyOfStdShared()
{
    std::shared_ptr<int> a(new int(52));
    for(int i=0; i<20'000'000; i++)
    {
        std::shared_ptr<int> b(a);
    }
}

void makePlentyOfUniquePtr()
{
    for(int i=0; i<20'000'000; i++)
    {
        UniquePtr<int> b(new int(52));
    }
}
void makePlentyOfStdUnique()
{
    for(int i=0; i<20'000'000; i++)
    {
        std::unique_ptr<int> b(new int(52));
    }
}
void makeTimeTest()
{
    { 
        LogDuration a(makePlentyOfUniquePtr, "UniquePtr");
        a.measure();
    }
    {
        LogDuration b(makePlentyOfStdUnique, "std::unique_ptr");
        b.measure(); 
    }
    {
        LogDuration c(makePlentyOfSharedPtr, "SharedPtr");
        c.measure();
    }
    {
        LogDuration d(makePlentyOfStdShared, "std::shared_ptr");
        d.measure();
    }
}