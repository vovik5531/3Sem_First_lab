#ifndef SharedPtr_H
#define SharedPtr_H
#include <cstddef>

struct Counter
{
    std::size_t weak=0; 
    std::size_t smart=0; 
};
//std::is_base_of
template<typename T>
class SharedPtr;


template<typename T>
class WeakPtr
{
private: 
    Counter* counter;
    T* shared_data; 
    void unconnect();
public: 
    WeakPtr(const SharedPtr<T>& SharedPtr);
    
    WeakPtr(const WeakPtr& other);
    
    Counter* getCounter(); 

    ~WeakPtr();
    
    bool expired() const;

    WeakPtr& operator=( const WeakPtr& other) noexcept;

    std::size_t getWeakCount() const;

    std::size_t getSmartCount() const; 

    // operator bool() const; 

    // bool operator==(const WeakPtr& other) const; 

    // bool operator!=(const WeakPtr& other) const; 
};

template<typename T>
class SharedPtr
{
private: 
    T* data; 
    Counter* counter;
    void unconnect();
public: 
    SharedPtr(T* ptr=nullptr);

    SharedPtr(const SharedPtr& other);
    
    ~SharedPtr();
    
    Counter* getCounter() const; 

    SharedPtr& operator=(const SharedPtr& another);

    SharedPtr(SharedPtr&& another); 
    
    T& operator*() const;
    
    T* operator->() const;
    
    std::size_t getWeakCount() const;

    std::size_t getSmartCount() const; 

    bool expired() const;

    T* get() const;

    operator bool() const; 

    bool operator==(const SharedPtr& other); 

    bool operator!=(const SharedPtr& other); 

};

template<typename U>
void swap(U& left_side, U& right_side);

template<typename T>
std::remove_reference_t<T>&& move(T&& a) noexcept;

#include"SharedPtr.tpp"
#endif /*SHARED_PRT_H*/ 
