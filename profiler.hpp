#ifndef PROFILER_H
#define PROFILER_H
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
class LogDuration
{
public: 
    explicit LogDuration( const std::function<void()>& functionInput, const std::string& input_message): 
         message(input_message+": ")
        , start(std::chrono::steady_clock::now())
        , functionToMeasure(functionInput)
    {
       
    }
    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now(); 
        auto duration = finish - start; 
        std::cout<< message <<std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " ms" << std::endl;
    }
    void measure()
    {
        functionToMeasure();
    }
private: 
    std::string message{""}; 
    std::chrono::steady_clock::time_point start; 
    const std::function<void()>& functionToMeasure;
};
//#added const std::function<void()>& functionInput 
//LogDuration get function which need to be speedtested
// (Any)->(Any)
    
#endif /*PROFILER_H*/