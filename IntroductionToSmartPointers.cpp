// MoveSemanticsPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
class Auto_ptr1
{
    T* m_ptr{};

public:

    // Pass in a pointer to "own" via the constructor
    Auto_ptr1(T* ptr = nullptr)
        :m_ptr{ ptr }
    {}
    // The destructor will make sure it gets deallocated
    ~Auto_ptr1()
    {
        delete m_ptr;
    }

    // overloaded dereference operator
    T& operator*() { return *m_ptr; }

    // overloaded operator->
   T* operator->() { return m_ptr; }

};

class Resource
{
public:
    Resource()
    {
        std::cout << "Resource acquired\n";
    }
    ~Resource()
    {
        std::cout << "Resource destroyed\n";
    }
    void sayHi()
    {
        std::cout << "Hi!\n";
    }

};

void someFunction()
{
    Auto_ptr1<Resource> ptr(new Resource());

    int x{};
    std::cout << "Enter an integer:";
    std::cin >> x;

    if (x == 0)
        return; // the function returns early

    // do stuff with pointer here
    ptr->sayHi();

}
int main()
{
    someFunction();
    return 0;
}

