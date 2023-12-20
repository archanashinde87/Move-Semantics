// PerformanceStudyForCopyVsMoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <chrono>

template <typename T>
class DynamicArray
{
    T* m_array{};
    int m_length{};

public:
    DynamicArray(int length)
        :m_array{new T[length]}
        ,m_length {length}
    {
    }

    ~DynamicArray()
    {
        delete[] m_array;
    }

    // Copy Constructor
    DynamicArray(const DynamicArray& arr) = delete;
    //    : m_length{arr.m_length}
    //{
    //    m_array = new T[m_length];
    //    std::copy_n(arr.m_array, m_length, m_array); // copy m_length elements from arr to m_array
    //}

    // Copy Assignment
    DynamicArray& operator=(const DynamicArray& arr) = delete;
 /*   {
        if (&arr == this)
            return *this;

        delete[] m_array;

        m_length = arr.m_length;
        m_array = new T[m_length];
        std::copy_n(arr.m_array, m_length, m_array);

        return *this;
    }*/

    // Move Constructor
    DynamicArray(DynamicArray&& arr) noexcept
        :m_array{arr.m_array}
        ,m_length{ arr.m_length }
    {
        arr.m_length = 0;
        arr.m_array = nullptr;
    }

    // Move assignment
    DynamicArray& operator=(DynamicArray&& arr) noexcept
    {
        if (&arr == this)
            return *this;

        delete[] m_array;

        m_length = arr.m_length;
        m_array = arr.m_array;
        arr.m_length = 0;
        arr.m_array = nullptr;

        return *this;
    }

    int getLength() const { return m_length; }
    T& operator[](int index) { return m_array[index]; }
    const T& operator[](int index) const { return m_array[index]; }
};

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<Clock> m_beg{ Clock::now() };

public:
    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int>& arr)
{
    DynamicArray<int> dbl(arr.getLength());
    for (int i = 0; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;

    return dbl;
}

int main()
{
    Timer t;

    DynamicArray<int> arr(1000000);

    for (int i = 0; i < arr.getLength(); i++)
        arr[i] = i;

    arr = cloneArrayAndDouble(arr);

    std::cout << t.elapsed();
}

// Time taken 0.0946458 for Copy Semantics
// Time taken 0.0326823 for Move Semantics
// Comparing the runtime of the two programs, (0.0946458 - 0.0326823) / 0.0946458 * 100 = 65.4688322144 % faster!


