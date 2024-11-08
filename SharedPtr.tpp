template<typename T>
void WeakPtr<T>::unconnect()
{
    if(counter!= nullptr)
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
WeakPtr<T>::WeakPtr():counter(nullptr), sharedData(nullptr)
{
}
template<typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr): counter(sharedPtr.counter), sharedData(sharedPtr.data)
{
    if(counter!=nullptr)
    {
        counter->weak++; 
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other) : counter(other.counter), sharedData(other.sharedData)
{
    if(counter)
    {
        counter->weak++;
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& other): counter(other.counter), sharedData(other.sharedData)
{
    other.counter = nullptr; 
    other.sharedData = nullptr; 
}

template<typename T>
WeakPtr<T>::~WeakPtr()
{
    unconnect();
}

template<typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept
{
    if(expired())
    {
        return nullptr;
    }
    SharedPtr<T> newShared; 
    newShared.data = sharedData; 
    newShared.counter = counter;
    if(counter!=nullptr)
    {
        counter->smart++; 
    }
    return newShared;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=( const WeakPtr& other) noexcept
{   
    if(&other == this )
    {
        return *this; 
    }
    unconnect(); 
    sharedData = other.sharedData;
    counter = other.counter;
    if(counter!=nullptr)
    {
        counter->weak++;
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
    return sharedData == other.sharedData;
}

template<typename T>
bool WeakPtr<T>::operator != (const WeakPtr<T>& other) const{
    return sharedData != other.sharedData;
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
SharedPtr<T>::SharedPtr() noexcept
{
    data = nullptr; 
    counter = nullptr;
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
template<typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other) {
// U* casted_data = std::dynamic_cast<U*>(data); 
//     if(casted_data)
//     {
//         return SharedPtr<U>(casted_data));
//     }
//     return SharedPtr<U>(nullptr); 
    try{
        T * new_ptr = dynamic_cast<T*> (other.get());
        if(new_ptr ==nullptr)
        {
            data = nullptr; 
            counter = nullptr;    
        }
        else
        {
            data = new_ptr;
            counter = other.counter; 
            // counter->smart = other.getSmartCount();
            // counter->weak  = other.getWeakCount();
            counter->smart++;
        }
    }
    catch(const std::bad_cast& e){
        
    }
     
}

template<typename T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& weak)
{
    if(weak.expired())
    {
        throw std::runtime_error("Attempt to create Shared from expired Weak");
    }
    //use weak.lock() 
    SharedPtr<T> lockedShared = weak.lock(); 
    data = lockedShared.data;
    counter = lockedShared.counter; 
    if(counter!=nullptr)
    {
        counter->smart++;
    }  
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
//SharedPtr<const Foo> 
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






// template<typename T>
// template<typename U>
// SharedPtr<U> SharedPtr<T>::dynamic_cast_ptr() const
// {
//     U* casted_data = std::dynamic_cast<U*>(data); 
//     if(casted_data)
//     {
//         return SharedPtr<U>(casted_data));
//     }
//     return SharedPtr<U>(nullptr); 
//     //throw std::bad_cast;
// }

// template<typename T, typename ...Args>
// SharedPtr<T> makeShared(Args&&...args)
// {
//     auto ptr = std::allocate_shared<T>(std::allocator<T>(), std::forward<Args>(args)...);
//     SharedPtr<T> shpt(ptr.get());
//     //*ptr = nullptr;
//     return shpt;
// }

//move and swap declared in UniquePtr
