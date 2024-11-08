#ifndef SharedPtr_H
#define SharedPtr_H
#include <cstddef>
#include <stdexcept>
#include <memory> //std::allocate_shared and std::allocator
struct Counter
{
    std::size_t weak=0; 
    std::size_t smart=0; 
};
template<typename T>
class SharedPtr;

template<typename T>
class WeakPtr
{
private: 
    Counter* counter;
    T* sharedData; 
    void unconnect();
public: 

    //add optional to get data_ptr if data not expired..
    WeakPtr(); 
    //avoid getCounter function, or make it private or think about composition of weak and shared..
    // #I've made WeakPtr a friend for SharedPtr
    WeakPtr(const SharedPtr<T>& sharedPtr);
    
    WeakPtr(const WeakPtr& other);

    WeakPtr(WeakPtr&& other);
    
    // #deleted Counter* getCounter(); 

    ~WeakPtr();
    
    bool expired() const;

    SharedPtr<T> lock() const noexcept; 

    WeakPtr& operator=( const WeakPtr& other) noexcept;

    std::size_t getWeakCount() const;

    std::size_t getSmartCount() const; 

    operator bool() const; 

    bool operator==(const WeakPtr& other) const; 

    bool operator!=(const WeakPtr& other) const; 
};

template<typename T>
class SharedPtr
{
private: 
    T* data = nullptr; 
    Counter* counter = nullptr;
    void unconnect();
public: 

    SharedPtr() noexcept;

    SharedPtr(T* ptr);

    SharedPtr(const SharedPtr& other);
    
    explicit SharedPtr(const WeakPtr<T>& weak); 
    
    ~SharedPtr();
    
    SharedPtr& operator=(const SharedPtr& another);

    SharedPtr(SharedPtr&& another); 

    SharedPtr& operator=(SharedPtr&& another); 
    
    // const T& operator*() const;
    // //something gonna happen here with constantness of objects...
    // const T* operator->() const;
    //# if have const SharedPtr<T> will call these methods K
    // otherwise J 
    T& operator*() const; 

    T* operator->() const; 

    // #deleted Counter* getCounter() const; //TODO why I need it?

    std::size_t getWeakCount() const;

    std::size_t getSmartCount() const; 

    //bool expired() const;

    // const T* get() const;//const return type

    T* get() const;//non-const return type

    operator bool() const; 

    bool operator==(const SharedPtr& other) const; 

    bool operator!=(const SharedPtr& other) const; 
    //solve polymorphysm essense
    // template<typename U>
    // SharedPtr<U> dynamic_cast_ptr();
    template<typename U>
    SharedPtr(const SharedPtr<U>& other );

    template<typename U>
    friend class SharedPtr;

    //solution to avoid getCounter function
    template<typename U>
    friend class WeakPtr;
};

template<typename U>
void swap(U& left_side, U& right_side);

template<typename T>
std::remove_reference_t<T>&& move(T&& a) noexcept;

// template<typename T, typename ...Args>
// SharedPtr<T> makeShared(Args&& ...args); 

#include"SharedPtr.tpp"

#endif /*SHARED_PRT_H*/ 
