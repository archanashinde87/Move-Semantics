// IntroductionToMoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
class Auto_ptr2
{
    T* m_ptr{};

public:

    // Default Constructor
    Auto_ptr2(T* ptr = nullptr)
        : m_ptr{ ptr }
    {}

    // Destructor
    ~Auto_ptr2()
    {
        delete m_ptr;
    }

    // A Copy Constructor that implements move semantics
    Auto_ptr2(Auto_ptr2& source) // non-const
    {
        m_ptr = source.m_ptr;  // transfer our dumb pointer from the source to our local object
        source.m_ptr = nullptr; // make sure the source no longer owns the pointer
    }

   // An assignment operator that implements move semantics
    Auto_ptr2& operator=(Auto_ptr2& source)
    {
        if (this == &source) // check for self assignment
            return *this;

        delete m_ptr; // make sure we deallocate any pointer the destination is already holding first

        m_ptr = source.m_ptr; // then transfer our dumb pointer from the source to the local object
        source.m_ptr = nullptr; // make sure the source no longer owns the pointer

        return *this;
    }

    T& operator*() { return *m_ptr; }
    T* operator->() { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};
int main()
{
    Auto_ptr2<Resource> res1( new Resource() );
    Auto_ptr2<Resource> res2; // Start as nullptr

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    res2 = res1; // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    return 0;

}

