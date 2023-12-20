// Auto_ptrClassExampleWithMoveConstructorAndAssignmentOp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
class Auto_ptr4
{
    T* m_ptr{};

public:
    Auto_ptr4(T* ptr = nullptr)
        :m_ptr{ptr}
    {
    }
   ~Auto_ptr4()
    {
       delete m_ptr;
    }

   // Copy Constructor
   Auto_ptr4(const Auto_ptr4& a)
   {
       m_ptr = new T;
       *m_ptr = *a.m_ptr;
   }

   // Move Constructor
   Auto_ptr4(Auto_ptr4&& a) noexcept
       : m_ptr{ a.m_ptr }
   {
       a.m_ptr = nullptr;
   }

   // Copy Assignment - do deep copy of a.m_ptr to m_ptr
   Auto_ptr4& operator=(const Auto_ptr4& a)
   {
       //self assignment check
       if (&a==this)
           return *this;
       // delete any resources if holding
       delete m_ptr;

       //copy the resource
       m_ptr = new T;
       *m_ptr = *a.m_ptr;

       return *this;
   }

   // Move assignment
   Auto_ptr4& operator=(Auto_ptr4&& a)  noexcept
   {
       // self-assignment check
       if (&a == this)
           return *this;

       // Release any resource we are holding
       delete m_ptr;

       // Transfer ownership of a.m_ptr to m_ptr
       m_ptr = a.m_ptr;
       a.m_ptr = nullptr;

       return *this;
   }

   T& operator*() const
   {
       return *m_ptr;
   }
   T* operator->() const
   {
       return m_ptr;
   }

   bool isNull() const
   {
       return m_ptr == nullptr;
   }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired.\n"; }
    ~Resource() { std::cout << "Resource destroyed.\n"; }
};

Auto_ptr4<Resource> generateResource()
{
    Auto_ptr4<Resource> res{ new Resource };
    return res; // this return value will invoke the move constructor
}
int main()
{
    Auto_ptr4<Resource> mainRes;
    mainRes = generateResource(); // this assignment will invoke the move assignment

    return 0;
}

