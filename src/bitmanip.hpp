#pragma once
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <stdint.h>
#include <vector>
// This file contains functions related to bit manipulation, bit streams, bit reader and writer


using bits = std::vector<bool>;
using bytes = std::vector<uint8_t>;

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
        for (int i = static_cast<int>(l.size() - 1); i >= 0; i--)
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
    for (const auto &bitval : b)
        os << bitval;
    return os;
}

class BitStreamWriter
{
    bits stream;

  public:
    void write(bool bit) { stream.push_back(bit); }

    void write(const bits &b) { stream.insert(stream.end(), b.begin(), b.end()); }

    // Return the stream as bytes, after calling this function, the stream is cleared
    bytes as_bytes()
    {
        // Pad with extra zero bits at the end
        while (stream.size() % 8 != 0)
            stream.push_back(0);

        bytes result;
        uint8_t temp_byte = 0;
        for (uint64_t i = 0; i < stream.size(); i++)
        {
            if (i != 0 && i % 8 == 0)
            {
                result.push_back(temp_byte);
                temp_byte = 0;
            }
            temp_byte <<= 1;
            temp_byte |= stream[i];

            // Check if this is the last byte
            if ((i + 1) == stream.size())
            {
                result.push_back(temp_byte);
            }
        }
        clear();
        return result;
    }

    void clear() { stream.clear(); }
};