#pragma once
#include "symbol.hpp"
#include <memory>
#include <queue>
#include <vector>


struct Node;

struct Node
{
    Symbol sym;
    uint64_t value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    bool is_leaf;

    Node(Symbol sym, uint64_t value)
        : sym(sym), value(value), left(nullptr), right(nullptr), is_leaf(true)
    {
    }

    Node(uint64_t value) : value(value), left(nullptr), right(nullptr), is_leaf(false) {}
};

struct Node_raw_ptr_compartor
{
    bool operator()(const Node *first, const Node *second) const
    {
        return first->value > second->value;
    }
};

class HuffmanCode
{
    std::unique_ptr<Node> root;

  public:
    HuffmanCode() : root(nullptr) {}

    // Builds the Huffman tree with the given symbol count, also returns the root of the
    // uncanonicalized, unprocessed tree
    // Note: The returned node does not transfer ownership, the pointer is valid as long as this
    // object is valid
    Node *build_from_frequency(const SymbolCountTable &frequency);
};