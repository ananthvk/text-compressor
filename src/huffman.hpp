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

class HuffmanTree
{
    std::unique_ptr<Node> root;

  public:
    HuffmanTree() : root(nullptr) {}

    // Builds a Huffman Tree from the given frequency distribution table
    void build_from_frequency_table(const SymbolCountTable &frequency);

    // Return a non owning pointer to the root of the tree
    Node *get_root() const { return root.get(); }
};

// This class implements a canonical huffman code
class HuffmanCode
{
  public:
    // Builds a Huffman code from the given huffman tree
    void build_from_tree(Node *root);

    // Build a huffman code from symbols and their bitstring length
    void build_from_bitstring_length(const SymbolCountTable &length);
};