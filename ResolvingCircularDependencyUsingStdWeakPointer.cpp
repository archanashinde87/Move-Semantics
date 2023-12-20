// ResolvingCircularDependencyUsingStdWeakPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>

class Person
{
    std::string m_name{};
    std::weak_ptr<Person> m_partner{};

public:
    Person(const std::string& name)
        :m_name{ name }
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if (!p1 || !p2)
            return false;

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }

};
int main()
{
    auto archu{ std::make_shared<Person>("Archana") };
    auto shanky{ std::make_shared<Person>("Shankar") };

    partnerUp(archu, shanky);

    return 0;
}

