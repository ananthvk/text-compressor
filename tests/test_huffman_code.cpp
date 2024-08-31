#include "huffman.hpp"
#include "gtest/gtest.h"

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

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}