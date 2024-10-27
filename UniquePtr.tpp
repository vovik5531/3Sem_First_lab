#include"UniquePtr.hpp"

// template<typename T>
// class UniquePtr
// {
// private: 
//     T* unique_ptr_data{}; 
// public: 
template <typename T>
UniquePtr<T>::UniquePtr(T* new_data): unique_ptr_data(new_data)
{
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : UniquePtr{other.unique_ptr_data}
{
    other.unique_ptr_data=nullptr;
}

template <typename T>   
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept
{
    if(&other == this)
    {
        return *this;
    }
    unique_ptr_data = other.unique_ptr_data;
    other.unique_ptr_data = nullptr;
    return *this;
} 

template <typename T>
UniquePtr<T>::operator bool() const noexcept
{
    if(unique_ptr_data==nullptr) return false; 
    else return true;
}

template <typename T>
T* UniquePtr<T>::operator->() const
{
    return unique_ptr_data;
}

template<typename T>
T& UniquePtr<T>::operator*() const 
{
    return *unique_ptr_data;
}

template<typename T>
T* UniquePtr<T>::release()
{   
    T* answer = unique_ptr_data; 
    unique_ptr_data = nullptr; 
    return answer;
}

template<typename T>
void UniquePtr<T>::reset(T* new_object)
{
    delete unique_ptr_data;
    unique_ptr_data = new_object;
}

template<typename T>
T* UniquePtr<T>::get() const 
{
    return unique_ptr_data;
}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
    delete unique_ptr_data;
}

template<typename U>
void swap(U& left_side, U& right_side)
{
    U temp = move(right_side);
    right_side = move(left_side);
    left_side = move(temp);
}

template<typename T>
std::remove_reference_t<T>&& move(T&& a) noexcept
{
    return static_cast<std::remove_reference_t<T>&&>(a);
}
