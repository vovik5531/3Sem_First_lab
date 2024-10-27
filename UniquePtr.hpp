#pragma once 

template<typename T>
class UniquePtr
{
private: 
    T* unique_ptr_data{}; 
public: 
    UniquePtr(T* new_data = nullptr);

    UniquePtr(const UniquePtr& other) = delete; 

    UniquePtr& operator=(const UniquePtr& other) = delete; 

    UniquePtr(UniquePtr&& other) noexcept;
    
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    operator bool() const noexcept;

    T* operator->() const;

    T& operator*() const;
    
    T* release();

    void reset(T* new_object = nullptr);

    T* get() const;

    ~UniquePtr();
    
};

template<typename U>
void swap(U& left_side, U& right_side);

template<typename T>
std::remove_reference_t<T>&& move(T&& a) noexcept;

#include"UniquePtr.tpp"

