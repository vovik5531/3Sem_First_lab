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
void empty()
{}
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
std::vector<double> generateArrayUniqPtr()
{
    std::vector<double> uniqPtrArr;
    {
        double j = 0; 
        LogDuration arr(empty, "UniquePtr");
        {
            for(int i=0; i<20'000'000; i++)
            {
                j++;
                UniquePtr<int> b(new int(52));
                if(j==100'000){
                    double dist = arr.measureDist();
                    uniqPtrArr.push_back(dist); 
                    j=0; 
                }
            }   
           
        } 
    }
    // for(int i= 0; i< uniqPtrArr.size(); i++)
    // {
    //     std::cout<<  uniqPtrArr[i] << "\n";
    // }
    return uniqPtrArr; 
}
std::vector<double> generateArrayStdUnique_ptr()
{
    std::vector<double> stdUniqPtrArr;
    {
        LogDuration arr(empty, "std::unique_ptr");
        {
            double j = 0;
            for(int i=0; i<20'000'000; i++)
            {
                j++; 
                std::unique_ptr<int> b(new int(52));
                if(j==100'000){
                    double dist = arr.measureDist();
                    stdUniqPtrArr.push_back(dist);
                    j = 0; 
                }
            }   
        }  
    }
    // for(int i= 0; i< stdUniqPtrArr.size(); i++)
    // {
    //     std::cout<<  stdUniqPtrArr[i] << "\n";
    // }
    return stdUniqPtrArr; 
}
std::vector<double> generateArraySharedPtr()
{
    std::vector<double> sharedPtrArr;
    {
        LogDuration arr(empty, "SharedPtr");
        {
            SharedPtr<int> a = (new int(52));
            double j = 0;
            for(int i=0; i<20'000'000; i++)
            {
                j++; 
                SharedPtr<int> b(a);
                if(j==100'000){
                    double dist = arr.measureDist();
                    sharedPtrArr.push_back(dist);
                    j = 0; 
                }
            }   
        }  
    }
    // for(int i= 0; i< sharedPtrArr.size(); i++)
    // {
    //     std::cout<<  sharedPtrArr[i] << "\n";
    // }
    return sharedPtrArr; 
}
std::vector<double> generateArrayStdSharedPtr()
{
    std::vector<double> stdSharedPtrArr;
    {
        LogDuration arr(empty, "std::shared_ptr");
        {
            std::shared_ptr<int> a(new int(52));
            double j = 0;
            for(int i=0; i<20'000'000; i++)
            {
                j++; 
                std::shared_ptr<int> b(a);
                if(j==100'000){
                    double dist = arr.measureDist();
                    stdSharedPtrArr.push_back(dist);
                    j = 0; 
                }
            }   
        }  
    }
    // for(int i= 0; i< stdSharedPtrArr.size(); i++)
    // {
    //     std::cout<<  stdSharedPtrArr[i] << "\n";
    // }
    return stdSharedPtrArr; 
}