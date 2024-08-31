#include "huffman.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <sstream>

TEST(HuffmanCodeTest, FromTree)
{
    std::string s = "BBBBAACD";
    std::map<Symbol, uint64_t> freq;
    for (const auto &ch : s)
    {
        ++freq[{static_cast<unsigned char>(ch)}];
    }

    HuffmanTree tree;
    tree.build_from_frequency_table(freq);

    HuffmanCode code;
    code.build_from_tree(tree.get_root());
}

TEST(HuffmanCodeTest, CompressionTest)
{
    std::cout << "Enter text:";
    std::string s;
    std::getline(std::cin, s);
    std::map<Symbol, uint64_t> freq;
    for (const auto &ch : s)
    {
        ++freq[{static_cast<unsigned char>(ch)}];
    }

    HuffmanTree tree;
    tree.build_from_frequency_table(freq);

    HuffmanCode code;
    code.build_from_tree(tree.get_root());

    BitStreamWriter writer;
    for (const auto &ch : s)
    {
        code.compress({static_cast<uint8_t>(ch)}, writer);
    }

    auto compressed = writer.as_bytes();

    std::cout << "Actual size: " << s.size() << std::endl;
    std::cout << "Compressed size: " << compressed.size() << std::endl;
    //for (const auto &byte : compressed)
    //{
    //    std::cout << "0x" << std::hex << (int)byte << " ";
    //}
    //std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}