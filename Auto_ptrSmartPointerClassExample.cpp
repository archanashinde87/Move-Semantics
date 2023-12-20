// Auto_ptrSmartPointerClassExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class Auto_ptr3
{
    T* m_ptr{};

public:
    Auto_ptr3(T* ptr = nullptr)
        :m_ptr{ ptr }
    {
    }

    ~Auto_ptr3()
    {
        delete m_ptr;
    }

    // Copy constructor
    Auto_ptr3(const Auto_ptr3& copy)
    {
        m_ptr = new T;
        *m_ptr = *copy.m_ptr;
    }

    // Copy assignment
    Auto_ptr3& operator=(const Auto_ptr3& source)
    {
        if (&source== this)
            return *this;

        delete m_ptr;

        m_ptr = new T;
        *m_ptr = *source.m_ptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() { return m_ptr == nullptr; }

};
class Resource
{
public:
    Resource() { std::cout << "Resource acquired.\n"; }
    ~Resource() { std::cout << "Resource destroyed.\n"; }
};

Auto_ptr3<Resource> generateResource()
{
    Auto_ptr3<Resource> res{ new Resource };
    return res;  // this return value will invoke the copy constructor
}

int main()
{
    Auto_ptr3<Resource> mainRes;
    mainRes = generateResource();

    return 0;
}

