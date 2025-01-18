#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstddef>
#include <stdexcept>

template <class T>
class LinkedList {
private:
    struct Node {
        T item;
        Node* next;
        Node* prev;

        Node(const T & item, Node* next = nullptr, Node* prev = nullptr):
            item(item), next(next), prev(prev)
        {
        };
    };
    Node* head;
    Node* tail;
    size_t size;
public:
    LinkedList(): head(nullptr), tail(nullptr), size(0) {};

    ~LinkedList() {
        Clear();
    }

    void Append(const T & item) {
        Node* node = new Node(item);
        if (size == 0) {
            tail = head = node;
        } else {
            tail -> next = node;
            node -> prev = tail;
            tail = node;
        }
        size++;
    }

    void Prepend(const T & item) {
        Node* node = new Node(item);
        if (size == 0) {
            tail = head = node;
        } else {
            head -> prev = node;
            node -> next = head;
            head = node;
        }
        size++;
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current -> next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    size_t GetSize() const{
        return size;
    }

    T& Get(const size_t & index) const{
        if (index >= size ) {
            throw std::out_of_range("Incorrect Index!");
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current -> next;
        }
        return current -> item;
    }

    void Set(size_t index, const T & value) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current -> next;
        }

        current -> item = value;
    }

     void InsertAt(size_t index, const T & item) {
        if (index > size || index < 0) {
            throw std::out_of_range("Incorrect Index!");
        }

        if (index ==  size) {
            Append(item);
        } else if (index == 0) {
            Prepend(item);
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp -> next;
            }

            Node* node = new Node(item);
            node -> next = temp -> next;
            temp -> next = node;
            node -> prev = temp;
            node -> next -> prev = node;
            size++;

        }
    }

    void RemoveAt(size_t index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Incorrect Index!");
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
        } else if (index == size - 1) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            delete temp;
        } else {
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }

        size--;
    }

};
#endif /* LINKEDLIST_H */