#include "test.hpp"
#include "timeTests.hpp"
#include "UI.hpp"
void InitializeUI()
{
    initscr(); 
    raw(); 
    keypad(stdscr, TRUE); 
    noecho(); 
    start_color(); 
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
}
void RunTimingTests()
{
    doPlotting();
    makeTimeTest(); 
}
void RunTests()
{
    testAll(); 
}
void work()
{
    LinkedList<SharedPtr<int>> smartPointerList;
    DynamicArray<SharedPtr<int>> smartPointerArray;
    LinkedList<WeakPtr<int>> weakPointerList;
    DynamicArray<WeakPtr<int>> weakPointerArray;
    bool isArrayMode = false;
    bool isWeakMode = false;
    int selected = 0;

    InitializeUI();

    while (true) {
        DrawUI(smartPointerList, smartPointerArray, weakPointerList, weakPointerArray, isArrayMode, isWeakMode, selected);

        int ch = getch();
        HandleKeypress(ch, smartPointerList, smartPointerArray, weakPointerList, weakPointerArray, isArrayMode, isWeakMode, selected);
    }

    endwin();
}