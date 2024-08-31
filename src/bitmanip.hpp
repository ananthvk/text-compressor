#pragma once
#include <ostream>
#include <stdexcept>
#include <vector>
// This file contains functions related to bit manipulation, bit streams, bit reader and writer


using bits = std::vector<bool>;

// If bit is 0, returns l as it is
// If bit is 1, add the bit to l and return the result
inline bits add(bits l, int bit)
{
    if (l.empty())
        throw std::logic_error("Bits is empty");

    if (bit == 0)
    {
        return l;
    }
    else if (bit == 1)
    {
        int carry = 1;
        for (int i = l.size() - 1; i >= 0; i--)
        {
            int sum = l[i] + carry;
            l[i] = sum % 2;
            if (sum <= 1)
            {
                // Carry has not been generated
                return l;
            }
        }
        // If control reaches here, it means that overflow has occured
        l.insert(l.begin(), 1);
        return l;
    }
    else
    {
        throw std::logic_error("Bit can only be 0 or 1");
    }
}

// Adds shift number of zeroes after value, thereby shifting it to the left
inline bits left_shift(bits value, int shift)
{
    for (int i = 0; i < shift; i++)
        value.push_back(0);
    return value;
}

inline std::ostream &operator<<(std::ostream &os, const bits &b)
{
    for(const auto& bitval: b)
        os << bitval;
    return os;
}