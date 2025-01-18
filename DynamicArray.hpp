#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdexcept>
template<class T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;
public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        size = dynamicArray.size;
        capacity = dynamicArray.capacity;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = dynamicArray.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& Get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    size_t GetSize() const{
        return size;
    }

    void Set(size_t index, const T & value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        data[index] = value;
    }


    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }


    void Append(const T & value) {
        if (size == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = value;
        size++;
    }

};
#endif /* DYNAMIC_ARRAY_H */