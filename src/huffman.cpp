#include "huffman.hpp"
#include "bitmanip.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
using std::make_unique;
using std::unique_ptr;

void compute_bitstring_lengths(const std::unique_ptr<Node> &root,
                               std::map<Symbol, int> &bitstring_length, int depth)
{
    if (root)
    {
        if (root->is_leaf)
        {
            bitstring_length[root->sym] = depth;
            return;
        }
        compute_bitstring_lengths(root->left, bitstring_length, depth + 1);
        compute_bitstring_lengths(root->right, bitstring_length, depth + 1);
    }
}

Node *HuffmanCode::build_from_frequency(const SymbolCountTable &frequency)
{
    if (frequency.begin() == frequency.end())
    {
        // The frequency table is empty, throw an exception
        throw std::logic_error("Supplied frequency table is empty");
    }

    std::priority_queue<Node *, std::vector<Node *>, Node_raw_ptr_compartor> nodes;
    // Initially each input symbol will be a leaf node of the Huffman tree
    for (const auto &symbol : frequency)
    {
        nodes.push(new Node(symbol.first, symbol.second));
    }
    // Then pick two smallest nodes by value, combine them into a new node, and add the new node to
    // the priority queue
    while (nodes.size() > 1)
    {
        auto smallest = nodes.top();
        nodes.pop();
        auto second_smallest = nodes.top();
        nodes.pop();

        auto new_node = new Node(smallest->value + second_smallest->value);
        // Transfer ownership of the two smallest nodes to the newly created node
        new_node->left = unique_ptr<Node>(smallest);
        new_node->right = unique_ptr<Node>(second_smallest);

        nodes.push(new_node);
    }

    // The root node is the node left in the priority queue
    root = unique_ptr<Node>(nodes.top());

    std::map<Symbol, int> bitstring_length;
    compute_bitstring_lengths(root, bitstring_length, 0);

    std::vector<std::pair<int, Symbol>> symbols;
    for (const auto &pair : bitstring_length)
    {
        // Reverse the order, insert (value, key) pairs into the vector
        symbols.push_back(std::make_pair<>(pair.second, pair.first));
    }
    std::sort(symbols.begin(), symbols.end());

    // Build the canonical huffman code
    bits code = {0};
    for (int i = 0; i < symbols.size(); i++)
    {
        std::cout << symbols[i].second.sym << ": " << code << std::endl;
        if (i == (symbols.size() - 1))
            break;
        code = left_shift(add(code, 1), symbols[i + 1].first - symbols[i].first);
    }

    return root.get();
}