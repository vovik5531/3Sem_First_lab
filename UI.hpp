#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <utility>
#include "SharedPtr.hpp"
#include "LinkedList.hpp"
#include "DynamicArray.hpp"
#include "test.hpp"
#include "timeTests.hpp"
#include "plotting.hpp"

void InitializeUI();
void RunTimingTests();
void RunTests(); 
// Draws the main UI, displaying pointers and mode information.
template <class T>
void DrawUI(
    const LinkedList<SharedPtr<T>>& smartPointerList, 
    const DynamicArray<SharedPtr<T>>& smartPointerArray,
    const LinkedList<WeakPtr<T>>& weakPointerList, 
    const DynamicArray<WeakPtr<T>>& weakPointerArray,
    bool isArrayMode, bool isWeakMode, size_t selected
) {
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "Use arrow keys to navigate. '^Q' Quit, '^P' Timing, '^S' Create Ptr, '^L' LinkedList, '^A' DynamicArray, '^W' Toggle Weak/Smart, '^T' Copy Ptr, '^R' Run Tests");
    mvprintw(1, 0, "%s %s Mode:", isWeakMode ? "Weak" : "Smart", isArrayMode ? "Array" : "Linked List");

    size_t size = (isArrayMode)
        ? (isWeakMode ? weakPointerArray.GetSize() : smartPointerArray.GetSize())
        : (isWeakMode ? weakPointerList.GetSize() : smartPointerList.GetSize());

    for (size_t i = 0; i < size; i++) {
        if (isWeakMode) {
            const WeakPtr<T>& weakPtr = isArrayMode ? weakPointerArray.Get(i) : weakPointerList.Get(i);
            if (!weakPtr.expired()) {
                mvprintw(i + 2, 0, "Weak Pointer %lu (Expired: No, Weak Count: %lu, Smart Count: %lu)", i, weakPtr.getWeakCount(), weakPtr.getSmartCount());
            } else {
                mvprintw(i + 2, 0, "Weak Pointer %lu (Expired: Yes)", i);
            }
        } else {
            const SharedPtr<T>& smartPtr = isArrayMode ? smartPointerArray.Get(i) : smartPointerList.Get(i);
            mvprintw(i + 2, 0, "Smart Pointer %lu (Value: %d, Smart Count: %lu, Weak Count: %lu)", i, *smartPtr, smartPtr.getSmartCount(), smartPtr.getWeakCount());
        }
    }
    refresh();
}

// Creates a new Smart Pointer and adds it to the list or array.
template <class T>
void CreateSmartPointer(
    LinkedList<SharedPtr<T>>& smartPointerList, 
    DynamicArray<SharedPtr<T>>& smartPointerArray, 
    bool isArrayMode
) 
{
    T value;
    mvprintw(22, 0, "Enter value for new Smart Pointer: ");
    echo();
    scanw("%d", &value);
    noecho();
    
    SharedPtr<T> smartPtr(new T(value));
    if (isArrayMode) {
        smartPointerArray.Append(smartPtr);
    } else {
        smartPointerList.Append(smartPtr);
    }
}

// Creates a new Weak Pointer based on an existing Smart Pointer.
template <class T>
void CreateWeakPointer(
    LinkedList<WeakPtr<T>>& weakPointerList, 
    DynamicArray<WeakPtr<T>>& weakPointerArray,
    const LinkedList<SharedPtr<T>>& smartPointerList, 
    const DynamicArray<SharedPtr<T>>& smartPointerArray, 
    bool isArrayMode
) 
{
    size_t index;
    mvprintw(22, 0, "Enter index of Smart Pointer to create Weak Pointer: ");
    echo();
    scanw("%ld", &index);
    noecho();
    
    if (isArrayMode && index < smartPointerArray.GetSize()) {
        WeakPtr<T> weakPtr(smartPointerArray.Get(index));
        weakPointerArray.Append(weakPtr);
    } else if (!isArrayMode && index < smartPointerList.GetSize()) {
        WeakPtr<T> weakPtr(smartPointerList.Get(index));
        weakPointerList.Append(weakPtr);
    }
}

// Copies an existing pointer and appends it to the list or array.
template <class T>
void CopyPointer(
    LinkedList<SharedPtr<T>>& smartPointerList, 
    DynamicArray<SharedPtr<T>>& smartPointerArray,
    LinkedList<WeakPtr<T>>& weakPointerList, 
    DynamicArray<WeakPtr<T>>& weakPointerArray,
    bool isArrayMode, bool isWeakMode
) 
{
    size_t index;
    mvprintw(22, 0, "Enter index to copy existing Pointer: ");
    echo();
    scanw("%ld", &index);
    noecho();
    
    if (isWeakMode) {
        if (isArrayMode && index < weakPointerArray.GetSize()) {
            WeakPtr<T> weakPtr = weakPointerArray.Get(index);
            weakPointerArray.Append(weakPtr);
        } else if (!isArrayMode && index < weakPointerList.GetSize()) {
            WeakPtr<T> weakPtr = weakPointerList.Get(index);
            weakPointerList.Append(weakPtr);
        }
    } else {
        if (isArrayMode && index < smartPointerArray.GetSize()) {
            SharedPtr<T> smartPtr = smartPointerArray.Get(index);
            smartPointerArray.Append(smartPtr);
        } else if (!isArrayMode && index < smartPointerList.GetSize()) {
            SharedPtr<T> smartPtr = smartPointerList.Get(index);
            smartPointerList.Append(smartPtr);
        }
    }
}

// Handles keypresses for the main menu and interactions.
template <class T>
void HandleKeypress(
    int ch, 
    LinkedList<SharedPtr<T>>& smartPointerList, 
    DynamicArray<SharedPtr<T>>& smartPointerArray,
    LinkedList<WeakPtr<T>>& weakPointerList, 
    DynamicArray<WeakPtr<T>>& weakPointerArray,
    bool& isArrayMode, bool& isWeakMode, int& selected
) 
{
    switch (ch) {
        case 17: // Ctrl+Q
            endwin();
            exit(0);
        case 19: // Ctrl+S
            if (isWeakMode) {
                CreateWeakPointer(weakPointerList, weakPointerArray, smartPointerList, smartPointerArray, isArrayMode);
            } else {
                CreateSmartPointer(smartPointerList, smartPointerArray, isArrayMode);
            }
            break;
        case 20: // Ctrl+T
            CopyPointer(smartPointerList, smartPointerArray, weakPointerList, weakPointerArray, isArrayMode, isWeakMode);
            break;
        case 12: // Ctrl+L
            isArrayMode = false;
            break;
        case 16: // Ctrl+P
            RunTimingTests();
            break;
        case 1: // Ctrl+A
            isArrayMode = true;
            break;
        case 23: // Ctrl+W
            //testDrawing();
            RunTimingTests();
            //TODO delete K
            isWeakMode = !isWeakMode;
            break;
        case 18: // Ctrl+R
            RunTests();
            break;
        case KEY_UP:
            selected = (selected > 0) ? selected - 1 : selected;
            break;
        case KEY_DOWN:
            selected++;
            break;
        default:
            break;
    }
}
void work();
#endif /* UI_H */