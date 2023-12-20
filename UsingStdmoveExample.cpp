// UsingStdmoveExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

template<class T>
void myswapCopy(T& a, T& b)
{
	T tmp{ a }; // invokes copy constructor
	a = b; // invokes copy assignment
	b = tmp; // invokes copy assignment
}

// std::move to convert our l-values into r-values so we can invoke move semantics:
template<class T>
void myswapMove(T& a, T& b)
{
	T tmp{ std::move(a) }; // invokes move constructor
	a = std::move(b); // invokes move assignment
	b = std::move(tmp); // invokes move assignment
}

int main()
{
	std::string x1{ "abc" };
	std::string y1{ "de" };

	std::cout << x1 << '\n';
	std::cout << y1 << '\n';

	myswapCopy(x1, y1); // this version of swap makes 3 copies.

	std::cout << x1 << '\n';
	std::cout << y1 << '\n';

	std::string x2{ "xyz" };
	std::string y2{ "uv" };

	std::cout << x2 << '\n';
	std::cout << y2 << '\n';

	myswapMove(x2, y2); // this version of swap makes 3 moves....more efficient

	std::cout << x2 << '\n';
	std::cout << y2 << '\n';

	return 0;
}

