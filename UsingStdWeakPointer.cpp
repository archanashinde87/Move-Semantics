// UsingStdWeakPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

    const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); }
    const std::string& getName() const { return m_name; }

};

int main()
{
    auto archie{ std::make_shared<Person>("Archie") };
    auto shanky{ std::make_shared<Person>("Shanky") };

    partnerUp(archie, shanky);

    auto partner = shanky->getPartner(); // get shared_ptr to shanky's partner
    std::cout << shanky->getName() << "'s partner is: " << partner->getName() << '\n';

    return 0;
}

