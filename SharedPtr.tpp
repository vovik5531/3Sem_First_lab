#include"SharedPtr.hpp"
 
template<typename T>
void WeakPtr<T>::unconnect()
{
    if(!counter)
    {
        counter->weak--; 
        if(counter->smart==0)
        {
            if(counter->weak==0)
            {
                delete counter; 
            }
        }
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr): counter(sharedPtr.getCounter())
{
    if(counter)
    {
        counter->weak++; 
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other) : counter(other.counter)
{
    if(counter)
    {
        counter->weak++;
    }
}

template<typename T>
Counter* WeakPtr<T>::getCounter()
{
    return counter; 
}

template<typename T>
WeakPtr<T>::~WeakPtr()
{
    unconnect();
}
template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=( const WeakPtr& other) noexcept
{   
    if(&other != this )
    {
        if(counter)
        {
            counter->weak--;
        }
        counter = other.counter;
        if(counter)
        {
            counter->weak++;
        }
    }
    return *this;
}    
template<typename T>
bool WeakPtr<T>::expired() const 
{
    if (counter == nullptr) {
        return true;
    } else if (counter->smart == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t WeakPtr<T>::getWeakCount() const 
{
    return (counter != nullptr) ? counter->weak : 0;
}

template<typename T>
std::size_t WeakPtr<T>::getSmartCount() const 
{
    return (counter != nullptr) ? counter->smart : 0;
}

template<typename T>
WeakPtr<T>::operator bool() const {
    return this != nullptr;
}

template<typename T>    
bool WeakPtr<T>::operator == (const WeakPtr<T>& other) const{
    return shared_data == other.shared_data;
}

template<typename T>
bool WeakPtr<T>::operator != (const WeakPtr<T>& other) const{
    return shared_data != other.shared_data;
}

template<typename T>
void SharedPtr<T>::unconnect()
{
    if(counter==nullptr)
    {
        return; 
    }
    counter->smart--; 
    if(counter->smart==0)
    {
        delete data; 
        if(counter->weak==0)
        {
            delete counter;
        }
    } 
}
template<typename T>
SharedPtr<T>::SharedPtr(T* ptr): data{ptr}, counter( (ptr==nullptr)? (nullptr) : new Counter{0, 1} ) 
{   
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other): data(other.data), counter(other.counter)
{
    if (counter == nullptr)
    {
        return;
    }
    counter->smart++;  
} 
template<typename T>
SharedPtr<T>::~SharedPtr()
{
    unconnect(); 
}
template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& another)
{
    if(this==&another)
    {
        return *this; 
    }
    unconnect(); 
    data=another.data;
    counter=another.counter; 
    if(counter != nullptr)
    {
        counter->smart++; 
    }
    return *this; 
} 
template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& another) : data(another.data), counter(another.counter)
{
    another.data = nullptr;
    another.counter = nullptr; 
}  

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& another)
{
    if(this==&another)//self-assignment check
    {
        return *this; 
    }   
    unconnect(); 
    data = another.data; 
    counter = another.counter; 

    another.data = nullptr; 
    another.counter = nullptr; 
    return *this; 
}

template<typename T>
T& SharedPtr<T>::operator*() const 
{
    return *data; 
} 

template<typename T>
Counter* SharedPtr<T>::getCounter() const
{
    return counter; 
}
template<typename T>
std::size_t SharedPtr<T>::getWeakCount() const
{
    return (counter != nullptr) ? counter->weak : 0;
}

template<typename T>
std::size_t SharedPtr<T>::getSmartCount() const
{
    return (counter != nullptr) ? counter->smart : 0;
}

template<typename T>
T* SharedPtr<T>::operator->() const 
{
    return data; 
}

template<typename T>
bool SharedPtr<T>::expired() const 
{
    if (counter == nullptr) {
        return true;
    } else if (counter->smart == 0) {
        return true;
    }
    return false;
}
template<typename T>
T* SharedPtr<T>::get() const
{
    return data; 
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return data != nullptr;
}

template<typename T>
bool SharedPtr<T>::operator ==(const SharedPtr<T>& other) const {
    return data == other.data;
}

template<typename T>
bool SharedPtr<T>::operator !=(const SharedPtr<T>& other) const {
    return data != other.data;
}

// template<typename T, typename ...Args>
// SharedPtr<T> make_shared(Args&&...args)
// {
//     auto ptr = new ControlBlock<T>{1, new T{std::forward<Args>(args)...}};
// }
// template<typename U>
// void swap(U& left_side, U& right_side)
// {
//     U temp = move(right_side);
//     right_side = move(left_side);
//     left_side = move(temp);
// }

// template<typename T>
// std::remove_reference_t<T>&& Smove(T&& a) noexcept
// {
//     return static_cast<std::remove_reference_t<T>&&>(a);
// }
