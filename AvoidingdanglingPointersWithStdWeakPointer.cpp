// AvoidingdanglingPointersWithStdWeakPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};
Resource* getDumbPtr()
{
    auto ptr{ std::make_unique<Resource>() };
    return ptr.get();
} // ptr goes out of scope, Resource destroyed

std::weak_ptr<Resource> getWeakPtr()
{
   auto ptr {std::make_shared<Resource>()};
   return std::weak_ptr<Resource>{ptr};
}
int main()
{
    auto dumb{ getDumbPtr() };
    std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

    auto weak{ getWeakPtr() };
    std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

    return 0;
}

