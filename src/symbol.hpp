#pragma once
#include <map>
#include <stdint.h>

struct Symbol
{
    uint8_t sym;

    bool operator<(const Symbol &other) const { return sym < other.sym; }
};

class SymbolCountTable
{
  private:
    std::map<Symbol, uint64_t> freq_table;

  public:
    void increment(Symbol symbol) { ++freq_table[symbol]; }

    void clear() { freq_table.clear(); }

    uint64_t count(Symbol symbol)
    {
        auto iter = freq_table.find(symbol);
        if (iter == freq_table.end())
            return 0;
        return iter->second;
    }

    auto begin() const { return freq_table.begin(); }

    auto end() const { return freq_table.end(); }
};
