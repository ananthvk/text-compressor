#include "huffman.hpp"
#include <stdexcept>
using std::make_unique;
using std::unique_ptr;

Node *HuffmanCode::build_from_frequency(const SymbolCountTable &frequency)
{
    if (frequency.begin() == frequency.end())
    {
        // The frequency table is empty, throw an exception
        throw std::logic_error("Supplied frequency table is empty");
    }

    std::priority_queue<Node*, std::vector<Node*>, Node_raw_ptr_compartor> nodes;
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

    return root.get();
}