#ifndef WEAK_PTR.H
#define WEAK_PTR.H

template<typedef T>
class Weak_ptr
{
private: 
    T* data; 


public: 
    Weak_ptr(T input_data): data{*input_data}
    Weak_ptr(const Weak_ptr& other):
    {
        data = other.data
    }
    
}



#endif /*WEAK_PTR.H*/